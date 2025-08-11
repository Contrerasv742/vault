#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QLabel>
#include <QLineEdit>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class LoginScreen : public QWidget {
    Q_OBJECT

    public:
        explicit LoginScreen(QWidget *parent = nullptr);

signals:
        void loginSuccessful();

        private slots:
            void onLoginClicked();
        void showInputFields();
        void cleanupAnimation();
        void togglePasswordVisibility();
        QIcon getIconFromPath(const QString &iconName);

    private:
        QLabel *titleLabel;
        QWidget *inputContainer;
        QLineEdit *usernameInput;
        QLineEdit *passwordInput;
        QPushButton *loginButton;
        QPushButton *togglePasswordButton;

        void setupUI();
        void animateTitle();
};

#endif  // LOGINSCREEN_H
