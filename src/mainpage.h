#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

#include "encryptpage.h"

class MainPage : public QWidget {
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);

private slots:
    void toggleOptions();
    void toggleFavorite(const QString &companyName);
    void showEncryptView();
    void showPasswordView();

private:
    void setupLeftContainer();
    void setupRightContainer();
    void createPasswordCard(const QString &companyName,
                            const QString &username);
    void reorderCards(QGridLayout *layout);
    QPushButton *createStyledButton(const QString &text,
                                    const QString &iconName,
                                    bool showText = true);
    void filterPasswords(const QString &searchText);
    void setupEncryptPage();
    void setupPasswordView();
    void setupEncryptView();

    QWidget *leftContainer;
    QWidget *rightContainer;
    QLineEdit *searchBar;
    QPushButton *optionsButton;
    QWidget *optionsWidget;
    QScrollArea *favoritesScrollArea;
    QScrollArea *allPasswordsScrollArea;
    EncryptPage *encryptPage;
    QWidget *passwordView;
    QWidget *encryptView;

    int favoritesCardCount;
    int allPasswordsCardCount;
};

#endif  // MAINPAGE_H
