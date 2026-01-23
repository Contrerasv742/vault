#include "crypto/cipher.h"

#include "encryptpage.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QRandomGenerator>
#include <QVBoxLayout>

EncryptPage::EncryptPage(QWidget *parent) : QWidget(parent) {
    setupUI();
    generatePassword();
}

void EncryptPage::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(20);
    mainLayout->setAlignment(Qt::AlignCenter);

    titleLabel = new QLabel("Encrypt", this);
    titleLabel->setStyleSheet(
            "font-size: 24px; font-weight: bold; color: #FFFFFF;");
    titleLabel->setAlignment(Qt::AlignCenter);

    passwordLabel = new QLabel(this);
    passwordLabel->setStyleSheet(
            "font-size: 36px; font-weight: bold; color: #DC8A78;");
    passwordLabel->setAlignment(Qt::AlignCenter);
    passwordLabel->setWordWrap(true);

    strengthLabel = new QLabel(this);
    strengthLabel->setStyleSheet("font-size: 18px; color: #FFFFFF;");
    strengthLabel->setAlignment(Qt::AlignCenter);

    QHBoxLayout *sliderLayout = new QHBoxLayout();
    sliderLayout->setAlignment(Qt::AlignCenter);

    passwordLengthSlider = new QSlider(Qt::Horizontal, this);
    passwordLengthSlider->setRange(8, 32);
    passwordLengthSlider->setValue(16);
    passwordLengthSlider->setStyleSheet(
            "QSlider::groove:horizontal {"
            "   background: #323547;"
            "   height: 8px;"
            "   border-radius: 4px;"
            "}"
            "QSlider::handle:horizontal {"
            "   background: #DC8A78;"
            "   width: 18px;"
            "   margin-top: -5px;"
            "   margin-bottom: -5px;"
            "   border-radius: 9px;"
            "}");

    passwordLengthLabel = new QLabel("16", this);
    passwordLengthLabel->setStyleSheet("color: #FFFFFF;");
    passwordLengthLabel->setAlignment(Qt::AlignCenter);

    sliderLayout->addStretch();
    sliderLayout->addWidget(passwordLengthSlider);
    sliderLayout->addWidget(passwordLengthLabel);
    sliderLayout->addStretch();

    encryptionAlgorithmComboBox = new QComboBox(this);
    encryptionAlgorithmComboBox->addItems(
            QStringList() << "caesar" << "vigenere" << "rot13" << "rsa");
    encryptionAlgorithmComboBox->setStyleSheet(
            "QComboBox {"
            "   background-color: #323547;"
            "   color: #FFFFFF;"
            "   border: 1px solid #DC8A78;"
            "   padding: 5px;"
            "   border-radius: 3px;"
            "}"
            "QComboBox::drop-down {"
            "   border: none;"
            "}");

    textToEncrypt = new QTextEdit(this);
    textToEncrypt->setPlaceholderText("Enter text to encrypt...");
    textToEncrypt->setStyleSheet(
            "QTextEdit {"
            "   background-color: #323547;"
            "   color: #FFFFFF;"
            "   border: none;"
            "   padding: 10px;"
            "   border-radius: 5px;"
            "}");

    encryptButton = new QPushButton("Encrypt", this);
    encryptButton->setStyleSheet(
            "QPushButton {"
            "   background-color: #DC8A78;"
            "   color: #FFFFFF;"
            "   border: none;"
            "   padding: 10px 20px;"
            "   border-radius: 5px;"
            "   font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "   background-color: #C77A68;"
            "}");

    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(passwordLabel);
    mainLayout->addWidget(strengthLabel);
    mainLayout->addLayout(sliderLayout);
    mainLayout->addWidget(encryptionAlgorithmComboBox);
    mainLayout->addWidget(textToEncrypt);
    mainLayout->addWidget(encryptButton, 0, Qt::AlignCenter);
    mainLayout->addStretch();

    connect(passwordLengthSlider, &QSlider::valueChanged, this,
            &EncryptPage::updatePasswordLength);
    connect(passwordLengthSlider, &QSlider::valueChanged, this,
            &EncryptPage::generatePassword);
    connect(encryptButton, &QPushButton::clicked, this,
            &EncryptPage::encryptText);
}

void EncryptPage::updatePasswordLength(int value) {
    passwordLengthLabel->setText(QString::number(value));
    updateStrengthIndicator();
}

void EncryptPage::generatePassword() {
    int length = passwordLengthSlider->value();
    QString password = generateRandomPassword(length);
    passwordLabel->setText(password);
    updateStrengthIndicator();
}

QString EncryptPage::generateRandomPassword(int length) {
    const QString possibleCharacters =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$"
            "%^&*("
            ")";
    QString randomString;
    for (int i = 0; i < length; ++i) {
        int index = QRandomGenerator::global()->bounded(
                possibleCharacters.length());
        QChar nextChar = possibleCharacters.at(index);
        randomString.append(nextChar);
    }
    return randomString;
}

void EncryptPage::updateStrengthIndicator() {
    int length = passwordLengthSlider->value();
    QString strength = assessPasswordStrength(length);
    strengthLabel->setText(strength);
}

QString EncryptPage::assessPasswordStrength(int length) {
    if (length <= 8) return "Very Weak";
    if (length <= 12) return "Weak";
    if (length <= 16) return "Mediocre";
    if (length <= 20) return "Strong";
    return "Very Strong";
}

void EncryptPage::encryptText() {
    QString selectedAlgorithm = encryptionAlgorithmComboBox->currentText();
    QString textToBeEncrypted = textToEncrypt->toPlainText();
    QString generatedPassword = passwordLabel->text();

    // Here you would call your encryption function based on the selected
    // algorithm For now, we'll just print the information
    qDebug() << "Algorithm:" << selectedAlgorithm;
    qDebug() << "Text to encrypt:" << textToBeEncrypted;
    qDebug() << "Generated password (key):" << generatedPassword;

    // You can implement the actual encryption here using the cipherOptable
    // std::string encryptedText =
    // cipherOptable[selectedAlgorithm.toStdString()](textToBeEncrypted.toStdString(),
    // generatedPassword.toStdString());
    // textToEncrypt->setPlainText(QString::fromStdString(encryptedText));
}
