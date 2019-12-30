#include "lcde.h"

#include <QHBoxLayout>
#include <QNetworkDatagram>
#include <QByteArray>

lcde::lcde (QWidget *parent) : QWidget(parent) {
    QHBoxLayout *l = new QHBoxLayout(this);
    this->lcd = new mono_lcd(Qt::GlobalColor::green, Qt::GlobalColor::black, 128, 64, 0.1);
    l->addWidget(this->lcd);

    this->server = new QTcpServer(this);

    this->socket = new QTcpSocket(this);


    if (!this->server->listen(QHostAddress::LocalHost, 55000)) {
        exit(errno);
    }

    connect(this->server, SIGNAL(newConnection()), this, SLOT(new_connection()));
}


/*

void lcde::server_read_port_spi () {
    QByteArray data = this->socket_spi->read(this->socket_spi->bytesAvailable());
    for (int i = 0; i < data.size(); i++) {
        if (!this->cs) {
            return;
        }

        if (!this->dc) {
            uint8_t cmd = data[i];

            switch (cmd) {
                case 0xE2: // Internal reset.
                    this->lcd->clean();
                    break;

                default:
                    if ((cmd & 0b11000000) == (1 << 6)) {
                        this->start_line_set = cmd & 0b11111;
                    } else if ((cmd & 0b11110000) == 0b10110000) {
                        this->p_addr = cmd & 0b1111;
                    } else if ((cmd & 0b11110000) == 0b00010000) {
                        this->column_addr = (this->column_addr & 0b1111) | ((cmd & 0b1111) << 4);
                    } else if ((cmd & 0b11110000) == 0) {
                        this->column_addr = (this->column_addr & 0b11110000) | (cmd & 0b1111);
                    }

                    break;
            }
        } else {
            for (int b = 0; b < 8; b++) {
                if (data[i] & (1 << b)) {
                    this->lcd->set_point(this->column_addr, this->p_addr*8 + b);
                }
            }

            this->column_addr++;
        }
    }
}*/

void lcde::cs_handler (uint8_t data) {
    this->cs = data;
}

void lcde::dc_handler (uint8_t data) {
    this->dc = data;
}

void lcde::rst_handler (uint8_t data) {
    this->rst = data;

    if (!this->rst) {
        this->lcd->clean();
    }
}

void lcde::spi_handler (uint8_t data) {
    if (this->cs) {
        return;
    }

    if (!this->dc) {
        uint8_t cmd = data;

        switch (cmd) {
            case 0xE2: // Internal reset.
                this->lcd->clean();
                break;

            default:
                if ((cmd & 0b11000000) == (1 << 6)) {
                    this->start_line_set = cmd & 0b11111;
                } else if ((cmd & 0b11110000) == 0b10110000) {
                    this->p_addr = cmd & 0b1111;
                } else if ((cmd & 0b11110000) == 0b00010000) {
                    this->column_addr = (this->column_addr & 0b1111) || ((cmd & 0b1111) << 4);
                } else if ((cmd & 0b11110000) == 0) {
                    this->column_addr = (this->column_addr & 0b11110000) || (cmd & 0b1111);
                }

                break;
        }
    } else {
        for (int b = 0; b < 8; b++) {
            if (data & (1 << b)) {
                this->lcd->set_point(this->column_addr, this->p_addr*8 + b);
            } else {
                this->lcd->reset_point(this->column_addr, this->p_addr*8 + b);
            }
        }

        this->column_addr++;
    }
}
