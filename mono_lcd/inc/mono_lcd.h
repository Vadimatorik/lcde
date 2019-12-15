#pragma once

#include <QWidget>
#include <QColor>

class mono_lcd : public QWidget {
Q_OBJECT

public:
    explicit mono_lcd (QColor back_color, QColor pixel,
                       uint8_t x_pix_num, uint8_t y_pix_num,
                       float proc_ind,
                       QWidget *parent = nullptr);

public:
    void clean ();
    int set_point (uint8_t x, uint8_t y);

protected:
    void paintEvent (QPaintEvent *event);

private:
    bool *state;
    uint8_t x_pix_num = 0;
    uint8_t y_pix_num = 0;
    float proc_ind = 0;

private:
    QColor back_color = QColor(Qt::GlobalColor::green);
    QColor pix_color = QColor(Qt::GlobalColor::black);

};
