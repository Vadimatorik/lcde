#include "lcde.h"

void lcde::new_connection () {
    this->socket = server->nextPendingConnection();
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(server_read()));
    connect(this->socket, SIGNAL(disconnected()), this, SLOT(client_disconnected()));
}

void lcde::client_disconnected () {
    this->server->close();
}

void lcde::server_read () {
    this->data.append(this->socket->read(this->socket->bytesAvailable()));
    while (this->data.size() > 2) {
        switch (this->data[0]) {
            case CODE_PIN_CS:
                this->cs_handler(this->data[1]);
                break;

            case CODE_PIN_DC:
                this->dc_handler(this->data[1]);
                break;

            case CODE_PIN_RST:
                this->rst_handler(this->data[1]);
                break;

            case CODE_BYTE_SPI:
                this->spi_handler(this->data[1]);
                break;
        }
        this->data.remove(0, 2);
    }
}
