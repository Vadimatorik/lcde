#include "lcde.h"

#include <QHBoxLayout>
#include <QNetworkDatagram>
#include <QByteArray>

lcde::lcde (QWidget *parent) : QWidget(parent) {
    QHBoxLayout *l = new QHBoxLayout(this);
    this->lcd = new mono_lcd(Qt::GlobalColor::green, Qt::GlobalColor::black, 128, 64, 0.1);
    l->addWidget(this->lcd);

    this->server_cs = new QTcpServer(this);
    this->server_dc = new QTcpServer(this);
    this->server_rst = new QTcpServer(this);
    this->server_spi = new QTcpServer(this);

    this->socket_cs = new QTcpSocket(this);
    this->socket_dc = new QTcpSocket(this);
    this->socket_rst = new QTcpSocket(this);
    this->socket_spi = new QTcpSocket(this);


    if (!this->server_cs->listen(QHostAddress::LocalHost, this->socket_port_cs)) {
        exit(errno);
    }

    if (!this->server_dc->listen(QHostAddress::LocalHost, this->socket_port_dc)) {
        exit(errno);
    }

    if (!this->server_rst->listen(QHostAddress::LocalHost, this->socket_port_rst)) {
        exit(errno);
    }

    if (!this->server_spi->listen(QHostAddress::LocalHost, this->socket_port_spi)) {
        exit(errno);
    }

    connect(this->server_cs, SIGNAL(newConnection()), this, SLOT(new_connection_port_cs()));
    connect(this->server_dc, SIGNAL(newConnection()), this, SLOT(new_connection_port_dc()));
    connect(this->server_rst, SIGNAL(newConnection()), this, SLOT(new_connection_port_rst()));
    connect(this->server_spi, SIGNAL(newConnection()), this, SLOT(new_connection_port_spi()));
}
