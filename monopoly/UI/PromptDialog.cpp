#include "PromptDialog.hpp"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

PromptDialog::PromptDialog(QWidget* parent)
    : QDialog(parent), promptLabel(new QLabel(this)), buttonLayout(new QVBoxLayout()) {
    QVBoxLayout* main = new QVBoxLayout(this);
    main->addWidget(promptLabel);
    main->addLayout(buttonLayout);
    setLayout(main);
    setWindowTitle("Action Required");
}

void PromptDialog::setPrompt(const std::string& prompt, const nlohmann::json& options) {
    promptLabel->setText(QString::fromStdString(prompt));

    QLayoutItem* item;
    while ((item = buttonLayout->takeAt(0)) != nullptr) {
        if (item->widget()) item->widget()->deleteLater();
        delete item;
    }

    for (const auto& opt : options) {
        QString text = QString("[%1] %2").arg(QString::fromStdString(opt["key"])).
                arg(QString::fromStdString(opt["description"]));
        QPushButton* btn = new QPushButton(text, this);
        connect(btn, &QPushButton::clicked, this, [this, key=QString::fromStdString(opt["key"])](){
            result = key;
            accept();
        });
        buttonLayout->addWidget(btn);
    }
}

std::string PromptDialog::execAndGetResult() {
    QDialog::exec();
    return result.toStdString();
}
