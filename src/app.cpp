#include "app.h"
#include "main.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>

EncryptionApp::EncryptionApp(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Password Manager");

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    modeComboBox = new QComboBox(this);
    modeComboBox->addItems({"encrypt", "decrypt"});
    layout->addWidget(modeComboBox);

    cipherComboBox = new QComboBox(this);
    for (const auto &cipher : cipherOptable) {
        cipherComboBox->addItem(QString::fromStdString(cipher.first));
    }
    layout->addWidget(cipherComboBox);

    inputText = new QLineEdit(this);
    layout->addWidget(inputText);

    outputText = new QTextEdit(this);
    outputText->setReadOnly(true);
    layout->addWidget(outputText);

    QPushButton *processButton = new QPushButton("Process", this);
    layout->addWidget(processButton);

    setCentralWidget(centralWidget);

    connect(processButton, &QPushButton::clicked, this, &EncryptionApp::processText);
}

void EncryptionApp::processText() {
    std::string mode = modeComboBox->currentText().toStdString();
    std::string cipher = cipherComboBox->currentText().toStdString();
    std::string input = inputText->text().toStdString();

    std::string result;
    if (mode == "encrypt") {
        result = cipherOptable[cipher](input);
    } else {
        // For decryption, you might need to implement separate decrypt functions
        // or modify your existing functions to handle both encryption and decryption
        result = cipherOptable[cipher](input);
    }

    outputText->setText(QString::fromStdString(result));
}

EncryptionApp::~EncryptionApp() {
    // Destructor implementation (can be empty if no manual cleanup is needed)
}
