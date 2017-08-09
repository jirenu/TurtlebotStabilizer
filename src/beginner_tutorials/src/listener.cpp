#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"


float prev_linear_x;
float prev_linear_y;
float prev_linear_z;
float prev_angular_x;
float prev_angular_y;
float prev_angular_z;

float alpha = .8;

ros::NodeHandle n;
ros::Publisher pub = n.advertise<geometry_msgs::Twist>("mobile_base_nodelet_manager",1);

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void cmd_vel_Callback(const geometry_msgs::Twist& cmd_vel)
{
//  ROS_INFO("I heard: [%s]", msg->data.c_str());
  ROS_INFO("I heard: [%f]", cmd_vel.linear.x);

  geometry_msgs::Twist new_cmd_vel; 
  
  new_cmd_vel.linear.x = (alpha * cmd_vel.linear.x) + (1-alpha)*prev_linear_x;
  new_cmd_vel.linear.y = cmd_vel.linear.y;
  new_cmd_vel.linear.z = cmd_vel.linear.z;

  new_cmd_vel.angular.x = cmd_vel.angular.x;
  new_cmd_vel.angular.y = cmd_vel.angular.y;
  new_cmd_vel.angular.z = cmd_vel.angular.z;
   
  prev_linear_x = new_cmd_vel.linear.x;	
  prev_linear_y = new_cmd_vel.linear.y;
  prev_linear_z = new_cmd_vel.linear.z;
  prev_angular_x = new_cmd_vel.angular.x;
  prev_angular_y = new_cmd_vel.angular.y;
  prev_angular_z = new_cmd_vel.angular.z;

  pub.publish(new_cmd_vel);  
}

int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "listener");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
//  ros::NodeHandle n;

  /**
   * The subscribe() call is how you tell ROS that you want to receive messages
   * on a given topic.  This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing.  Messages are passed to a callback function, here
   * called chatterCallback.  subscribe() returns a Subscriber object that you
   * must hold on to until you want to unsubscribe.  When all copies of the Subscriber
   * object go out of scope, this callback will automatically be unsubscribed from
   * this topic.
   *
   * The second parameter to the subscribe() function is the size of the message
   * queue.  If messages are arriving faster than they are being processed, this
   * is the number of messages that will be buffered up before beginning to throw
   * away the oldest ones.
   */

 
/*  
  geometry_msgs::Twist new_cmd_vel = *cmd_vel;

  new_cmd_vel.linear.x = cmd_vel->linear.x;
  new_cmd_vel.linear.y = cmd_vel->linear.y;
  new_cmd_vel.linear.z = cmd_vel->linear.z;

  new_cmd_vel.angular.x = cmd_vel->angular.x;
  new_cmd_vel.angular.y = cmd_vel->angular.y;
  new_cmd_vel.angular.z = cmd_vel->angular.z;

  pub.publish(new_vel);
  
*/

  ros::Subscriber sub = n.subscribe("new_topic", 1000, cmd_vel_Callback);


  float last_linear_x;	
  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
  ros::spin();

  return 0;
}
