#pragma once

#include <ros/ros.h>
#include <string>
#include <math.h>
#include <geometry_msgs/Twist.h>

#include "sensor_msgs/LaserScan.h"

namespace husky_highlevel_controller {

/*!
 * Class containing the Husky Highlevel Controller
 */
class HuskyHighlevelController {
public:
	/*!
	 * Constructor.
	 */
	HuskyHighlevelController(ros::NodeHandle& nodeHandle);

	/*!
	 * Destructor.
	 */
	virtual ~HuskyHighlevelController();

private:

	bool readParameters();
	void scanCallback(const sensor_msgs::LaserScan& msg);

	ros::NodeHandle& nodeHandle;

	//variable declarations related to subscriber
	ros::Subscriber subscriber;
	std::string scanTopicName;
	int scanTopicQueueSize;

	//variable declarations realated to publisher
	ros::Publisher pubCmdVel;
	std::string pubTopicName;
	int pubTopicQueueSize;
	geometry_msgs::Twist velMsg;

	bool side;
};

} /* namespace */
