#include "crypto/cipher.h"
#include <QApplication>
#include "test.h"
#include "ui/app.h"

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
    rsaDebugTest();
    return 0;
    /*
     */

    QApplication app(argc, argv);
    setApplicationStyle(app);

    EncryptionApp window;
    window.show();

    return app.exec();
}
