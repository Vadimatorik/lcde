#pragma once

#include <QWidget>
#include <QTcpServer>
#include <QByteArray>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QList>
#include <QTcpSocket>

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
    void new_connection_port_cs ();
    void new_connection_port_dc ();
    void new_connection_port_rst ();
    void new_connection_port_spi ();

    void server_read_port_cs ();
    void server_read_port_dc ();
    void server_read_port_rst ();
    void server_read_port_spi ();

    void client_disconnected_port_cs ();
    void client_disconnected_port_dc ();
    void client_disconnected_port_rst ();
    void client_disconnected_port_spi ();

private:
    QTcpServer *server_cs = nullptr;
    QTcpServer *server_dc = nullptr;
    QTcpServer *server_rst = nullptr;
    QTcpServer *server_spi = nullptr;

    QTcpSocket *socket_cs = nullptr;
    QTcpSocket *socket_dc = nullptr;
    QTcpSocket *socket_rst = nullptr;
    QTcpSocket *socket_spi = nullptr;

private:
    bool cs = false;
    bool rst = false;
    bool dc = false;

private:
    uint8_t p_addr = 0;
    uint8_t column_addr = 0;
    uint8_t start_line_set = 0;

private:
    mono_lcd *lcd = nullptr;

};