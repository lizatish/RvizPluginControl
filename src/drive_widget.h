
#ifndef DRIVE_WIDGET_H
#define DRIVE_WIDGET_H

#include <QWidget>
#include <stdio.h>
#include <math.h>
#include <QLineEdit>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QSlider>
#include <QTreeWidgetItem>
#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>
#include <ros/console.h>

#include "boat_parameters.h"

namespace rviz_plugin_control
{
class DriveWidget: public QWidget
{
    Q_OBJECT
public:

    DriveWidget( QWidget* parent = 0 );

Q_SIGNALS:
    void outputVelocity( float linear, float angular );

    // mouseMoveEvent() and mousePressEvent() need the same math to
    // figure the velocities, so I put that in here.
protected:
    // Лист всех лодок
    QComboBox* boats_list;
    QList<Boat_parameters *> boat_list_;

    // Слайдеры для управления скоростями
    QLabel* angular_speed_label;
    QLabel* linear_speed_label;

    // Кнопки управления списком лодочек
    QPushButton* add_button;


    // Finally the member variables:
    float linear_velocity_; // In m/s
    float angular_velocity_; // In radians/s
    float linear_scale_; // In m/s
    float angular_scale_; // In radians/s
private Q_SLOTS:
    void setLinearData( int linear_data);
    void setAngularData( int angular_data);
    void stopBoat();
protected Q_SLOTS:
    //Слот нажатия кнопки добавления объекта
    void add_button_on_clicked();
    void add_boat_on_list();

};
// END_TUTORIAL

} // end namespace rviz_plugin_tutorials


#endif // DRIVE_WIDGET_H
