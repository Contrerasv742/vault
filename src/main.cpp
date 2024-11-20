#include "main.h"
#include <QApplication>
#include "app.h"
#include "cipher.h"
#include "passwordManager.h"

void setApplicationStyle(QApplication &app) {
    app.setStyleSheet(
            "QWidget { background-color: #1E1E2E; color: white; }"
            "QPlainTextEdit { background-color: #323547; color: white; }"
            "QPushButton { background-color: #323547; color: white; border: "
            "1px "
            "solid #5c5c5c; padding: 5px; }"
            "QPushButton:hover { background-color: #323547; }"
            "QLineEdit { background-color: #323547; color: white; padding: "
            "5px; }"
            "QComboBox { background-color: #323547; color: white; border: 1px "
            "solid "
            "#5c5c5c; padding: 5px; }"
            "QComboBox::drop-down { border: 0px; } "
            "QComboBox::down-arrow { image: url(dropdown.png); width: 14px; "
            "height: "
            "14px; }"
            "QTextEdit { background-color: #323547; color: white; }");
}

int main(int argc, char *argv[]) {
    /* Testing */
    PasswordManager passwords = PasswordManager("passwords.json");

    Password google = Password("Google", "Victor", "agent?3");
    Password x = Password("X.com", "Neel", "Walse");

    passwords.addPassword(google);
    passwords.addPassword(x);

    std::cout << passwords.view() << std::endl;

    passwords.removePassword(google);
    passwords.removePassword(x);

    std::cout << passwords.view() << std::endl;
    
    // std::string output = rsa("","");
    // std::cout << output << std::endl;

    return 0;

    /*
     */
    QApplication app(argc, argv);
    setApplicationStyle(app);

    EncryptionApp window;
    window.show();

    return app.exec();
}
