#include "main.h"
#include "app.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    EncryptionApp window;
    window.resize(400, 300);
    window.show();

    return app.exec();
}
