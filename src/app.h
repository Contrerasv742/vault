#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <QProxyStyle>
#include <QStyleOption>

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
  // Macro from the core QT header file
  Q_OBJECT

public:
  explicit EncryptionApp(QWidget *parent = nullptr);
  virtual ~EncryptionApp();

private slots:
  void processText();

private:
  void setupUI();
  void styleLabels();
  void forceComboBoxDropDown();
  void updateOptionalInput();

  QComboBox *modeComboBox;
  QComboBox *cipherComboBox;
  QLineEdit *inputText;
  QLineEdit *optionalInputText;
  QTextEdit *outputText;
};

#endif // APP_H
