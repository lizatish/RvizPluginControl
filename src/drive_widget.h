#ifndef DRIVE_WIDGET_H
#define DRIVE_WIDGET_H

#include <QThread>
#include <QWidget>
#include <QList>
#include <QLineEdit>
#include <QSlider>
#include <QTreeWidgetItem>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <ros/console.h>
#include <rviz/panel.h>

#include "boat_parameters.h"
#include "boat_server_node.h"

namespace rviz_plugin_control
{
class DriveWidget: public QWidget
{
    Q_OBJECT
public:
    DriveWidget( QWidget* parent = 0 );
    ~DriveWidget();

    void sendCommandVelocity();

    virtual void load( const rviz::Config& config );
    virtual void save( rviz::Config config ) const;

protected:

    //Объект узла
    QList<Boat_server_node *> ros_node_list_;
    //Поток узлов
    QList<QThread *> ros_node_thread_list_;

    int currentItemIndex;
    //Список лодочек
    QList<QTreeWidgetItem *> boat_list_for_widget_;
    QList<Boat_parameters *> boat_list_;

    //Виджет списка платформ
    QTreeWidget *boat_list_widget_;

    // Слайдеры для управления скоростями
    QLabel* angular_speed_label;
    QLabel* linear_speed_label;

    // Кнопки управления списком лодочек
    QPushButton* add_button;

    // Finally the member variables:
    float linear_velocity_; // In m/s
    float angular_velocity_; // In radians/s

protected Q_SLOTS:
    void setLinearData( int linear_data);
    void setAngularData( int angular_data);

    //Слот нажатия кнопки добавления объекта
    void add_button_on_clicked();
    void edit_button_on_clicked();
    void remove_button_on_clicked();
    void add_boat_on_list();
    void edit_boat_to_boat_list();
    void set_current_item();
    void stopBoat();
};

// END_TUTORIAL

} // end namespace rviz_plugin_tutorials


#endif // DRIVE_WIDGET_H
