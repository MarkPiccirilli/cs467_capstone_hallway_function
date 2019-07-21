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
	
}

} /* namespace */
