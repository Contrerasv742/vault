#include "mainpage.h"
#include <QIcon>
#include <QDebug>

MainPage::MainPage(QWidget *parent) : QWidget(parent), 
    favoritesScrollArea(nullptr), allPasswordsScrollArea(nullptr)
{
    qDebug() << "MainPage constructor started";
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    
    leftContainer = new QWidget(this);
    rightContainer = new QWidget(this);
    
    if (!leftContainer || !rightContainer) {
        qCritical() << "Failed to create containers in MainPage";
        return;
    }
    
    mainLayout->addWidget(leftContainer, 1);
    mainLayout->addWidget(rightContainer, 2);
    
    setupLeftContainer();
    setupRightContainer();
    
    setLayout(mainLayout);
    qDebug() << "MainPage constructor finished";
}

void MainPage::setupLeftContainer()
{
    qDebug() << "setupLeftContainer started";
    if (!leftContainer) {
        qCritical() << "leftContainer is null in setupLeftContainer";
        return;
    }
    
    QVBoxLayout *leftLayout = new QVBoxLayout(leftContainer);
    
    // App name
    QLabel *appNameLabel = new QLabel("VAULT", leftContainer);
    appNameLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    leftLayout->addWidget(appNameLabel);
    
    // Search bar
    searchBar = new QLineEdit(leftContainer);
    searchBar->setPlaceholderText("Search");
    leftLayout->addWidget(searchBar);
    
    // Options dropdown
    optionsDropdown = new QComboBox(leftContainer);
    optionsDropdown->addItems({"Decrypt", "Encrypt", "Passwords", "Secure Notes"});
    leftLayout->addWidget(optionsDropdown);
    
    leftLayout->addStretch();

    qDebug() << "setupLeftContainer finished";
}

void MainPage::createPasswordCard(const QString &companyName, const QString &username)
{
    qDebug() << "createPasswordCard started for" << companyName;
    QWidget *card = new QWidget(this);
    if (!card) {
        qCritical() << "Failed to create card widget";
        return;
    }
    card->setObjectName("Card_" + companyName);  // Set a unique object name for debugging
    card->setStyleSheet("background-color: #323547; border-radius: 5px; padding: 10px;");
    
    QHBoxLayout *cardLayout = new QHBoxLayout(card);
    if (!cardLayout) {
        qCritical() << "Failed to create card layout for" << companyName;
        return;
    }
    
    // Company logo (placeholder)
    QLabel *logoLabel = new QLabel(card);
    if (!logoLabel) {
        qCritical() << "Failed to create logo label for" << companyName;
        return;
    }
    QIcon icon = QIcon::fromTheme("application-x-executable");
    if (icon.isNull()) {
        qWarning() << "Failed to load icon for" << companyName;
        logoLabel->setText("Logo");
    } else {
        logoLabel->setPixmap(icon.pixmap(32, 32));
    }
    cardLayout->addWidget(logoLabel);
    
    // Company name and username
    QVBoxLayout *infoLayout = new QVBoxLayout();
    QLabel *companyLabel = new QLabel(companyName, card);
    QLabel *usernameLabel = new QLabel(username, card);
    if (!companyLabel || !usernameLabel) {
        qCritical() << "Failed to create info labels for" << companyName;
        return;
    }
    infoLayout->addWidget(companyLabel);
    infoLayout->addWidget(usernameLabel);
    cardLayout->addLayout(infoLayout);
    
    // Copy password button
    QPushButton *copyButton = new QPushButton("Copy", card);
    if (!copyButton) {
        qCritical() << "Failed to create copy button for" << companyName;
        return;
    }
    cardLayout->addWidget(copyButton);
    
    qDebug() << "Adding card to layouts for" << companyName;
    
    // Add the card to both favorites and all passwords layouts
    if (favoritesScrollArea && favoritesScrollArea->widget() && favoritesScrollArea->widget()->layout()) {
        QBoxLayout* favLayout = qobject_cast<QBoxLayout*>(favoritesScrollArea->widget()->layout());
        if (favLayout) {
            favLayout->addWidget(card);
            qDebug() << "Added card to favorites for" << companyName;
        } else {
            qWarning() << "Failed to cast favorites layout for" << companyName;
        }
    } else {
        qWarning() << "Favorites scroll area or its widget or layout is null for" << companyName;
    }
    
    if (allPasswordsScrollArea && allPasswordsScrollArea->widget() && allPasswordsScrollArea->widget()->layout()) {
        QBoxLayout* allLayout = qobject_cast<QBoxLayout*>(allPasswordsScrollArea->widget()->layout());
        if (allLayout) {
            allLayout->addWidget(card);
            qDebug() << "Added card to all passwords for" << companyName;
        } else {
            qWarning() << "Failed to cast all passwords layout for" << companyName;
        }
    } else {
        qWarning() << "All passwords scroll area or its widget or layout is null for" << companyName;
    }
    
    qDebug() << "createPasswordCard finished for" << companyName;
}

void MainPage::setupRightContainer()
{
    qDebug() << "setupRightContainer started";
    if (!rightContainer) {
        qCritical() << "rightContainer is null in setupRightContainer";
        return;
    }
    QVBoxLayout *rightLayout = new QVBoxLayout(rightContainer);
    
    // Favorites section
    QLabel *favoritesLabel = new QLabel("Favorites", rightContainer);
    favoritesLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
    rightLayout->addWidget(favoritesLabel);
    
    favoritesScrollArea = new QScrollArea(rightContainer);
    QWidget *favoritesWidget = new QWidget(favoritesScrollArea);
    QVBoxLayout *favoritesLayout = new QVBoxLayout(favoritesWidget);
    
    favoritesWidget->setLayout(favoritesLayout);
    favoritesScrollArea->setWidget(favoritesWidget);
    favoritesScrollArea->setWidgetResizable(true);
    rightLayout->addWidget(favoritesScrollArea);
    
    // All passwords section
    QLabel *allPasswordsLabel = new QLabel("All Passwords", rightContainer);
    allPasswordsLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
    rightLayout->addWidget(allPasswordsLabel);
    
    allPasswordsScrollArea = new QScrollArea(rightContainer);
    QWidget *allPasswordsWidget = new QWidget(allPasswordsScrollArea);
    QVBoxLayout *allPasswordsLayout = new QVBoxLayout(allPasswordsWidget);
    
    allPasswordsWidget->setLayout(allPasswordsLayout);
    allPasswordsScrollArea->setWidget(allPasswordsWidget);
    allPasswordsScrollArea->setWidgetResizable(true);
    rightLayout->addWidget(allPasswordsScrollArea);
    
    // Add some example password cards
    qDebug() << "Creating example password cards";
    createPasswordCard("Google", "user@gmail.com");
    createPasswordCard("Facebook", "user@facebook.com");
    createPasswordCard("Amazon", "user@amazon.com");
    createPasswordCard("Twitter", "user@twitter.com");
    createPasswordCard("LinkedIn", "user@linkedin.com");
    
    qDebug() << "setupRightContainer finished";
}
