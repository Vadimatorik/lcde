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
    this->state = new bool[x_pix_num*y_pix_num];
    memset(this->state, 0, sizeof(bool)*x_pix_num*y_pix_num);
}

void mono_lcd::clean () {

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

    uint size_pixel_column = static_cast<uint>((d_w_width/x_pix_num)*(1 - this->proc_ind));
    uint size_pixel_row = static_cast<uint>((d_w_height/y_pix_num)*(1 - this->proc_ind));

    for (int string_num = 0; string_num < this->y_pix_num; string_num++) {
        for (int column_num = 0; column_num < this->x_pix_num; column_num++) {
            if (this->state[string_num*this->y_pix_num + column_num]) {
                painter.drawRect(static_cast<uint>(d_w_width/128.0*column_num),
                                 static_cast<uint>(d_w_height/64.0*string_num),
                                 size_pixel_column,
                                 size_pixel_row);
            }
        }
    }

}

int mono_lcd::set_point (uint8_t x, uint8_t y) {
    this->state[y*this->y_pix_num + x] = true;

    return 0;
}
