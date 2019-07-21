#include "husky_highlevel_controller/HuskyHighlevelController.hpp"

namespace husky_highlevel_controller {

HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle& nodeHandle) :
  nodeHandle(nodeHandle)
{
	//read parameters
	if(!readParameters()) {
		ROS_ERROR("Could not find topic parameter!");
		ros::requestShutdown();
	}
	
	//launch subscriber
	subscriber = nodeHandle.subscribe(scanTopicName, scanTopicQueueSize, &HuskyHighlevelController::scanCallback, this);
	//launch publisher
	pubCmdVel = nodeHandle.advertise<geometry_msgs::Twist>(pubTopicName, pubTopicQueueSize);
	ROS_INFO("Node has been launched successfully");
}


HuskyHighlevelController::~HuskyHighlevelController()
{
}

bool HuskyHighlevelController::readParameters() {
	//get scan topic name parameter
	if(!nodeHandle.getParam("scanTopicName", scanTopicName)) {
		return false;
	}

	//get scan topic queue parameter
	if(!nodeHandle.getParam("scanTopicQueueSize", scanTopicQueueSize)) {
		return false;
	}

	//get publisher topic name parameter
	if(!nodeHandle.getParam("pubTopicName", pubTopicName)) {
		return false;
	}
 
	//get publisher queue size parameter
	if(!nodeHandle.getParam("pubTopicQueueSize", pubTopicQueueSize)) {
		return false;
	}	

	return true;
}

void HuskyHighlevelController::scanCallback(const sensor_msgs::LaserScan& msg) {
	//create a vector of the ranges from the Laser Scan msg
	std::vector<float> ranges = msg.ranges;
	
	/* exercise 2 code
	//initailze the variable to hold the smallest range
	float smallest = ranges[0];
	//calculate the smallest range
	for(float i : ranges) {
		if(i < smallest) {
			smallest = i;
		}
	}

	//print the smallest range
	ROS_INFO_STREAM("Smallest Range: " << std::to_string(smallest));
	*/
	
	//int size = sizeof(ranges)/sizeof(ranges[0]);

	int size = 0;
	for(float i : ranges) {
		size++;
	}

	float left = ranges[120];
	float right = ranges[600];

	//the min max and step data was printed and used to calculate the 120 and 600 indexes to fined the left and right wall distance
	//ROS_INFO_STREAM("min: " << msg.angle_min << " max: " << msg.angle_max << " step: " << msg.angle_increment);

	ROS_INFO_STREAM("left: " << left << " Right: " << right << " size: " << size << std::endl);
	
	ROS_INFO_STREAM("side: " << side);

	//if robot is in the center, go straight forward
	if (abs(left - right) < .7) {
		if(side) { //right side
			if(left - right > 0) { //before center point
				velMsg.linear.x = 1;
				velMsg.angular.z = (right - left) * .3;
				ROS_INFO("TEST 1"); //testing code
			}
			else { //after center point
				velMsg.linear.x = 1;
				velMsg.angular.z = 0;
				ROS_INFO("TEST 2"); //testing code
			}
		}		
		else { //left side
			if(left - right < 0) { //before center point
				velMsg.linear.x = 1;
				velMsg.angular.z = (right - left) * .3;
				ROS_INFO("TEST 1"); //testing code
			}
			else { //after center point
				velMsg.linear.x = 1;
				velMsg.angular.z = 0;
				ROS_INFO("TEST 2"); //testing code
			}

		}
	}
	//if robot is not in center, move towards center
	else {
		if(left - right < 0) { //left side
			side = false;
		}
		else { //right side
			side = true;
		}
		velMsg.linear.x = .7;
		velMsg.angular.z = (left - right) * .03;
		ROS_INFO_STREAM("l-r: " << left - right << std::endl); //testing code
	}

	//publish command velocity
	pubCmdVel.publish(velMsg);
}

} /* namespace */
