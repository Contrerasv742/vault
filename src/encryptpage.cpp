#include "encryptpage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRandomGenerator>

EncryptPage::EncryptPage(QWidget *parent) : QWidget(parent)
{
  setupUI();
  generatePassword();
}

void EncryptPage::setupUI()
{
  // Main layout
  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  mainLayout->setContentsMargins(20, 20, 20, 20);
  mainLayout->setSpacing(20);
  mainLayout->setAlignment(Qt::AlignCenter);

  // Title label
  titleLabel = new QLabel("Encrypt", this);
  titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #FFFFFF;");
  titleLabel->setAlignment(Qt::AlignCenter);

  // Password label
  passwordLabel = new QLabel(this);
  passwordLabel->setStyleSheet("font-size: 36px; font-weight: bold; color: #DC8A78;");
  passwordLabel->setAlignment(Qt::AlignCenter);
  passwordLabel->setWordWrap(true);

  // Slider layout
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
    "}"
  );

  passwordLengthLabel = new QLabel("16", this);
  passwordLengthLabel->setStyleSheet("color: #FFFFFF;");
  passwordLengthLabel->setAlignment(Qt::AlignCenter);

  sliderLayout->addStretch();
  sliderLayout->addWidget(passwordLengthSlider);
  sliderLayout->addWidget(passwordLengthLabel);
  sliderLayout->addStretch();

  // Text edit for encryption
  textToEncrypt = new QTextEdit(this);
  textToEncrypt->setPlaceholderText("Enter text to encrypt...");
  textToEncrypt->setStyleSheet(
    "QTextEdit {"
    "   background-color: #323547;"
    "   color: #FFFFFF;"
    "   border: none;"
    "   padding: 10px;"
    "   border-radius: 5px;"
    "}"
  );

  // Button layout
  QHBoxLayout *buttonLayout = new QHBoxLayout();
  buttonLayout->setAlignment(Qt::AlignCenter);

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
    "}"
  );

  buttonLayout->addStretch();
  buttonLayout->addWidget(encryptButton);
  buttonLayout->addStretch();

  // Add widgets to main layout
  mainLayout->addWidget(titleLabel);
  mainLayout->addWidget(passwordLabel);
  mainLayout->addLayout(sliderLayout);
  mainLayout->addWidget(textToEncrypt);
  mainLayout->addLayout(buttonLayout);
  mainLayout->addStretch();

  // Connect signals and slots
  connect(passwordLengthSlider, &QSlider::valueChanged, this, &EncryptPage::updatePasswordLength);
  connect(passwordLengthSlider, &QSlider::valueChanged, this, &EncryptPage::generatePassword);
  connect(encryptButton, &QPushButton::clicked, this, &EncryptPage::encryptText);
}

void EncryptPage::updatePasswordLength(int value)
{
  passwordLengthLabel->setText(QString::number(value));
}

void EncryptPage::generatePassword()
{
  int length = passwordLengthSlider->value();
  QString password = generateRandomPassword(length);
  passwordLabel->setText(password);
}

QString EncryptPage::generateRandomPassword(int length)
{
  const QString possibleCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()";
  QString randomString;
  for(int i=0; i<length; ++i)
  {
    int index = QRandomGenerator::global()->bounded(possibleCharacters.length());
    QChar nextChar = possibleCharacters.at(index);
    randomString.append(nextChar);
  }
  return randomString;
}

void EncryptPage::encryptText()
{
  // Implement your encryption logic here
  // For now, we'll just print the text to encrypt
  qDebug() << "Text to encrypt:" << textToEncrypt->toPlainText();
}
