# robo
1) The first stage begins with an omni-directional robot parked in front of a table. The four legs of the table are visible to the Lidar sensor at the centre of the robot.
2) In the second stage, the robot will then find its way to go underneath the table, and it will align and center itself within 4 legs of the table as shown in the picture attached. Additionally the robot will response to the movement of the table accordingly.

### Prerequisites

1) Install ROS Kinetic with ubuntu 16.04.

### Instructions

1) create a workspace <br />
$ mkdir -p ~/catkin_ws/src <br />
$ cd ~/catkin_ws/src <br />
$ catkin_init_workspace <br />
$ cd .. <br />
$ catkin_make <br />
   
2) Clone the project and launch <br />
$ cd ~/catkin_ws/src <br />
$ git clone https://github.com/rvipin17/robo.git <br />
$ cd .. <br />
$ catkin_make <br />
$ source ~/catkin_ws/devel/setup.bash <br />
$ roslaunch robo robo.launch <br />

3) Now you will see robot getting inside the robot. Please change the table position, the robot will respond accordingly. 


Thank You. 
