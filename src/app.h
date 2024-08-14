#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <QProxyStyle>
#include <QStyleOption>
#include "loginScreen.h"
#include "mainpage.h"

class QComboBox;
class QLineEdit;
class QTextEdit;

class ComboBoxStyle : public QProxyStyle {
public:
    int styleHint(StyleHint hint, const QStyleOption* option = 0, const QWidget* widget = 0, QStyleHintReturn* returnData = 0) const override
    {
        if (hint == QStyle::SH_ComboBox_Popup)
            return 0;
        return QProxyStyle::styleHint(hint, option, widget, returnData);
    }
};

class EncryptionApp : public QMainWindow {
    Q_OBJECT

public:
    explicit EncryptionApp(QWidget *parent = nullptr);
    virtual ~EncryptionApp();

private slots:
    void onLoginSuccessful();

private:
    LoginScreen *loginScreen;
    MainPage *mainPage;
};

#endif // APP_H
