
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

namespace rviz_plugin_control
{
class DriveWidget: public QWidget
{
    Q_OBJECT
public:
    // This class is not instantiated by pluginlib::ClassLoader, so the
    // constructor has no restrictions.
    DriveWidget( QWidget* parent = 0 );

    // We override QWidget::paintEvent() to do custom painting.
    virtual void paintEvent( QPaintEvent* event );

    // We override the mouse events and leaveEvent() to keep track of
    // what the mouse is doing.

    virtual void leaveEvent( QEvent* event );

    // Override sizeHint() to give the layout managers some idea of a
    // good size for this.
    virtual QSize sizeHint() const { return QSize( 150, 150 ); }

    // We emit outputVelocity() whenever it changes.
Q_SIGNALS:
    void outputVelocity( float linear, float angular );

    // mouseMoveEvent() and mousePressEvent() need the same math to
    // figure the velocities, so I put that in here.
protected:
    // Лист всех лодок
    QComboBox* boats_list;

    // Слайдеры для управления скоростями
    QLabel* linear_label;
    QSlider* linear_slider;
    QLabel* angular_label;
    QSlider* angular_slider;
    QLabel* angular_speed_label;
    QLabel* linear_speed_label;

    //// Сетки расположений
    // Управления
    QGridLayout* controls_layout;
    // Списка лодочек
    QGridLayout* boat_tree_layout;
    // Стоп-кнопки
    QGridLayout* stop_button_layout;
    // Кнопок изменнения списка лодочек
    QGridLayout* manager_buttons_layout;
    // Главная сетка
    QGridLayout* main_layout;

    // Кнопка экстренной остаовки
    QPushButton* stop_button;
    QLabel* stop_button_label;

    // Кнопки управления списком лодочек
    QPushButton* add_button;
    QPushButton* edit_button;
    QPushButton* remove_button;


    // A function to emit zero velocity.
    void stop();

    // Finally the member variables:
    float linear_velocity_; // In m/s
    float angular_velocity_; // In radians/s
    float linear_scale_; // In m/s
    float angular_scale_; // In radians/s
private Q_SLOTS:
    void setLinearData( int linear_data);
    void setAngularData( int angular_data);
    void stopBoat();
};
// END_TUTORIAL

} // end namespace rviz_plugin_tutorials


#endif // DRIVE_WIDGET_H
