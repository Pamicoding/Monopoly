#include "SudoDialog.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

SudoDialog::SudoDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("🛠️ Sudo Command Console");
    setFixedSize(450, 180);
    setupUI();
}

void SudoDialog::setupUI() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* titleLabel = new QLabel("Enter Sudo Command (e.g. /move 5):");
    inputField = new QLineEdit();
    execButton = new QPushButton("Execute");
    resultLabel = new QLabel();
    resultLabel->setWordWrap(true);

    QHBoxLayout* inputLayout = new QHBoxLayout();
    inputLayout->addWidget(inputField);
    inputLayout->addWidget(execButton);

    layout->addWidget(titleLabel);
    layout->addLayout(inputLayout);
    layout->addWidget(resultLabel);

    connect(execButton, &QPushButton::clicked, this, &SudoDialog::onCommandEntered);
    connect(inputField, &QLineEdit::returnPressed, this, &SudoDialog::onCommandEntered);

    setLayout(layout);
}

void SudoDialog::setExecutor(std::function<void(const ParsedCommand&)> func) {
    executor = std::move(func);
}

void SudoDialog::onCommandEntered() {
    QString inputText = inputField->text().trimmed();
    if (inputText.isEmpty()) {
        resultLabel->setText("⚠️ Please enter a command.");
        return;
    }

    ParsedCommand cmd = parser.parse(inputText.toStdString());
    if (cmd.type == SudoCommandType::UNKNOWN) {
        resultLabel->setText("❌ Unknown or invalid command.");
        return;
    }

    // 顯示指令提示
    std::string cmdName = inputText.section(' ', 0, 0).mid(1).toStdString(); // remove "/"
    auto def = parser.getDefinition(cmdName);
    resultLabel->setText(QString::fromStdString(def.prompt));

    // 執行
    if (executor) {
        executor(cmd);
    } else {
        resultLabel->setText("⚠️ No executor attached.");
    }
}