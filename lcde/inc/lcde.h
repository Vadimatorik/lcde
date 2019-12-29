#pragma once

#include <QWidget>

#include "mono_lcd.h"

class lcde : public QWidget {
Q_OBJECT

public:
    explicit lcde (QWidget *parent = nullptr);

private:
    mono_lcd *lcd;

};