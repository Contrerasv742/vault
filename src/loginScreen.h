// loginscreen.h
#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPropertyAnimation>

class LoginScreen : public QWidget
{
    Q_OBJECT

public:
    explicit LoginScreen(QWidget *parent = nullptr);

signals:
    void loginSuccessful();

private slots:
    void onLoginClicked();
    void showInputFields();

private:
    QLabel *titleLabel;
    QLineEdit *usernameInput;
    QLineEdit *passwordInput;
    QPushButton *loginButton;
    QVBoxLayout *layout;

    void setupUI();
    void animateTitle();
};

#endif //LOGINSCREEN_H
