#include <QApplication>

#include "mono_lcd.h"

int main (int argc, char *argv[]) {
    QApplication app(argc, argv);

    mono_lcd *lcd = new mono_lcd(Qt::GlobalColor::green, Qt::GlobalColor::black, 128, 64, 0.1);

    for (uint8_t i = 0; i < 64; i++) {
        lcd->set_point(i, i);
    }

    lcd->setMinimumWidth(128 * 3);
    lcd->setMinimumHeight(64 * 3);
    lcd->show();
    return app.exec();
}
