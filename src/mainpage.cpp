#include "mainpage.h"
#include <algorithm>
#include <QIcon>
#include <QDebug>
#include <QFile>
#include <QPainter>
#include <QPixmap>
#include <QFrame>
#include <QGridLayout>
#include <QScrollArea>
#include <qnamespace.h>
#include <QRegularExpression>

MainPage::MainPage(QWidget *parent) : QWidget(parent), 
  favoritesScrollArea(nullptr), allPasswordsScrollArea(nullptr),
  favoritesCardCount(0), allPasswordsCardCount(0)
{
  qDebug() << "MainPage constructor started";
  QHBoxLayout *mainLayout = new QHBoxLayout(this);
  mainLayout->setSpacing(0);
  mainLayout->setContentsMargins(0, 0, 0, 0);

  leftContainer = new QWidget(this);
  rightContainer = new QWidget(this);

  if (!leftContainer || !rightContainer) {
    qCritical() << "Failed to create containers in MainPage";
    return;
  }

  // Create a vertical separator
  QFrame *separator = new QFrame(this);
  separator->setFrameShape(QFrame::VLine);
  separator->setStyleSheet("QFrame { background-color: white; margin: 10px 0; opacity: 0.5}");

  mainLayout->addWidget(leftContainer, 1);
  mainLayout->addWidget(separator);
  mainLayout->addWidget(rightContainer, 2);

  // Setting up containers
  setupLeftContainer();
  setupRightContainer();
  setupPasswordView();
  setupEncryptView();

  // Initially show the password view
  showPasswordView();

  setLayout(mainLayout);
  qDebug() << "MainPage constructor finished";
}

void MainPage::setupPasswordView()
{
  passwordView = new QWidget(this);
  QVBoxLayout *passwordLayout = new QVBoxLayout(passwordView);

  // Favorites section
  QLabel *favoritesLabel = new QLabel("Favorites", rightContainer);
  favoritesLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #FFFFFF;");
  passwordLayout->addWidget(favoritesLabel);

  favoritesScrollArea = new QScrollArea(rightContainer);
  favoritesScrollArea->setWidgetResizable(true);
  favoritesScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  favoritesScrollArea->setStyleSheet("QScrollArea { border: none; background-color: transparent; }");

  QWidget *favoritesWidget = new QWidget(favoritesScrollArea);
  favoritesWidget->setStyleSheet("background-color: transparent;");
  QGridLayout *favoritesLayout = new QGridLayout(favoritesWidget);
  favoritesLayout->setSpacing(10);
  favoritesLayout->setColumnStretch(0, 1);
  favoritesLayout->setColumnStretch(1, 1);
  favoritesLayout->setColumnStretch(2, 1);
  favoritesLayout->setAlignment(Qt::AlignTop);

  favoritesScrollArea->setWidget(favoritesWidget);
  passwordLayout->addWidget(favoritesScrollArea);

  // All passwords section
  QLabel *allPasswordsLabel = new QLabel("All Passwords", rightContainer);
  allPasswordsLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #FFFFFF;");
  passwordLayout->addWidget(allPasswordsLabel);

  allPasswordsScrollArea = new QScrollArea(rightContainer);
  allPasswordsScrollArea->setWidgetResizable(true);
  allPasswordsScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  allPasswordsScrollArea->setStyleSheet("QScrollArea { border: none; background-color: transparent; }");

  QWidget *allPasswordsWidget = new QWidget(allPasswordsScrollArea);
  allPasswordsWidget->setStyleSheet("background-color: transparent;");
  QGridLayout *allPasswordsLayout = new QGridLayout(allPasswordsWidget);
  allPasswordsLayout->setSpacing(10);
  allPasswordsLayout->setColumnStretch(0, 1);
  allPasswordsLayout->setColumnStretch(1, 1);
  allPasswordsLayout->setColumnStretch(2, 1);
  allPasswordsLayout->setAlignment(Qt::AlignTop);

  allPasswordsScrollArea->setWidget(allPasswordsWidget);
  passwordLayout->addWidget(allPasswordsScrollArea);

  // Add some example password cards
  qDebug() << "Creating example password cards";
  createPasswordCard("Google", "user@gmail.com");
  createPasswordCard("Facebook", "user@facebook.com");
  createPasswordCard("Amazon", "user@amazon.com");
  createPasswordCard("Twitter", "user@twitter.com");
  createPasswordCard("LinkedIn", "user@linkedin.com");

  // Add passwordView to rightContainer
  QVBoxLayout *rightLayout = qobject_cast<QVBoxLayout*>(rightContainer->layout());
  if (rightLayout) {
    rightLayout->addWidget(passwordView);
  }
}

void MainPage::setupEncryptView()
{
    encryptView = new QWidget(rightContainer);
    QVBoxLayout *encryptLayout = new QVBoxLayout(encryptView);
    
    encryptPage = new EncryptPage(encryptView);
    encryptLayout->addWidget(encryptPage);

    // Add encryptView to rightContainer
    QVBoxLayout *rightLayout = qobject_cast<QVBoxLayout*>(rightContainer->layout());
    if (rightLayout) {
        rightLayout->addWidget(encryptView);
    }
    encryptView->hide();  // Initially hidden
}

void MainPage::showEncryptView() {
    if (passwordView) passwordView->hide();
    if (encryptView) encryptView->show();
}

void MainPage::showPasswordView()
{
    if (encryptView) encryptView->hide();
    if (passwordView) passwordView->show();
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
  connect(searchBar, &QLineEdit::textChanged, this, &MainPage::filterPasswords);

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

        if (options[i] == "Encrypt") {
            connect(optionButton, &QPushButton::clicked, this, &MainPage::showEncryptView);
        } else if (options[i] == "Passwords") {
            connect(optionButton, &QPushButton::clicked, this, &MainPage::showPasswordView);
        }
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
  rightLayout->setContentsMargins(20, 20, 20, 20);
  rightLayout->setSpacing(20);

  setupEncryptPage();
  rightLayout->addWidget(encryptPage);

  qDebug() << "setupRightContainer finished";
}

void MainPage::createPasswordCard(const QString &companyName, const QString &username)
{
  if (companyName.isEmpty()) {
    qWarning() << "Attempted to create a password card with an empty company name. Skipping.";
    return;
  }

  qDebug() << "createPasswordCard started for" << companyName;
  QWidget *card = new QWidget(this);
  if (!card) {
    qCritical() << "Failed to create card widget";
    return;
  }
  card->setObjectName("Card_" + companyName);  // Set a unique object name for debugging
  card->setStyleSheet("background-color: #323547; border-radius: 5px; padding: 10px;");
  card->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  card->setFixedHeight(80);  // Adjust this value as needed

  QHBoxLayout *cardLayout = new QHBoxLayout(card);
  cardLayout->setContentsMargins(10, 10, 10, 10);
  cardLayout->setSpacing(10);

  // Company logo (placeholder)
  QLabel *logoLabel = new QLabel(card);
  logoLabel->setFixedSize(32, 32);
  QString logoPath = QString("../icons/%1.png").arg(companyName.toLower());
  if (QFile::exists(logoPath)) {
    QPixmap originalPixmap(logoPath);
    QPixmap scaledPixmap = originalPixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Create a new transparent pixmap
    QPixmap finalPixmap(32, 32);
    finalPixmap.fill(Qt::transparent);

    // Paint the scaled pixmap centered on the transparent pixmap
    QPainter painter(&finalPixmap);
    painter.drawPixmap((32 - scaledPixmap.width())/2, (32 - scaledPixmap.height())/2, scaledPixmap);

    logoLabel->setPixmap(finalPixmap);
  } else {
    qWarning() << "Failed to load logo for" << companyName;
    logoLabel->setText(companyName.left(1));
    logoLabel->setStyleSheet("background-color: #DC8A78; color: white; border-radius: 16px; font-weight: bold; qproperty-alignment: AlignCenter;");
  }
  cardLayout->addWidget(logoLabel);

  // Company name and username
  QVBoxLayout *infoLayout = new QVBoxLayout();
  QLabel *companyLabel = new QLabel(companyName, card);
  QLabel *usernameLabel = new QLabel(username, card);
  companyLabel->setStyleSheet("color: #FFFFFF; font-weight: bold;");
  usernameLabel->setStyleSheet("color: #AAAAAA;");
  companyLabel->setFixedHeight(40);
  usernameLabel->setFixedHeight(40);
  infoLayout->addWidget(companyLabel);
  infoLayout->addWidget(usernameLabel);
  cardLayout->addLayout(infoLayout, 1);

  // Copy password button
  QPushButton *copyButton = new QPushButton("Copy", card);
  copyButton->setStyleSheet("background-color: #DC8A78; color: #FFFFFF; border: none; padding: 5px 10px; border-radius: 3px;");
  copyButton->setFixedSize(60, 30);
  cardLayout->addWidget(copyButton);

  // Add the card to both favorites and all passwords layouts
  if (favoritesScrollArea && favoritesScrollArea->widget()) {
    QGridLayout* favLayout = qobject_cast<QGridLayout*>(favoritesScrollArea->widget()->layout());
    if (favLayout) {
      favLayout->addWidget(card);
      reorderCards(favLayout);
      favoritesCardCount++;
      qDebug() << "Added card to favorites for" << companyName;
    }
  }

  if (allPasswordsScrollArea && allPasswordsScrollArea->widget()) {
    QGridLayout* allLayout = qobject_cast<QGridLayout*>(allPasswordsScrollArea->widget()->layout());
    if (allLayout) {
      allLayout->addWidget(card);
      reorderCards(allLayout);
      allPasswordsCardCount++;
      qDebug() << "Added card to all passwords for" << companyName;
    }
  }

  // Add favorite toggle button
  QPushButton *favoriteButton = new QPushButton(card);
  favoriteButton->setObjectName("favoriteButton");  // Set an object name for easy finding
  favoriteButton->setIcon(QIcon("../icons/empty-star.png"));  // Start with empty star
  favoriteButton->setStyleSheet("background-color: transparent; border: none;");
  favoriteButton->setFixedSize(24, 24);
  cardLayout->addWidget(favoriteButton);

  // Set initial favorite status
  card->setProperty("isFavorite", false);

  connect(favoriteButton, &QPushButton::clicked, this, [this, companyName]() {
    toggleFavorite(companyName);
  });

  qDebug() << "createPasswordCard finished for" << companyName;
}

void MainPage::reorderCards(QGridLayout *layout)
{
    if (!layout) {
        qDebug() << "Layout is null, exiting reorderCards";
        return;
    }

    qDebug() << "Starting reorderCards";

    // Collect all widgets from the layout
    QList<QPair<QWidget*, QString>> cards;
    for (int i = 0; i < layout->count(); ++i) {
        QLayoutItem *item = layout->itemAt(i);
        if (QWidget *widget = item->widget()) {
            QString companyName;
            for (QLabel *label : widget->findChildren<QLabel*>()) {
                if (!label->text().contains('@')) {
                    companyName = label->text();
                    break;
                }
            }
            cards.append(qMakePair(widget, companyName));
            qDebug() << "Collected card with company name:" << companyName;
        }
    }

    qDebug() << "Collected" << cards.size() << "cards";

    // Sort cards alphabetically based on company name, with empty names at the end
    std::stable_sort(cards.begin(), cards.end(), 
        [](const QPair<QWidget*, QString> &a, const QPair<QWidget*, QString> &b) {
            if (a.second.isEmpty() && b.second.isEmpty()) return false;
            if (a.second.isEmpty()) return false;
            if (b.second.isEmpty()) return true;
            return a.second.compare(b.second, Qt::CaseInsensitive) < 0;
        });

    // Print the new order of cards
    qDebug() << "New order of cards after sorting:";
    for (const auto &card : cards) {
        qDebug() << card.second;
    }

    // Remove all widgets from the layout
    while (layout->count() > 0) {
        QLayoutItem *item = layout->takeAt(0);
        if (item) {
            if (item->widget()) {
                item->widget()->setParent(nullptr);
            }
            delete item;
        }
    }

    // Add widgets back to the layout in sorted order
    for (int i = 0; i < cards.size(); ++i) {
        int row = i / 3;
        int col = i % 3;
        layout->addWidget(cards[i].first, row, col);
    }

    qDebug() << "Finished reordering cards";
}

void MainPage::toggleFavorite(const QString &companyName)
{
  QWidget *card = findChild<QWidget*>("Card_" + companyName);
  if (card) {
    bool isFavorite = card->property("isFavorite").toBool();
    isFavorite = !isFavorite;
    card->setProperty("isFavorite", isFavorite);

    // Update the favorite button icon
    QPushButton *favoriteButton = card->findChild<QPushButton*>("favoriteButton");
    if (favoriteButton) {
      favoriteButton->setIcon(QIcon(isFavorite ? "../icons/star-filled.png" : "../icons/star-empty.png"));
    }

    // Move the card between favorites and all passwords sections
    QGridLayout *sourceLayout = isFavorite ? 
      qobject_cast<QGridLayout*>(allPasswordsScrollArea->widget()->layout()) :
      qobject_cast<QGridLayout*>(favoritesScrollArea->widget()->layout());

    QGridLayout *targetLayout = isFavorite ? 
      qobject_cast<QGridLayout*>(favoritesScrollArea->widget()->layout()) :
      qobject_cast<QGridLayout*>(allPasswordsScrollArea->widget()->layout());

    if (sourceLayout && targetLayout) {
      // Remove the card from the source layout
      sourceLayout->removeWidget(card);

      // Add the card to the target layout (it will be added at the end)
      targetLayout->addWidget(card);

      // Reorder both layouts
      reorderCards(sourceLayout);
      reorderCards(targetLayout);

      // Update card counts
      if (isFavorite) {
        allPasswordsCardCount--;
        favoritesCardCount++;
      } else {
        favoritesCardCount--;
        allPasswordsCardCount++;
      }
    }
  }
}

void MainPage::filterPasswords(const QString &searchText)
{
  QRegularExpression regex("Card_.*");
  for (QWidget *card : findChildren<QWidget*>(regex)) {
    bool shouldShow = card->objectName().contains(searchText, Qt::CaseInsensitive) ||
      card->findChild<QLabel*>()->text().contains(searchText, Qt::CaseInsensitive);
    card->setVisible(shouldShow);
  }
}

void MainPage::setupEncryptPage()
{
    encryptPage = new EncryptPage(this);
    encryptPage->hide();
}
