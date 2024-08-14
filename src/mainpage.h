#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QScrollArea>

class MainPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);

private:
    void setupLeftContainer();
    void setupRightContainer();
    void createPasswordCard(const QString &companyName, const QString &username);

    QWidget *leftContainer;
    QWidget *rightContainer;
    QLineEdit *searchBar;
    QComboBox *optionsDropdown;
    QScrollArea *favoritesScrollArea;
    QScrollArea *allPasswordsScrollArea;
};
#endif // MAINPAGE_H
