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
    while(!is_finished_processing) {
        usleep(50);
    }
}

void Boat_server_node::process() {

    std::string frame_id;

    //Узел ROS
    ros::NodeHandle n;
    n.param<std::string> ("frame_id", frame_id, "earth");

    if(gnss_topic_type_ == 1)
        boat_command_velocity_publisher_ = n.advertise<geometry_msgs::Twist>( gnss_topic_name_.toStdString(), 10 );

    while(is_allow_processing && ros::ok()) {
        if(is_actual_command_velocity_data) {
            is_actual_command_velocity_data = false;

            cout<<"Message actual"<<endl;
            boat_command_velocity_publisher_.publish(command_velocity);
        }

        usleep(50);
        ros::spinOnce();
    }
    is_finished_processing = true;
}
void Boat_server_node::set_boat_command_velocity(geometry_msgs::Twist data){
    command_velocity.linear.x = data.linear.x;
    command_velocity.angular.z = data.angular.z;

    is_actual_command_velocity_data = true;
}
