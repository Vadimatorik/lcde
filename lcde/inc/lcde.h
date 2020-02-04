#pragma once

#include <QWidget>
#include <QTcpServer>
#include <QByteArray>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QList>
#include <QTcpSocket>

#include "mono_lcd.h"

struct lcde_cfg {
    uint16_t port;
};

class lcde : public QWidget {
Q_OBJECT

public:
    explicit lcde (QWidget *parent, lcde_cfg *cfg);

private slots:
    void new_connection ();
    void server_read ();
    void client_disconnected ();

private:
    void cs_handler (uint8_t data);
    void dc_handler (uint8_t data);
    void rst_handler (uint8_t data);
    void spi_handler (uint8_t data);

private:
    QTcpServer *server = nullptr;
    QTcpSocket *socket = nullptr;

private:
    bool cs = false;
    bool rst = false;
    bool dc = false;

private:
    uint8_t p_addr = 0;
    uint8_t column_addr = 0;
    uint8_t start_line_set = 0;

private:
    static const uint8_t CODE_PIN_CS = 0;
    static const uint8_t CODE_PIN_DC = 1;
    static const uint8_t CODE_PIN_RST = 2;
    static const uint8_t CODE_BYTE_SPI = 3;

private:
    QByteArray data;

private:
    mono_lcd *lcd = nullptr;

};