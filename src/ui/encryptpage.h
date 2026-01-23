// encryptpage.h
#ifndef ENCRYPTPAGE_H
#define ENCRYPTPAGE_H

#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QTextEdit>
#include <QWidget>

class EncryptPage : public QWidget {
    Q_OBJECT

public:
    explicit EncryptPage(QWidget *parent = nullptr);

private slots:
    void updatePasswordLength(int value);
    void generatePassword();
    void encryptText();
    void updateStrengthIndicator();

private:
    QLabel *titleLabel;
    QLabel *passwordLabel;
    QLabel *strengthLabel;
    QSlider *passwordLengthSlider;
    QLabel *passwordLengthLabel;
    QComboBox *encryptionAlgorithmComboBox;
    QTextEdit *textToEncrypt;
    QPushButton *encryptButton;

    void setupUI();
    QString generateRandomPassword(int length);
    QString assessPasswordStrength(int length);
};

#endif  // ENCRYPTPAGE_H
