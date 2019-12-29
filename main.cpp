#include <QApplication>

#include "lcde.h"

int main (int argc, char *argv[]) {
    QApplication app(argc, argv);
    lcde *l = new lcde();
    l->setMinimumWidth(128 * 5);
    l->setMinimumHeight(64 * 5);
    l->show();
    return app.exec();
}
