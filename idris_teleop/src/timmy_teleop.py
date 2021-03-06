#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
import math

vel_pub = 0
update_flag = False
twist = Twist()


def turtle_teleop_callback(data):
	global vel_pub
	global twist
	global update_flag
	rospy.loginfo('Interrupt Received for teleop')
	speed = 200
	twist = Twist()
	if data.linear.x == 2.0:
		twist.linear.x = speed
		twist.linear.y = speed
	elif data.linear.x == -2.0:
		twist.linear.x = -speed
		twist.linear.y = -speed
	elif data.angular.z == -2.0:
		twist.linear.x = -speed
		twist.linear.y = speed
	elif data.angular.z == 2.0:
		twist.linear.x = speed
		twist.linear.y = -speed	
	update_flag = True


def initTeleop():
	global vel_pub
	global twist
	global update_flag
	rospy.init_node('timmy_teleop', anonymous=True)
	vel_pub = rospy.Publisher('robot_velocity', Twist, queue_size=10)
	rospy.Subscriber("/turtle1/cmd_vel", Twist, turtle_teleop_callback)
	rospy.loginfo('Teleop Node Initialised...')
	rate = rospy.Rate(10)
	stop_flag = False
	while not rospy.is_shutdown():
		if update_flag:
			rospy.loginfo(twist.linear.x)	
			rospy.loginfo(twist.linear.y)	
			vel_pub.publish(twist)
			update_flag = False
			stop_flag = True

		elif stop_flag:
			twist.linear.x = 0
			twist.linear.y = 0
			rospy.loginfo(twist.linear.x)	
			rospy.loginfo(twist.linear.y)
			vel_pub.publish(twist)
			stop_flag = False
		rate.sleep()
		
 
if __name__ == '__main__':
	initTeleop()
