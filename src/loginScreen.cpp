#include "loginScreen.h"
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

LoginScreen::LoginScreen(QWidget *parent) : QWidget(parent)
{
  setupUI();
  QTimer::singleShot(100, this, &LoginScreen::animateTitle); // Slight delay to ensure widget is fully initialized
  QTimer::singleShot(3000, this, &LoginScreen::showInputFields);
}

void LoginScreen::setupUI()
{
  setStyleSheet("background-color: #323547; color: white;");

  layout = new QVBoxLayout(this);
  layout->setAlignment(Qt::AlignCenter);

  // Vault Logo
  titleLabel = new QLabel("VAULT", this);
  titleLabel->setStyleSheet("font-size: 48px; font-weight: bold; background-color: none;");
  titleLabel->setAlignment(Qt::AlignCenter);
  layout->addWidget(titleLabel, 0, Qt::AlignCenter);

  // Username Box
  usernameInput = new QLineEdit(this);
  usernameInput->setPlaceholderText("Username");
  usernameInput->setFixedWidth(400);
  usernameInput->setFixedHeight(50);
  usernameInput->setStyleSheet("background-color: #454d6b; border: none; padding: 10px; margin: 5px;");
  usernameInput->hide();
  layout->addWidget(usernameInput);

  // Password Box
  passwordInput = new QLineEdit(this);
  passwordInput->setPlaceholderText("Password");
  passwordInput->setEchoMode(QLineEdit::Password);
  passwordInput->setFixedWidth(400);
  passwordInput->setFixedHeight(50);
  passwordInput->setStyleSheet("background-color: #454d6b; border: none; padding: 10px; margin: 5px;");
  passwordInput->hide();
  layout->addWidget(passwordInput);

  // Enter Button
  loginButton = new QPushButton("Enter", this);
  loginButton->setStyleSheet("background-color: #5c6894; border: none; padding: 10px; margin: 5px;");
  loginButton->hide();
  layout->addWidget(loginButton);

  connect(loginButton, &QPushButton::clicked, this, &LoginScreen::onLoginClicked);
}

void LoginScreen::animateTitle()
{
  // Create opacity effect
  QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
  titleLabel->setGraphicsEffect(effect);

  // Create opacity animation
  QPropertyAnimation *opacityAnimation = new QPropertyAnimation(effect, "opacity");
  opacityAnimation->setDuration(1000);
  opacityAnimation->setStartValue(0.0);
  opacityAnimation->setEndValue(1.0);
  opacityAnimation->setEasingCurve(QEasingCurve::InOutQuad);

  // Start the animation
  opacityAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void LoginScreen::showInputFields()
{
  usernameInput->show();
  passwordInput->show();
  loginButton->show();

  // Animate fade-in for input fields and button
  QGraphicsOpacityEffect *usernameEffect = new QGraphicsOpacityEffect(usernameInput);
  QGraphicsOpacityEffect *passwordEffect = new QGraphicsOpacityEffect(passwordInput);
  QGraphicsOpacityEffect *buttonEffect = new QGraphicsOpacityEffect(loginButton);

  usernameInput->setGraphicsEffect(usernameEffect);
  passwordInput->setGraphicsEffect(passwordEffect);
  loginButton->setGraphicsEffect(buttonEffect);

  QPropertyAnimation *usernameAnimation = new QPropertyAnimation(usernameEffect, "opacity");
  QPropertyAnimation *passwordAnimation = new QPropertyAnimation(passwordEffect, "opacity");
  QPropertyAnimation *buttonAnimation = new QPropertyAnimation(buttonEffect, "opacity");

  for (QPropertyAnimation *animation : {usernameAnimation, passwordAnimation, buttonAnimation}) {
    animation->setDuration(1000);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
  }
}

void LoginScreen::onLoginClicked()
{
  // Here you would typically validate the username and password
  // For this example, we'll just emit the loginSuccessful signal
  emit loginSuccessful();
}
