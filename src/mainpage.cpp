#include "mainpage.h"
#include <QIcon>
#include <QDebug>
#include <QFile>
#include <QPainter>
#include <QPixmap>

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
  leftLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  leftLayout->setContentsMargins(20, 20, 20, 20);
  leftLayout->setSpacing(10);

  // App name
  QLabel *appNameLabel = new QLabel("VAULT", leftContainer);
  appNameLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #FFFFFF;");
  leftLayout->addWidget(appNameLabel);

  // Search bar
  searchBar = new QLineEdit(leftContainer);
  searchBar->setPlaceholderText("Search");
  searchBar->setStyleSheet(
    "QLineEdit {"
    "   background-color: #2C2F33;"
    "   color: #FFFFFF;"
    "   border: none;"
    "   padding: 5px;"
    "   padding-left: 30px;"  // Make room for the icon
    "   border-radius: 15px;"
    "   min-height: 30px;"
    "}"
    "QLineEdit:focus {"
    "   outline: none;"
    "   border: 2px solid #DC8A78;"
    "}"
  );

  // Add search icon
  QAction *searchAction = new QAction(searchBar);
  QIcon searchIcon("../icons/search.png");  // Make sure you have this icon
  searchAction->setIcon(searchIcon);
  searchBar->addAction(searchAction, QLineEdit::LeadingPosition);

  leftLayout->addWidget(searchBar);  

  // Options button
  optionsButton = createStyledButton("Options", "options.png", true);  // The false parameter hides the text
  optionsButton->setStyleSheet(optionsButton->styleSheet() + "QPushButton { padding-right: 15px; }");
  leftLayout->addWidget(optionsButton);

  // Options widget (initially hidden)
  optionsWidget = new QWidget(leftContainer);
  QVBoxLayout *optionsLayout = new QVBoxLayout(optionsWidget);
  optionsLayout->setAlignment(Qt::AlignLeft);
  optionsLayout->setContentsMargins(0, 0, 0, 0);
  optionsLayout->setSpacing(10);  // Increased from 5

  QStringList options = {"Decrypt", "Encrypt", "Passwords", "Secure Notes"};
  QStringList icons = {"open-lock.png", "closed-lock.png", "password.png", "notepad.png"};
  for (int i = 0; i < options.size(); ++i) {
    QPushButton *optionButton = createStyledButton(options[i], icons[i]);
    optionsLayout->addWidget(optionButton);
  }

  optionsWidget->setLayout(optionsLayout);
  optionsWidget->hide();
  leftLayout->addWidget(optionsWidget);

  leftLayout->addStretch();

  connect(optionsButton, &QPushButton::clicked, this, &MainPage::toggleOptions);

  qDebug() << "setupLeftContainer finished";
}

QPushButton* MainPage::createStyledButton(const QString &text, const QString &iconName, bool showText) {
  QPushButton *button = new QPushButton();
  button->setStyleSheet(QString(
    "QPushButton {"
    "   background-color: transparent;"
    "   color: #FFFFFF;"
    "   border: 2px solid #FFFFFF;"
    "   border-radius: 20px;"
    "   padding: 10px;"
    "   text-align: left;"
    "   font-weight: bold;"
    "   min-width: 150px;"
    "   min-height: 30px;"
    "}"
    "QPushButton:hover {"
    "   background-color: #DC8A78;"
    "}"
  ));

  // Create a horizontal layout for the button
  QHBoxLayout *buttonLayout = new QHBoxLayout(button);
  buttonLayout->setContentsMargins(10, 10, 10, 10);  // Increased from 5, 5, 5, 5
  buttonLayout->setSpacing(15);  // Increased from 10

  // Add the icon
  QLabel *iconLabel = new QLabel(button);
  iconLabel->setFixedSize(30, 30);  // Increased from 20, 20
  iconLabel->setStyleSheet("QLabel { background-color: none; }");
  QString iconPath = QString("../icons/%1").arg(iconName);
  if (QFile::exists(iconPath)) {
    QPixmap originalPixmap(iconPath);
    QPixmap scaledPixmap = originalPixmap.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Create a new transparent pixmap
    QPixmap transparentPixmap(scaledPixmap.size());
    transparentPixmap.fill(Qt::transparent);

    // Paint the scaled pixmap onto the transparent pixmap
    QPainter painter(&transparentPixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawPixmap(0, 0, scaledPixmap);
    painter.end();

    iconLabel->setPixmap(transparentPixmap);
  } else {
    qWarning() << "Icon not found:" << iconPath;
    iconLabel->hide(); // Hide the label if icon is not found
  }
  buttonLayout->addWidget(iconLabel);

  // Add the text label for the button
  if (showText) {
    QLabel *textLabel = new QLabel(text, button);
    textLabel->setStyleSheet("color: #FFFFFF; font-weight: bold; background-color: none; padding-left: 20px;");
    buttonLayout->addWidget(textLabel);
  }

  buttonLayout->addStretch();

  return button;
}

void MainPage::toggleOptions()
{
  if (optionsWidget->isVisible()) {
    optionsWidget->hide();
  } else {
    optionsWidget->show();
  }
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
