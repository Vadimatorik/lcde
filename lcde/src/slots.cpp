#include "lcde.h"

void lcde::new_connection_port_cs () {
    this->socket_cs = server_cs->nextPendingConnection();
    connect(this->socket_cs, SIGNAL(readyRead()), this, SLOT(server_read_port_cs()));
    connect(this->socket_cs, SIGNAL(disconnected()), this, SLOT(client_disconnected_port_cs()));
}

void lcde::new_connection_port_dc () {
    this->socket_dc = server_dc->nextPendingConnection();
    connect(this->socket_dc, SIGNAL(readyRead()), this, SLOT(server_read_port_dc()));
    connect(this->socket_dc, SIGNAL(disconnected()), this, SLOT(client_disconnected_port_dc()));
}

void lcde::new_connection_port_rst () {
    this->socket_rst = server_rst->nextPendingConnection();
    connect(this->socket_rst, SIGNAL(readyRead()), this, SLOT(server_read_port_rst()));
    connect(this->socket_rst, SIGNAL(disconnected()), this, SLOT(client_disconnected_port_rst()));
}

void lcde::new_connection_port_spi () {
    this->socket_spi = server_spi->nextPendingConnection();
    connect(this->socket_spi, SIGNAL(readyRead()), this, SLOT(server_read_port_spi()));
    connect(this->socket_spi, SIGNAL(disconnected()), this, SLOT(client_disconnected_port_spi()));
}

void lcde::client_disconnected_port_cs () {
    this->server_cs->close();
}

void lcde::client_disconnected_port_dc () {
    this->server_dc->close();
}

void lcde::client_disconnected_port_rst () {
    this->server_rst->close();
}

void lcde::client_disconnected_port_spi () {
    this->server_spi->close();
}

void lcde::server_read_port_cs () {
    QByteArray data = this->socket_cs->read(this->socket_cs->bytesAvailable());
    for (int i = 0; i < data.size(); i++) {
        this->cs = data[i];
    }
}

void lcde::server_read_port_dc () {
    QByteArray data = this->socket_dc->read(this->socket_dc->bytesAvailable());
    for (int i = 0; i < data.size(); i++) {
        this->dc = data[i];
    }
}

void lcde::server_read_port_rst () {
    QByteArray data = this->socket_rst->read(this->socket_rst->bytesAvailable());
    for (int i = 0; i < data.size(); i++) {
        this->rst = data[i];

        if (!this->rst) {
            this->lcd->clean();
        }
    }
}

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
}