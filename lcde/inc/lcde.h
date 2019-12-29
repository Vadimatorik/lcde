#pragma once

#include <QWidget>

#include "mono_lcd.h"

class lcde : public QWidget {
Q_OBJECT

public:
    explicit lcde (QWidget *parent = nullptr);

private:
    uint16_t socket_port_rst = 50000;
    uint16_t socket_port_dc = 50001;
    uint16_t socket_port_cs = 50002;
    uint16_t socket_port_spi = 50100;

private slots:
    void socket_port_cs_slot ();
    void socket_port_dc_slot ();
    void socket_port_rst_slot ();
    void socket_port_spi_slot ();

private:
    mono_lcd *lcd;

};