#include "app.h"
#include <QVBoxLayout>
#include <QDebug>

EncryptionApp::EncryptionApp(QWidget *parent) : QMainWindow(parent) {
    qDebug() << "EncryptionApp constructor started";
    setWindowTitle("VAULT - Password Manager");

    loginScreen = new LoginScreen(this);
    if (!loginScreen) {
        qCritical() << "Failed to create LoginScreen";
        return;
    }
    setCentralWidget(loginScreen);

    connect(loginScreen, &LoginScreen::loginSuccessful, this, &EncryptionApp::onLoginSuccessful);

    mainPage = new MainPage(this);
    if (!mainPage) {
        qCritical() << "Failed to create MainPage";
        return;
    }
    mainPage->hide();

    resize(2000, 1000);
    qDebug() << "EncryptionApp constructor finished";
}

void EncryptionApp::onLoginSuccessful() {
    qDebug() << "onLoginSuccessful called";
    if (!loginScreen) {
        qCritical() << "loginScreen is null in onLoginSuccessful";
        return;
    }
    loginScreen->hide();

    if (!mainPage) {
        qCritical() << "mainPage is null in onLoginSuccessful";
        return;
    }
    setCentralWidget(mainPage);
    mainPage->show();
    qDebug() << "onLoginSuccessful finished";
}

EncryptionApp::~EncryptionApp() {
    qDebug() << "EncryptionApp destructor called";
}
