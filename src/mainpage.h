#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>

class MainPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);

private slots:
    void toggleOptions();

private:
    void setupLeftContainer();
    void setupRightContainer();
    void createPasswordCard(const QString &companyName, const QString &username);
    QPushButton* createStyledButton(const QString &text, const QString &iconName, bool showText = true);

    QWidget *leftContainer;
    QWidget *rightContainer;
    QLineEdit *searchBar;
    QPushButton *optionsButton;
    QWidget *optionsWidget;
    QScrollArea *favoritesScrollArea;
    QScrollArea *allPasswordsScrollArea;
};

#endif // MAINPAGE_H
