#include <ros/ros.h>
#include<iostream>
#include <geometry_msgs/PoseStamped.h>

float altitude_command;

int main(int argc, char** argv) {
    ros::init(argc, argv, "trajectory_generator_node");

    ros::NodeHandle nh_;

    ros::Publisher traj_command = nh_.advertise<geometry_msgs::PoseStamped>("command/pose",1);

    ROS_INFO("Please enter the altitude command:");
    std::cin >> altitude_command;

    ROS_INFO("The altitude command: %f", altitude_command);

    return 0;
}