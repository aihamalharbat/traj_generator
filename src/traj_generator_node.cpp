#include <ros/ros.h>
#include<iostream>
#include <geometry_msgs/PoseStamped.h>

float command_alt;
int dummy;
double start_time;
int start_alt = -2;
float command = -1;
int t_f = 5;
float calculateCommand(double t_var){
    int a0 = start_alt;
    float a2 = (3/(std::pow(t_f,2))) * (command_alt - start_alt);
    float a3 = (-2/(std::pow(t_f,3))) * (command_alt - start_alt);
    float command_var = a0 + a2 * (std::pow(t_var,2)) + a3 * (std::pow(t_var,3));
    return (command_var);
}
void TimedCommandCallback(const ros::TimerEvent& e){
    double t = ros::Time::now().toSec();
    t = t - start_time;
    if(t <= t_f){
        command = calculateCommand(t);
        ROS_WARN("Here @ %f", command);
    }
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "trajectory_generator_node");

    ros::NodeHandle nh_;

    ros::Publisher traj_command = nh_.advertise<geometry_msgs::PoseStamped>("command/pose",1);

    ROS_INFO("Please enter the altitude command:");
    std::cin >> command_alt;

    ROS_INFO("The altitude command: %f", command_alt);

    ROS_WARN("Enter any number to start..");

    std::cin >> dummy;

    ros::Timer command_timer_;
    command_timer_ = nh_.createTimer(
      ros::Duration(0.01), TimedCommandCallback, false, true);

    geometry_msgs::PoseStamped msg;

    msg.header.frame_id = "map";
    msg.pose.position.x = 0;
    msg.pose.position.y = 0;
    msg.pose.orientation.x = 0;
    msg.pose.orientation.y = 0;
    msg.pose.orientation.z = 0;
    msg.pose.orientation.w = 1;

    start_time = ros::Time::now().toSec();
    while (ros::ok())
    {
        ros::spinOnce();
        msg.header.stamp = ros::Time::now();
        msg.pose.position.z = command;
        traj_command.publish(msg);
    }
    

    return 0;
}