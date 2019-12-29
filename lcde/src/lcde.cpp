#include "lcde.h"

#include <QHBoxLayout>
#include <QNetworkDatagram>
#include <QByteArray>

lcde::lcde (QWidget *parent) : QWidget(parent) {
    QHBoxLayout *l = new QHBoxLayout(this);
    this->lcd = new mono_lcd(Qt::GlobalColor::green, Qt::GlobalColor::black, 128, 64, 0.1);
    l->addWidget(this->lcd);

    this->udp_socket_cs = new QUdpSocket(this);
    this->udp_socket_dc = new QUdpSocket(this);
    this->udp_socket_rst = new QUdpSocket(this);
    this->udp_socket_spi = new QUdpSocket(this);

    udp_socket_cs->bind(QHostAddress::LocalHost, socket_port_cs);
    udp_socket_dc->bind(QHostAddress::LocalHost, socket_port_dc);
    udp_socket_rst->bind(QHostAddress::LocalHost, socket_port_rst);
    udp_socket_spi->bind(QHostAddress::LocalHost, socket_port_spi);


    connect(udp_socket_cs, SIGNAL(readyRead()), this, SLOT(socket_port_cs_slot()));
    connect(udp_socket_dc, SIGNAL(readyRead()), this, SLOT(socket_port_dc_slot()));
    connect(udp_socket_rst, SIGNAL(readyRead()), this, SLOT(socket_port_rst_slot()));
    connect(udp_socket_spi, SIGNAL(readyRead()), this, SLOT(socket_port_spi_slot()));
}

void lcde::get_pin_state (QUdpSocket *udp, bool& var) {
    if (!udp->hasPendingDatagrams()) {
        return;
    }

    QByteArray data = udp->receiveDatagram().data();
    if (data.size() != 1) {
        return;
    }

    var = (data[0])?true:false;
}