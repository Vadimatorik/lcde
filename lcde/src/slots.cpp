#include "lcde.h"

void lcde::socket_port_cs_slot () {
    this->get_pin_state(this->udp_socket_cs, this->cs);
}

void lcde::socket_port_dc_slot () {
    this->get_pin_state(this->udp_socket_dc, this->dc);
}

void lcde::socket_port_rst_slot () {
    this->get_pin_state(this->udp_socket_rst, this->rst);
}

void lcde::socket_port_spi_slot () {

}