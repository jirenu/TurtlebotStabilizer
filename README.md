# Stabilizing turtlebots' motion
# How to run agents in rl_agent
**Start the agent before publishing to topics pertinent to the agent**
1. roscore
2. roslaunch turtlebot_bringup minimal.launch
3. roslaunch turtlebot_teleop keyboard_teleop.launch
4. source /home/servicerobot2/catkin_ws2/devel/setup.bash
5. roslaunch phidgets_imu imu.launch
6. source ~/catkin_ws2/devel/setup.bash
7. source rl-texplore-ros-pkg/devel/setup.bash
3. rosrun rl_agent agent --agent texplore
4. rosrun beginner_tutorials listener2
# Key file(s) and script(s)
All files are located in */home/servicerobot2/catkin_ws2/src/beginner_tutorials*
* *src/listener2.cpp* - Creates the node
* *startTurtlebotWithKeyboard* - Invokes **~/jishnu/scripts/rosboot2** with teleop running in the foreground
* *startTurtlebotWithoutKeyboard* - Invokes **~/jishnu/scripts/rosboot** with listener running in the foreground
# Suggested future work
One of the following paths can be taken to successfully stabilize the movements of turtlebots:
* A functional approximator with a model free agent such as q-learning or SARSA can be used to deal with continuous state space.
* A model based agent such as texlplore or r-max in conjunction with state range and number of states can be used to discretize the state space.
* A policy gradient method can be used to make deal with continuous action and state spaces.
* A different machine learning technique such as neural nets can be applied.

