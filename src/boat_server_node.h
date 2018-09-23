#ifndef BOAT_SERVER_NODE_H
#define BOAT_SERVER_NODE_H

#include <QObject>
#include <QString>

#include <string>
#include <iostream>
using namespace std;

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <visualization_msgs/Marker.h>


class Boat_server_node : public QObject
{
    Q_OBJECT
public:
    Boat_server_node();
    ~Boat_server_node();

    enum topicType {
        geometry_msgs_Twist = 1,
    };
    void setName(QString name) {
        node_name_ = name;
    }
    void setGNSSpublisher(QString topic, topicType topic_type) {
        gnss_topic_name_ = topic;
        gnss_topic_type_ = topic_type;
    }
    void setFrame(QString frame_id) {
        node_frame_ = frame_id;
    }
    void finish();

    void set_boat_command_velocity(geometry_msgs::Twist data);

public Q_SLOTS:
    void process();
private:
    //Имя узла
    QString node_name_;
    //Фрейм узла
    QString node_frame_;
    //Имя топика
    QString gnss_topic_name_;
    //Тип топика
    topicType gnss_topic_type_;

    //Публикатор положения платформы виде маркера
    ros::Publisher boat_command_velocity_publisher_;

    geometry_msgs::Twist command_velocity;

    //Флаг разрешения на обработку
    bool is_allow_processing;
    //Флаг окончания обработки
    bool is_finished_processing;
    //Флаг наличия актуальных данных с gnss
    bool is_actual_command_velocity_data;
};

#endif // BOAT_SERVER_NODE_H
