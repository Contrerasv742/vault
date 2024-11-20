#include "loginScreen.h"

#include <QApplication>
#include <QDir>
#include <QGraphicsOpacityEffect>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QSpacerItem>
#include <QTimer>
#include <QVBoxLayout>

LoginScreen::LoginScreen(QWidget *parent) : QWidget(parent) {
    setupUI();
    QTimer::singleShot(100, this, &LoginScreen::animateTitle);
    QTimer::singleShot(3000, this, &LoginScreen::showInputFields);
}

void LoginScreen::setupUI() {
    setStyleSheet("background-color: #323547; color: white;");

    // Create a main layout for the LoginScreen
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addSpacerItem(
            new QSpacerItem(0, 100, QSizePolicy::Minimum, QSizePolicy::Fixed));

    // Title
    titleLabel = new QLabel("VAULT⋅⋅⋅", this);
    titleLabel->setStyleSheet(
            "font-size: 48px; font-weight: bold; background-color: none;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);
    mainLayout->addSpacerItem(
            new QSpacerItem(0, 100, QSizePolicy::Minimum, QSizePolicy::Fixed));

    // Create a container widget for input fields and button
    inputContainer = new QWidget(this);
    inputContainer->setStyleSheet("background-color: none;");
    inputContainer->hide();

    QVBoxLayout *inputLayout = new QVBoxLayout(inputContainer);
    inputLayout->setSpacing(20);

    // Username Box
    usernameInput = new QLineEdit(inputContainer);
    usernameInput->setPlaceholderText("Username");
    usernameInput->setFixedSize(400, 50);
    usernameInput->setStyleSheet(
            "background-color: #323547; border: none; padding: 10px; "
            "border-radius: "
            "5px;");
    inputLayout->addWidget(usernameInput, 0, Qt::AlignCenter);

    // Password Box with Eye Icon
    QHBoxLayout *passwordLayout = new QHBoxLayout();
    passwordLayout->setSpacing(0);

    passwordInput = new QLineEdit(inputContainer);
    passwordInput->setPlaceholderText("Password");
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setFixedSize(350, 50);
    passwordInput->setStyleSheet(
            "QLineEdit {"
            "   background-color: #323547;"
            "   border: none;"
            "   padding: 10px;"
            "   border-top-left-radius: 5px;"
            "   border-bottom-left-radius: 5px;"
            "   border-top-right-radius: 0px;"
            "   border-bottom-right-radius: 0px;"
            "}");

    togglePasswordButton = new QPushButton(inputContainer);
    togglePasswordButton->setFixedSize(50, 50);
    togglePasswordButton->setStyleSheet(
            "QPushButton {"
            "   background-color: #323547;"
            "   border: none;"
            "   border-top-left-radius: 0px;"
            "   border-bottom-left-radius: 0px;"
            "   border-top-right-radius: 5px;"
            "   border-bottom-right-radius: 5px;"
            "   padding: 5px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #3E4257;"
            "}"
            "QPushButton:pressed {"
            "   background-color: #3E4257;"
            "}"
            "QPushButton:focus {"
            "   outline: none;"
            "}");
    togglePasswordButton->setFocusPolicy(Qt::NoFocus);

    // Set the initial icon
    QIcon closedEyeIcon = this->getIconFromPath("eye-closed.png");
    if (closedEyeIcon.isNull()) {
        qWarning() << "Failed to load closed eye icon";
        togglePasswordButton->setText(
                "👁");  // Fallback to unicode eye symbol
    } else {
        togglePasswordButton->setIcon(closedEyeIcon);
    }
    togglePasswordButton->setIconSize(QSize(20, 20));
    togglePasswordButton->setAttribute(Qt::WA_OpaquePaintEvent);

    passwordLayout->addWidget(passwordInput);
    passwordLayout->addWidget(togglePasswordButton);

    inputLayout->addLayout(passwordLayout, 0);

    // Login Button
    loginButton = new QPushButton("Enter", inputContainer);
    loginButton->setFixedSize(400, 50);
    loginButton->setStyleSheet(
            "background-color: #5c6894; border: none; padding: 10px; "
            "border-radius: "
            "5px;");
    inputLayout->addWidget(loginButton, 0, Qt::AlignCenter);

    // Add input container to main layout
    mainLayout->addWidget(inputContainer, 0, Qt::AlignHCenter);

    // Add a stretching spacer at the bottom to push everything up
    mainLayout->addStretch();

    connect(loginButton, &QPushButton::clicked, this,
            &LoginScreen::onLoginClicked);
    connect(togglePasswordButton, &QPushButton::clicked, this,
            &LoginScreen::togglePasswordVisibility);
}

void LoginScreen::togglePasswordVisibility() {
    if (passwordInput->echoMode() == QLineEdit::Password) {
        passwordInput->setEchoMode(QLineEdit::Normal);
        QIcon openEyeIcon = this->getIconFromPath("eye-open.png");
        if (!openEyeIcon.isNull()) {
            togglePasswordButton->setIcon(openEyeIcon);
        } else {
            togglePasswordButton->setText(
                    "👁");  // Fallback to unicode eye symbol
        }
    } else {
        passwordInput->setEchoMode(QLineEdit::Password);
        QIcon closedEyeIcon = this->getIconFromPath("eye-closed.png");
        if (!closedEyeIcon.isNull()) {
            togglePasswordButton->setIcon(closedEyeIcon);
        } else {
            togglePasswordButton->setText(
                    "👁");  // Fallback to unicode eye symbol
        }
    }
}

QIcon LoginScreen::getIconFromPath(const QString &iconName) {
    QStringList searchPaths = {
            QDir::currentPath() + "/icons",
            QApplication::applicationDirPath() + "/icons",
            QDir::currentPath() + "/../icons",
            QApplication::applicationDirPath() + "/../icons"};

    for (const QString &path : searchPaths) {
        QString fullPath = path + "/" + iconName;
        if (QFile::exists(fullPath)) {
            return QIcon(fullPath);
        }
    }

    qWarning() << "Icon not found:" << iconName;
    return QIcon();
}

void LoginScreen::animateTitle() {
    // Create opacity effect
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(titleLabel);
    titleLabel->setGraphicsEffect(effect);

    // Create opacity animation
    QPropertyAnimation *opacityAnimation =
            new QPropertyAnimation(effect, "opacity");
    opacityAnimation->setDuration(1000);
    opacityAnimation->setStartValue(0.0);
    opacityAnimation->setEndValue(1.0);
    opacityAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    // Start the animation
    opacityAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void LoginScreen::showInputFields() {
    // Make sure the input fields and button are visible
    usernameInput->show();
    passwordInput->show();
    loginButton->show();

    // Create opacity effect for the input container
    QGraphicsOpacityEffect *containerEffect =
            new QGraphicsOpacityEffect(inputContainer);
    inputContainer->setGraphicsEffect(containerEffect);

    // Create opacity animation
    QPropertyAnimation *animation =
            new QPropertyAnimation(containerEffect, "opacity");
    animation->setDuration(1000);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::InOutQuad);

    // Connect animation finished signal to cleanup slot
    connect(animation, &QPropertyAnimation::finished, this,
            &LoginScreen::cleanupAnimation);

    // Show the input container and start the animation
    inputContainer->show();
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void LoginScreen::cleanupAnimation() {
    // Remove the graphics effect after animation
    inputContainer->setGraphicsEffect(nullptr);
}

void LoginScreen::onLoginClicked() {
    // Here you would typically validate the username and password
    // For this example, we'll just emit the loginSuccessful signal
    emit loginSuccessful();
}
