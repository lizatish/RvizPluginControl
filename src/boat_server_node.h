#ifndef BOAT_SERVER_NODE_H
#define BOAT_SERVER_NODE_H

#include <QObject>
#include <QString>

#include <string>

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <visualization_msgs/Marker.h>

class Boat_server_node : public QObject
{
    Q_OBJECT
public:
    Boat_server_node();

    enum topicType {
        geometry_msgs_Twist = 1,
    };
    void setName(QString name) {
        node_name_ = name;
    }
    void setGNSSsubscriber(QString topic, topicType topic_type) {
        gnss_topic_name_ = topic;
        gnss_topic_type_ = topic_type;//topic_type;
    }
    void setFrame(QString frame_id) {
        node_frame_ = frame_id;
    }
    void finish();

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

    //Подписчик на данные о глобальном положении
    ros::Subscriber gnss_subscriber_;
    //Подписчик на аккумулятор
    ros::Subscriber battery_status_subscriber_;
    //Публикатор положения платформы виде маркера
    ros::Publisher robot_model_publisher_;


    //Флаг разрешения на обработку
    bool is_allow_processing;
    //Флаг окончания обработки
    bool is_finished_processing;
    //Флаг наличия актуальных данных с gnss
    bool is_actual_gnss;

//    //Координаты платформы
//    geographic_msgs::GeoPoint gnss_lonlat_pt;
//    geodesy::UTMPoint gnss_utm_pt;

//    //Ответчики
//    void gnss_callback_odom(const nav_msgs::Odometry &data);
//    void gnss_callback_navsat(const sensor_msgs::NavSatFix &data);
};

#endif // BOAT_SERVER_NODE_H
