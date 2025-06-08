#ifndef PROMPTDIALOG_HPP
#define PROMPTDIALOG_HPP

#include <QDialog>
#include <nlohmann/json.hpp>

class QLabel;
class QVBoxLayout;

class PromptDialog : public QDialog {
    Q_OBJECT
public:
    explicit PromptDialog(QWidget* parent = nullptr);
    void setPrompt(const std::string& prompt, const nlohmann::json& options);
    std::string execAndGetResult();
private:
    QLabel* promptLabel;
    QVBoxLayout* buttonLayout;
    QString result;
};

#endif // PROMPTDIALOG_HPP
