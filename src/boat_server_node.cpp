#include "boat_server_node.h"

Boat_server_node::Boat_server_node()
{
    is_allow_processing = true;
    is_finished_processing = false;
    node_frame_ = "earth";
    is_actual_gnss = false;
}

//void Boat_server_node::gnss_callback_odom(const nav_msgs::Odometry &data) {

//    gnss_lonlat_pt.latitude = (double)data.pose.pose.position.x;
//    gnss_lonlat_pt.longitude = (double)data.pose.pose.position.y;
//    gnss_lonlat_pt.altitude = (double)data.pose.pose.position.z;
//    gnss_utm_pt = geodesy::UTMPoint(gnss_lonlat_pt);
//    is_actual_gnss = true;
//}

//void Boat_server_node::gnss_callback_navsat(const sensor_msgs::NavSatFix &data) {

//}

void Boat_server_node::finish() {
    is_allow_processing = false;
    while(!is_finished_processing) {
        usleep(50);
    }
}

void Boat_server_node::process() {

    std::string frame_id;

    //Узел ROS
    ros::NodeHandle n;
    n.param<std::string> ("frame_id", frame_id, "earth");
//    //Формируем подписчиков
//    if(gnss_topic_type_ == nav_msgs_Odometry && !gnss_topic_name_.isEmpty()){
//        gnss_subscriber_ = n.subscribe("/sbg_output", 8,&ugv_server_node::gnss_callback_odom, this);
//    }
//    if(gnss_topic_type_ == sensor_msgs_NavSatFix && !gnss_topic_name_.isEmpty()){
//        gnss_subscriber_ = n.subscribe("/sbg_output", 8,&ugv_server_node::gnss_callback_navsat, this);
//    }

    robot_model_publisher_ = n.advertise<visualization_msgs::Marker>( "/ugv", 10 );

    while(is_allow_processing && ros::ok()) {
        if(is_actual_gnss) {
            is_actual_gnss = false;
//            cout<<"Message"<<endl;
            //Формируем сообщение с автобусом
            visualization_msgs::Marker marker;
            marker.header.frame_id = "/earth";
            marker.header.stamp = ros::Time();
            marker.ns = node_name_.toStdString();
            marker.id = 0;
            marker.type = visualization_msgs::Marker::CUBE;
            marker.action = visualization_msgs::Marker::ADD;
//            marker.pose.position.x = gnss_utm_pt.easting;
//            marker.pose.position.y = gnss_utm_pt.northing;
            marker.pose.position.z = 0.0;
            marker.pose.orientation.x = 0.0;
            marker.pose.orientation.y = 0.0;
            marker.pose.orientation.z = 0.0;
            marker.pose.orientation.w = 1.0;
            marker.scale.x = 15.0;
            marker.scale.y = 15.0;
            marker.scale.z = 15.0;
            marker.color.g = 1.0;
            marker.color.a = 1.0;
            robot_model_publisher_.publish(marker);
        }
        usleep(50);
        ros::spinOnce();
    }
    is_finished_processing = true;
}
