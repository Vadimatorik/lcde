#pragma once

#include <QWidget>
#include <QUdpSocket>

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
    void get_pin_state (QUdpSocket *udp, bool& var);

private:
    QUdpSocket *udp_socket_cs = nullptr;
    QUdpSocket *udp_socket_dc = nullptr;
    QUdpSocket *udp_socket_rst = nullptr;
    QUdpSocket *udp_socket_spi = nullptr;

private:
    bool cs = false;
    bool rst = false;
    bool dc = false;

private:
    mono_lcd *lcd = nullptr;

};