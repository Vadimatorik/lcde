#include "mono_lcd.h"

#include <QPainter>

mono_lcd::mono_lcd (QColor back_color, QColor pix_color,
                    uint8_t x_pix_num, uint8_t y_pix_num,
                    float proc_ind,
                    QWidget *parent) :
    QWidget(parent),
    back_color(back_color),
    pix_color(pix_color),
    x_pix_num(x_pix_num),
    y_pix_num(y_pix_num),
    proc_ind(proc_ind) {

    this->state = new bool *[x_pix_num];

    for (int i = 0; i < x_pix_num; i++) {
        this->state[i] = new bool[y_pix_num];
    }

    this->clean();
}

void mono_lcd::clean () {
    for (int y = 0; y < this->y_pix_num; y++) {
        for (int x = 0; x < this->x_pix_num; x++) {
            this->state[x][y] = false;
        }
    }
}

void mono_lcd::paintEvent (QPaintEvent *event) {
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setPen(QPen(back_color, 0));
    painter.setBrush(QBrush(back_color, Qt::SolidPattern));
    painter.drawRect(0, 0, this->width(), this->height());
    painter.setPen(QPen(pix_color, 0));
    painter.setBrush(QBrush(pix_color, Qt::SolidPattern));

    double d_w_width = this->width();
    double d_w_height = this->height();

    uint size_pixel_x = static_cast<uint>((d_w_width/x_pix_num)*(1 - this->proc_ind));
    uint size_pixel_y = static_cast<uint>((d_w_height/y_pix_num)*(1 - this->proc_ind));

    for (int y = 0; y < this->y_pix_num; y++) {
        for (int x = 0; x < this->x_pix_num; x++) {
            if (this->state[x][y]) {
                painter.drawRect(static_cast<uint>(d_w_width/128.0*x),
                                 static_cast<uint>(d_w_height/64.0*y),
                                 size_pixel_x,
                                 size_pixel_y);
            }
        }
    }

}

int mono_lcd::set_point (uint8_t x, uint8_t y) {
    this->state[x][y] = true;
    this->update();
    return 0;
}

int mono_lcd::reset_point (uint8_t x, uint8_t y) {
    this->state[x][y] = false;
    this->update();
    return 0;
}

