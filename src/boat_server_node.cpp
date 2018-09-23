#include "boat_server_node.h"

Boat_server_node::Boat_server_node()
{
    is_allow_processing = true;
    is_finished_processing = false;
    node_frame_ = "earth";
    is_actual_command_velocity_data = false;
}

void Boat_server_node::finish() {
    is_allow_processing = false;

    command_velocity.linear.x = 0;
    command_velocity.angular.z = 0;
    boat_command_velocity_publisher_.publish(command_velocity);
    ros::spinOnce();

    //    while(!is_finished_processing) {
    //        usleep(50);
    //    }
}

void Boat_server_node::process() {

    std::string frame_id;

    //Узел ROS
    ros::NodeHandle n;
    n.param<std::string> ("frame_id", frame_id, "earth");

    if(gnss_topic_type_ == 1)
        boat_command_velocity_publisher_ = n.advertise<geometry_msgs::Twist>( gnss_topic_name_.toStdString(), 10 );

    ros::Rate rate(100);
    while(is_allow_processing && ros::ok()) {

        cout<<"Message actual: lin " << command_velocity.linear.x << " ang "
           << command_velocity.angular.z <<endl;

        boat_command_velocity_publisher_.publish(command_velocity);
        ros::spinOnce();
        rate.sleep();
    }
}
void Boat_server_node::set_boat_command_velocity(geometry_msgs::Twist data){
    command_velocity.linear.x = data.linear.x;
    command_velocity.angular.z = data.angular.z;

    is_actual_command_velocity_data = true;
}
