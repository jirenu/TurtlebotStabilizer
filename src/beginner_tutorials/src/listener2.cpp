#include "ros/ros.h"
#include "float.h"
#include <cmath>
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "sensor_msgs/Imu.h"
#include "rl_msgs/RLAction.h"
#include "rl_msgs/RLEnvDescription.h"
#include "rl_msgs/RLStateReward.h"

struct StateReward{
//Teleop values
float teleopLinearXIn;
float teleopAngularZIn;
float teleopLinearXOut;
float teleopAngularZOut;

//IMU1 values
float imu1LinearX;
float imu1LinearZ;

//IMU2 values
float imu2LinearX;
float imu2LinearZ;

//Odom values
float odomLinearX;
float odomAngularZ;

};

int actionFrequency[6];
float prev_linear_x;
float prev_linear_y;
float prev_linear_z;
float prev_angular_x;
float prev_angular_y;
float prev_angular_z;
float totalReward = 0.0;
float numReward = 0.0;
float alpha = .5;
int act1 = 0;
int act2 = 0;
int act3 = 0;
int act4 = 0;
int act5 = 0;
int act6 = 0;

StateReward stateReward;
//ros::NodeHandle np;
ros::Publisher pub;
ros::Publisher pubRLEnv;
ros::Publisher pubRLState;

float rewardCalculator(StateReward st)
{
	numReward++;
	float maxReward = 10;
        float beta = 0.5;
        float lossImuSquared = pow(10*st.imu1LinearX - 10*st.imu2LinearX, 2) +
                               pow(10*st.imu1LinearZ - 10*st.imu2LinearZ, 2);
        float lossImu = pow(lossImuSquared, 0.5);
        float lossTeleopSquared = pow(10*st.teleopLinearXIn - 10*st.teleopLinearXOut, 2) +
                               pow(10*st.teleopAngularZIn - 10*st.teleopAngularZOut, 2);
        float lossTeleop  = pow(lossTeleopSquared, 0.5);
        float loss = beta*lossImu+(1-beta)*lossTeleop;
	float reward = maxReward -loss;
	if (reward<0.0)
	{
		totalReward +=0.0;
        	printf( "Running average is: %6.4lf\n", totalReward/numReward);
		return 0.0;
	}
	totalReward +=reward;
	printf( "Running average is: %6.4lf\n", totalReward/numReward);
	return reward;
}


/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void cmd_vel_Callback_teleop(const geometry_msgs::Twist& cmd_vel)
{
  //ROS_INFO("I heard: [%f]", cmd_vel.linear.x);
/*
  geometry_msgs::Twist new_cmd_vel;

  new_cmd_vel.linear.x = (alpha * cmd_vel.linear.x) + (1-alpha)*prev_linear_x;
  new_cmd_vel.linear.y = (alpha * cmd_vel.linear.y) + (1-alpha)*prev_linear_y;
  new_cmd_vel.linear.z = (alpha * cmd_vel.linear.z) + (1-alpha)*prev_linear_z;

  new_cmd_vel.angular.x = (alpha * cmd_vel.angular.x) + (1-alpha)*prev_angular_x;
  new_cmd_vel.angular.y = (alpha * cmd_vel.angular.y) + (1-alpha)*prev_angular_y;
  new_cmd_vel.angular.z = (alpha * cmd_vel.angular.z) + (1-alpha)*prev_angular_z;

  prev_linear_x = new_cmd_vel.linear.x;
  prev_linear_y = new_cmd_vel.linear.y;
  prev_linear_z = new_cmd_vel.linear.z;
  prev_angular_x = new_cmd_vel.angular.x;
  prev_angular_y = new_cmd_vel.angular.y;
  prev_angular_z = new_cmd_vel.angular.z;
*/
  //ROS_INFO("I sent: [%f]", new_cmd_vel.linear.x);
 

  //Set struct values
  stateReward.teleopLinearXIn = cmd_vel.linear.x;
  stateReward.teleopAngularZIn = cmd_vel.angular.z; 
  
//TODO: publish to RL_State_Reward
//  ROS_INFO("I heard: [%s]", msg->data.c_str());

//  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("mobile_base_nodelet_manager",1);
 // pub.publish(new_cmd_vel);
  //Prep the message to be sent
  rl_msgs::RLStateReward stateVar;
  stateVar.state.push_back(10*stateReward.odomLinearX);
  stateVar.state.push_back(10*stateReward.odomAngularZ);
  stateVar.state.push_back(10*stateReward.teleopLinearXIn);
  stateVar.state.push_back(10*stateReward.teleopAngularZIn);
  stateVar.reward = rewardCalculator(stateReward);
  //publish the message
  pubRLState.publish(stateVar);

}


void cmd_vel_Callback_odom(const nav_msgs::Odometry& odom)
{
  stateReward.odomLinearX = odom.twist.twist.linear.x;
  stateReward.odomAngularZ = odom.twist.twist.angular.z;
  //ROS_INFO("I heard odom: [%f]", odom.twist.twist.linear.x);
}

void imu1_Callback(const sensor_msgs::Imu& imu1)
{
//  stateReward.imu1LinearX = imu1.linear_acceleration.x;
  //stateReward.imu1LinearY = imu1.linear_acceleration.y;
  stateReward.imu1LinearZ = imu1.linear_acceleration.z;

 // ROS_INFO("I heard imu1 x acc: [%f]", imu1.linear_acceleration.x);
 // ROS_INFO("I heard imu1 y acc: [%f]", imu1.linear_acceleration.y);
  //ROS_INFO("I heard imu1 z acc: [%f]", imu1.linear_acceleration.z);
   
}

void imu2_Callback(const sensor_msgs::Imu& imu2)
{
  //stateReward.imu2LinearX = imu2.linear_acceleration.x;
  //stateReward.imu2LinearY = imu2.linear_acceleration.y;
  stateReward.imu2LinearZ = imu2.linear_acceleration.z;
 
 //ROS_INFO("I heard imu2 x acc: [%f]", imu2.linear_acceleration.x);
  //ROS_INFO("I heard imu2 y acc: [%f]", imu2.linear_acceleration.y);
  //ROS_INFO("I heard imu3 z acc: [%f]", imu2.linear_acceleration.z);

}
void actPrinter()
{
	printf("Action 1(low lin):%d\n", act1);
	printf("Action 2(med lin):%d\n", act2);
	printf("Action 3(high lin):%d\n", act3);
	printf("Action 4(no speed):%d\n", act4);
	printf("Action 5(low ang):%d\n", act5);
	printf("Action 6(high ang):%d\n", act6);
}
void RLAction_Callback(const rl_msgs::RLAction& act)
{
	float low = 0.2;
	float med = 0.5;
	float high = 1;
	float maxOdom = 0.18;
	float minOdom = -0.18;
	geometry_msgs::Twist new_cmd_vel;
	if (act.action==0)
	{
		act1++;
		new_cmd_vel.linear.x = low*maxOdom;
  		new_cmd_vel.angular.x = 0;
	}
	else if(act.action==1)
	{
		act2++;
		new_cmd_vel.linear.x = med*maxOdom;
                new_cmd_vel.angular.x = 0;	
	}
	else if(act.action==2)
        {
		act3++;
		new_cmd_vel.linear.x = high*maxOdom;
                new_cmd_vel.angular.x = 0;
                
        }
	else if(act.action==3)
        {
		act4++;
                new_cmd_vel.linear.x = 0;
                new_cmd_vel.angular.x = 0;
        }
	else if(act.action==4)
        {
		act5++;
                new_cmd_vel.linear.x = 0;
                new_cmd_vel.angular.z = float(0.5); 
        }
	else if(act.action==5)
	{
		act6++;
		new_cmd_vel.linear.x = 0;
                new_cmd_vel.angular.z = float(-0.5);
	}
	new_cmd_vel.linear.y = 0;
	new_cmd_vel.linear.z = 0;
	new_cmd_vel.angular.x = 0;
	new_cmd_vel.angular.y = 0;
	//Set struct values
	stateReward.teleopLinearXOut = new_cmd_vel.linear.x;	
	stateReward.teleopAngularZOut = new_cmd_vel.angular.z;
	pub.publish(new_cmd_vel);
	actPrinter();
	//ROS_INFO("I sent: [%f]", new_cmd_vel.linear.x);
	//ROS_INFO("I heard from agent: [%f]", act.action);
}

void initStruct(StateReward* st)
{
        //Teleop values
st->teleopLinearXIn = 0;
st->teleopAngularZIn = 0;
st->teleopLinearXOut = 0;
st->teleopAngularZOut= 0;

st->imu1LinearX = 0;
st->imu1LinearZ = 0;

st->imu2LinearX = 0;
st->imu2LinearZ = 0;

st->odomLinearX = 0;
st->odomAngularZ = 0;
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
  ros::init(argc, argv, "listener2");
initStruct(&stateReward);
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
  ros::NodeHandle n;
  ros::Subscriber sub_teleop = n.subscribe("new_topic", 1000, cmd_vel_Callback_teleop);
  ros::Subscriber sub_odom = n.subscribe("odom", 1000, cmd_vel_Callback_odom);
  ros::Subscriber sub_imu1 = n.subscribe("/sim1/imu/data_raw", 1000, imu1_Callback);
  ros::Subscriber sub_imu2 = n.subscribe("/sim2/imu/data_raw", 1000, imu2_Callback);
  
  //Subscribing from reinforcement learning agent
  ros::Subscriber sub_RLAction = n.subscribe("/rl_agent/rl_action",1000, RLAction_Callback);
  
  pub = n.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/teleop",1); 


  //Publihing to reinforcement learning agent
  pubRLState = n.advertise<rl_msgs::RLStateReward>("/rl_env/rl_state_reward", 1);
  //Advertises to rl_msgs/RLEnvDescription Message
  pubRLEnv = n.advertise<rl_msgs::RLEnvDescription>("/rl_env/rl_env_description", 1, true);
   //ros::Publisher chatter_pub = n.advertise<std_msgs::String>("", 1000);  

//Advertises to rl_msgs/RLStateReward.msg
  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
//  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("mobile_base_nodelet_manager",1);
//  pub.publish(cmd_vel);

//TODO: Publish to env
	rl_msgs::RLEnvDescription envDesc;
	envDesc.num_actions = 6;
	envDesc.num_states = 16;
	envDesc.min_state_range.push_back(float(-0.18));
	envDesc.min_state_range.push_back(float(-0.9));
	envDesc.min_state_range.push_back(float(-0.2));
        envDesc.min_state_range.push_back(float(-1.0));
	
	envDesc.max_state_range.push_back(float(0.18));
        envDesc.max_state_range.push_back(float(0.9));
	envDesc.max_state_range.push_back(float(0.2));	
	envDesc.max_state_range.push_back(float(1.0));
	envDesc.max_reward = 100;
	envDesc.reward_range = 100;
	envDesc.stochastic = false;
	envDesc.episodic = false;
	pubRLEnv.publish(envDesc);
  	ros::spin();

  

  return 0;
}
