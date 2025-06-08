#include "Game.hpp"
#include "Error.hpp"
//#include "InputManager.hpp"
#include "Tiles/Bank.hpp"
#include "Tiles/CardStore.hpp"
#include "MiniGames/MiniGameManager.hpp"
#include "Utils/Utils.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <unordered_map>

std::default_random_engine Game::engine;
std::shared_ptr<Game> Game::instance = nullptr;

Game::Game(const GameConfig& cfg)
    : config(cfg), currentState(State::INIT), gameForceControl(false) {
    board = Board::getInstance(config);
    playersList.clear();
    currentTurnIndex = 0;
    diceResult = "";

    try {
        std::ifstream cmdFile("resources/command.json");
        cmdFile >> commandData;

        std::ifstream dlgFile("resources/dialogue.json");
        dlgFile >> dialogueData;
    } catch (...) {
        throw GameException("Failed to load game dialogue or command JSON.");
    }
}

std::shared_ptr<Game> Game::getInstance(const GameConfig& config) {
    if (!instance) {
        instance = std::shared_ptr<Game>(new Game(config));
    }
    return instance;
}

std::shared_ptr<Game> Game::getInstance() {
    if (!instance) {
        throw GameException("Game instance not initialized. Call getInstance(config) first.");
    }
    return instance;
}

const std::vector<std::shared_ptr<Player>>& Game::getPlayers() const {
    return playersList;
}

const std::shared_ptr<Player> Game::getCurrentPlayer() const{
    return playersList[currentTurnIndex];
}

void Game::nextTurn() {
    if (playersList.empty()) return;

    // Unset current player's turn
    playersList[currentTurnIndex]->setMyTurn(false);

    // Find next valid player (non-bankrupt)
    do {
        currentTurnIndex = (currentTurnIndex + 1) % playersList.size();
    } while (playersList[currentTurnIndex]->isBankrupt());

    // Set turn
    playersList[currentTurnIndex]->setMyTurn(true);
    changeState(State::START);

    std::cout << "🕐 Next turn: " << playersList[currentTurnIndex]->getName() << "\n";
}

void Game::executeSudoCommand(const ParsedCommand& cmd){
    auto player = getCurrentPlayer();
    if (!player) return;

    if (cmd.type == SudoCommandType::MOVE) {
        if (cmd.args.size() >= 1) {
            int pos = std::stoi(cmd.args[0]);
            player->setPosition(pos);
            changeState(State::MOVED);
        }
    } else if (cmd.type == SudoCommandType::GET) {
        if (cmd.args.size() == 1) {
            long long money = std::stoll(cmd.args[0]);
            Bank::getInstance()->payToPlayer(player, money);
        } else if (cmd.args.size() == 2) {
            std::string name = cmd.args[0];
            long long money = std::stoll(cmd.args[1]);
            for (auto& p : playersList) {
                if (p->getName() == name) {
                    Bank::getInstance()->payToPlayer(p, money);
                    break;
                }
            }
        }
    } else if (cmd.type == SudoCommandType::GIVE) {
        if (cmd.args.size() == 2) {
            std::string name = cmd.args[0];
            long long money = std::stoll(cmd.args[1]);
            for (auto& p : playersList) {
                if (p->getName() == name) {
                    if (player->getMoney() >= money) {
                        player->deductMoney(money);
                        p->addMoney(money);
                    }
                    break;
                }
            }
        }
    } else if (cmd.type == SudoCommandType::ADDCARD) {
        if (cmd.args.size() >= 1) {
            std::string cardName = cmd.args[0];
            auto card = CardStore::getInstance()->getCardByName(cardName);
            if (card) player->addCard(card);
        }
    } else if (cmd.type == SudoCommandType::STATE) {
        if (cmd.args.size() >= 1) {
            std::string stateStr = cmd.args[0];
            std::transform(stateStr.begin(), stateStr.end(), stateStr.begin(), ::toupper);
            if (stateStr == "INIT") changeState(State::INIT);
            else if (stateStr == "START") changeState(State::START);
            else if (stateStr == "MOVED") changeState(State::MOVED);
            else if (stateStr == "ROUND_END") changeState(State::ROUND_END);
            else if (stateStr == "FINISH") changeState(State::FINISH);
        }
    } else if (cmd.type == SudoCommandType::INFO) {
        // UI auto-refresh; no-op
    } else if (cmd.type == SudoCommandType::REFRESH) {
        // UI refresh triggered externally
    } else {
        std::cerr << "Unknown sudo command executed.\n";
    }
}
void Game::initGame() {
    playersList.clear();
    currentTurnIndex = 0;

    auto names = config.getPlayerNames();
    auto icons = config.getPlayerIcons();
    auto colors = config.getPlayerColors();
    long long startMoney = config.getStartMoney();

    for (int i = 0; i < config.getPlayersNum(); ++i) {
        auto player = std::make_shared<Player>(
            names[i], icons[i], colors[i], startMoney
        );
        playersList.push_back(player);
    }

    Board::getInstance()->init(config, playersList);

    changeState(State::INIT);
    std::cout << "[INIT] Game initialized with " << playersList.size() << " players.\n";
}

void Game::start() {
    if (currentState != State::INIT) {
        throw GameException("Game has already started or is in an invalid state.");
    }

    changeState(State::START);
    currentTurnIndex = 0;

    for (size_t i = 0; i < playersList.size(); ++i) {
        playersList[i]->setMyTurn(i == currentTurnIndex);
    }

    // Optional: log or show a start message
    std::cout << "🎮 Game started. It's " << playersList[currentTurnIndex]->getName() << "'s turn.\n";
}

void Game::processPlayerAction(std::shared_ptr<Player> player, std::shared_ptr<Tile> tile, bool isCommandResult) {
    if (tile->isBlocked()) {
        std::cout << "This tile is blocked by a barrier. Skipping turn...\n";
        nextTurn();
        return;
    }

    TileAction action = tile->landOn(player);
    nlohmann::json optionsJson;

    switch (action) {
        case TileAction::START_POINT:
            optionsJson = dialogueData["player_action"]["moved"]["start_point"];
            break;
        case TileAction::STORE:
            optionsJson = dialogueData["player_action"]["moved"]["store"];
            break;
        case TileAction::HOSPITAL:
            optionsJson = dialogueData["player_action"]["moved"]["hospital"];
            break;
        case TileAction::JAIL:
            optionsJson = dialogueData["player_action"]["moved"]["jail"];
            break;
        case TileAction::PURCHASE_PROPERTY:
            optionsJson = dialogueData["player_action"]["moved"]["property_unowned"];
            break;
        case TileAction::OWN:
            optionsJson = dialogueData["player_action"]["moved"]["property_owned"];
            break;
        case TileAction::PAY_TOLL:
            optionsJson = dialogueData["player_action"]["moved"]["property_toll"];
            break;
        case TileAction::SPECIAL_EVENT:
            optionsJson = dialogueData["player_action"]["moved"]["event"];
            break;
        case TileAction::NONE:
        default:
            nextTurn();
            return;
    }

    std::string prompt = optionsJson["prompt"];
    std::cout << prompt << "\n";

    const auto& options = optionsJson["options"];
    for (const auto& opt : options) {
        std::cout << "[" << opt["key"] << "] " << opt["description"] << "\n";
    }

    std::string input;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        bool matched = false;
        // TODO: 這邊要想一下，因為我們用UI的話，這邊應該不會有輸入
        for (const auto& opt : options) {
            if (opt["key"] == "*" || opt["key"] == input) {
                matched = true;
                if (input == "I") {
                    //player->printInfo();
                } else if (input == "R") {
                    // Buy or upgrade
                    // Placeholder: handle accordingly
                } else if (input == "S") {
                    // Sell
                    // Placeholder: handle accordingly
                } else if (input == "E") {
                    // Enter store
                    // Placeholder
                } else if (input == "T") {
                    // Roll dice (usually not here)
                }
                if (opt["key"] == "*" || input != "I") {
                    nextTurn();
                    return;
                }
                break;
            }
        }

        if (!matched) {
            std::cout << dialogueData["invalid_input"]["prompt"] << "\n";
        }
    }
}

bool Game::processCommand(std::shared_ptr<Player> player, const std::string& input) {
    /*
    我是想說我們有用UI的話，這邊應該不用了
    */
    throw NotImplement("`Game::processCommand` not implement");
}

void Game::throwDice(std::shared_ptr<Player> player) {
    std::uniform_int_distribution<int> dist(1, 6);
    int result = dist(engine);

    diceResult = std::to_string(result);
    movePlayer(player, result);
}

void Game::checkGameOver() {
    // Count how many players are still alive (not bankrupt)
    int aliveCount = 0;
    std::shared_ptr<Player> lastAlive = nullptr;

    for (const auto& p : playersList) {
        if (!p->isBankrupt()) {
            aliveCount++;
            lastAlive = p;
        }
    }

    if (aliveCount <= 1) {
        changeState(State::FINISH);
        std::cout << "\n============================\n";
        std::cout << "        GAME OVER!\n";
        std::cout << "============================\n";
        if (lastAlive) {
            std::cout << "Winner: " << lastAlive->getName() << " with $" << lastAlive->getMoney() << "\n";
        } else {
            std::cout << "No winner (all players bankrupt).\n";
        }
        endGame();
    }
}

void Game::endGame() {
    std::cout << "\nFinal Player Status:\n";
    std::cout << "---------------------\n";
    for (const auto& player : playersList) {
        std::cout << player->getName() << " - $" << player->getMoney();
        if (player->isBankrupt()) {
            std::cout << " [BANKRUPT]";
        }
        std::cout << "\n";
    }
    std::cout << "\nThank you for playing Monopoly!\n";
}

void Game::changeState(State newState) {
    std::cout << "[STATE] Transition: " << getStateString() << " → ";
    setState(newState);
    std::cout << getStateString() << "\n";
}

State& operator++(State& state) {
    switch (state) {
        case State::INIT: state = State::START; break;
        case State::START: state = State::MOVED; break;
        case State::MOVED: state = State::ROUND_END; break;
        case State::ROUND_END: state = State::FINISH; break;
        case State::FINISH: state = State::FINISH; break;
    }
    return state;
}

void Game::setState(State state) {
    currentState = state;
}

const nlohmann::json& Game::playerAction() {
    static const nlohmann::json empty = dialogueData["invalid_input"];

    std::string stateStr = getStateString();
    if (!dialogueData.contains("player_action") || !dialogueData["player_action"].contains(stateStr)) {
        return empty;
    }

    const auto& base = dialogueData["player_action"][stateStr];
    if (base.contains("default")) {
        return base["default"];
    }
    return base;
}

const nlohmann::json& Game::playerAction(const std::string& key) {
    static const nlohmann::json empty = dialogueData["invalid_input"];

    std::string stateStr = getStateString();
    if (!dialogueData.contains("player_action") || !dialogueData["player_action"].contains(stateStr)) {
        return empty;
    }

    const auto& base = dialogueData["player_action"][stateStr];
    if (base.contains(key)) {
        return base[key];
    }
    if (base.contains("default")) {
        return base["default"];
    }
    return empty;
}

void Game::movePlayer(std::shared_ptr<Player> player, int steps) {
    int oldPos = player->getPosition();
    int mapSize = static_cast<int>(config.getBoardTiles().size());

    int newPos = (oldPos + steps) % mapSize;
    player->setPosition(newPos);

    // 經過起點加獎金
    if (oldPos + steps >= mapSize) {
        player->addMoney(config.getPassingStartBonus());
    }

    auto tile = Board::getInstance()->getTile(newPos);
    tile->landOn(player);

    changeState(State::MOVED);
    processPlayerAction(player, tile);
}

std::string Game::getStateString() {
    switch (currentState) {
        case State::INIT: return "INIT";
        case State::START: return "START";
        case State::MOVED: return "MOVED";
        case State::ROUND_END: return "ROUND_END";
        case State::FINISH: return "FINISH";
        default: return "UNKNOWN";
    }
}

bool Game::isActivateState() const {
    return currentState == State::START || currentState == State::MOVED;
}

bool Game::isRoundState() const {
    return currentState == State::ROUND_END;
}