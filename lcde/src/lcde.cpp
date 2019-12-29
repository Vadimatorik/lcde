#include "lcde.h"

#include <QHBoxLayout>
#include <QUdpSocket>

lcde::lcde (QWidget *parent) : QWidget(parent) {
    QHBoxLayout *l = new QHBoxLayout();
    this->setLayout(l);

    this->lcd = new mono_lcd(Qt::GlobalColor::green, Qt::GlobalColor::black, 128, 64, 0.1);
    l->addWidget(lcd);
}