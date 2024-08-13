#ifndef APP_H
#define APP_H

#include <QMainWindow>

class QComboBox;
class QLineEdit;
class QTextEdit;

class EncryptionApp : public QMainWindow {
  // Macro from the core QT header file
    Q_OBJECT

public:
    explicit EncryptionApp(QWidget *parent = nullptr);
    virtual ~EncryptionApp();

private slots:
    void processText();

private:
    QComboBox *modeComboBox;
    QComboBox *cipherComboBox;
    QLineEdit *inputText;
    QTextEdit *outputText;
};

#endif // APP_H
