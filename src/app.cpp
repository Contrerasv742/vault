#include "app.h"
#include "cipher.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>

EncryptionApp::EncryptionApp(QWidget *parent) : QMainWindow(parent) {
  setWindowTitle("Password Manager");
  setupUI();
}

void EncryptionApp::setupUI() {
  QGridLayout *layout = new QGridLayout;

  // Initialize member widgets
  modeComboBox = new QComboBox(this);
  cipherComboBox = new QComboBox(this);
  inputText = new QLineEdit(this);
  optionalInputText = new QLineEdit(this);
  outputText = new QTextEdit(this);

  // Mode ComboBox
  QLabel *modeLabel = new QLabel("Mode:", this);
  modeComboBox->addItems({"encrypt", "decrypt"});
  layout->addWidget(modeLabel, 0, 0);
  layout->addWidget(modeComboBox, 0, 1);

  // Cipher ComboBox
  QLabel *cipherLabel = new QLabel("Cipher:", this);
  for (const auto &cipher : cipherOptable) {
    cipherComboBox->addItem(QString::fromStdString(cipher.first));
  }
  layout->addWidget(cipherLabel, 1, 0);
  layout->addWidget(cipherComboBox, 1, 1);

  // Input Text
  QLabel *inputLabel = new QLabel("Input:", this);
  layout->addWidget(inputLabel, 2, 0);
  layout->addWidget(inputText, 2, 1);

  // Optional Input Text
  QLabel *optionalInputLabel = new QLabel("Optional:", this);
  layout->addWidget(optionalInputLabel, 2, 0);
  layout->addWidget(optionalInputText, 2, 1);

  // Output Text
  QLabel *outputLabel = new QLabel("Output:", this);
  outputText->setReadOnly(true);
  layout->addWidget(outputLabel, 3, 0);
  layout->addWidget(outputText, 3, 1);

  // Process Button
  QPushButton *processButton = new QPushButton("Process", this);
  layout->addWidget(processButton, 4, 0, 1, 2);

  connect(processButton, &QPushButton::clicked, this, &EncryptionApp::processText);

  QWidget *centralWidget = new QWidget(this);
  centralWidget->setLayout(layout);
  setCentralWidget(centralWidget);
}

void EncryptionApp::styleLabels() {
  QString labelStyle = "QLabel { color: #c0c0c0; font-weight: bold; font-size: 14px; margin-right: 5px; }";
  QList<QLabel*> labels = findChildren<QLabel*>();
  for (QLabel* label : labels) {
    label->setStyleSheet(labelStyle);
  }
}

void EncryptionApp::forceComboBoxDropDown() {
  modeComboBox->setStyle(new ComboBoxStyle());
  cipherComboBox->setStyle(new ComboBoxStyle());
}

void EncryptionApp::updateOptionalInput() {
    QString selectedCipher = cipherComboBox->currentText();
    
    if (selectedCipher == "caesar" || selectedCipher == "rot13") {
        optionalInputText->setPlaceholderText("Enter rotation number");
    } else if (selectedCipher == "vigenere" || selectedCipher == "rsa") {
        optionalInputText->setPlaceholderText("Enter key");
    } else {
        optionalInputText->setPlaceholderText("");
    }
}

void EncryptionApp::processText() {
    std::string mode = modeComboBox->currentText().toStdString();
    std::string cipher = cipherComboBox->currentText().toStdString();
    std::string input = inputText->text().toStdString();
    std::string optionalInput = optionalInputText->text().toStdString();

    std::string result;
    if (mode == "encrypt") {
        result = cipherOptable[cipher](input, optionalInput);
    } else {
        // For decryption, you might need to implement separate decrypt functions
        // or modify your existing functions to handle both encryption and decryption
        result = cipherOptable[cipher](input, optionalInput);
    }

    outputText->setText(QString::fromStdString(result));
}

EncryptionApp::~EncryptionApp() {
  // Destructor implementation (can be empty if no manual cleanup is needed)
}
