#include "std_msgs/Int16.h"
  #include "std_msgs/String.h"
#include "std_msgs/Bool.h"
  #include "geometry_msgs/Twist.h"
  #include "sound_play/sound_play.h"
 
  int inicio = 0;
  int rotate = 0;
  int turn = 0;
  int start = 0;
  int stop = 1;
  float linear_vel = 0.0;
  float angular_vel = 0.0;
  std_msgs::String comando_voz;  
  ros::Publisher follow_it;
 
  void sleepok(int t, ros::NodeHandle &n)
  {
       if (n.ok())
               sleep(t);
  }
 
  void speech(const std_msgs::String& voz)
  {
  	ros::NodeHandle n;  
        ::comando_voz = voz;
	sound_play::SoundClient voz_robot;
         
        ros::Publisher move_base_pub_=n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1);
      
        std_msgs::Int16 objeto;
        geometry_msgs::Twist mover_base;
             
        if (::comando_voz.data == "timmy")
        {
                inicio = 1;
		ROS_INFO("timmy detected");
                               
        }
        else if (::comando_voz.data == "slebhijby")
        {
                inicio = 0;
                               
        }
        else if (inicio == 1)
        {
                if (::comando_voz.data == "stop")
                {
                        ::linear_vel = 0.0;
                        ::angular_vel = 0.0;
			ROS_INFO("Applying Brakes. Halted");
		        voz_robot.say("Applying Brakes. Halted");
			sleepok(4, n);
                       
                }
                else if (::comando_voz.data == "move forward")
                {
			::linear_vel = 0.1;
                        ::angular_vel = 0.0;
                       ROS_INFO("Aye AYe Sir, Moving Forward");
		       voz_robot.say("Aye AYe Sir, Moving Forward");
			sleepok(4, n);
                        
                       
                }
                else if (::comando_voz.data == "move backward")
                {
			::linear_vel = -0.1;
                        ::angular_vel = 0.0;
                       ROS_INFO("Aye AYe Sir, Moving Reverse");
		       voz_robot.say("Aye AYe Sir, Moving Reverse");
			sleepok(4, n);
                        
                       
                }      
                else if (::comando_voz.data == "turn left")
                {
			ROS_INFO("Turning Left Now");
		        voz_robot.say("Turning Left Now");
			sleepok(4, n);
                        if (::angular_vel <= 0 || ::rotate == 1)
                        {
                                ::angular_vel = 0.1;
                               
                                ::rotate = 0;
                                ::turn = 1;    
                                
                        }
                        else
                        {
                       
                                ::angular_vel = ::angular_vel + 0.1;

                        }
                }
                else if (::comando_voz.data == "turn right")
                {
			ROS_INFO("Turning Right Now");
		        voz_robot.say("Turning Right Now");
			sleepok(4, n);
                        if (::angular_vel >= 0 || ::rotate == 1)
                        {
                                ::angular_vel = -0.1;
                               
                                ::rotate = 0;
                                ::turn = 1;                            
                        }
                        else
                        {
               
                                 ::angular_vel = ::angular_vel - 0.1;

                        }
                }
                else if (::comando_voz.data == "rotate left")
                {
			ROS_INFO("Rotating Counter Clockwise");
		        voz_robot.say("Rotating Counter Clockwise");
			sleepok(4, n);
                        if (::angular_vel <= 0 || ::turn == 1)
                        {
                                ::angular_vel = 0.1;
                               
                                ::turn = 0;
                                ::rotate = 1;
                        }
                       
                        ::linear_vel = 0.0;
                       
                }
                else if (::comando_voz.data == "rotate right")
                {
			ROS_INFO("Rotating Clockwise");
		        voz_robot.say("Rotating Clockwise");
			sleepok(4, n);
                        if (::angular_vel >= 0 || ::turn == 1)
                        {
                                ::angular_vel = -0.1;
                               
                                ::turn = 0;
                                ::rotate = 1;                          
                        }
                       
                        ::linear_vel = 0.0;

                }              
                else if (::comando_voz.data == "speed up")                             
                {
			ROS_INFO("Increasing my speed");
		        voz_robot.say("Increasing my speed");
			sleepok(4, n);
                        if (::linear_vel == 0)
                        {
                                if (::angular_vel > 0 && ::rotate == 1)
                                {
                                        ::angular_vel= ::angular_vel + 0.05;
                                }
                                else if (::rotate == 1)
                                {
                                        ::angular_vel = ::angular_vel - 0.05;
                                }                      
                        }
                        else
                        {
                                if (::linear_vel > 0)
                                {
                                        ::linear_vel = ::linear_vel + 0.05;
                                }
                                else
                                {
                                        ::linear_vel = ::linear_vel - 0.05;
                                }
                        }
                }
                else if (::comando_voz.data == "slow down")                            
                {
			ROS_INFO("Decreasing my speed");
		        voz_robot.say("Decreasing my speed");
			sleepok(4, n);
                        if (::linear_vel == 0)
                        {
                                if (::angular_vel > 0 && ::rotate == 1)
                                {
                                        ::angular_vel = ::angular_vel - 0.05;
                                }
                                else if (::rotate == 1)
                                {
                                        ::angular_vel = ::angular_vel + 0.05;
                                }                                      
                        }
                        else
                        {
                                if (::linear_vel > 0)
                                {
                                        ::linear_vel = ::linear_vel - 0.05;
                                }
                                else
                                {
                                        ::linear_vel = ::linear_vel + 0.05;
                                }                      
                        }
                }
				else if(::comando_voz.data == "what are you"){
					ROS_INFO("I am ROS Based robot, a part of idris system.");
					voz_robot.say("I am ROS Based robot, a part of idris system.");
					sleepok(4, n);
					
				}
				else if(::comando_voz.data == "who are you"){
					ROS_INFO("I am Timmy.");
					voz_robot.say("I am Timmy.");
					sleepok(4, n);
				}
				else if(::comando_voz.data == "how are you"){
					ROS_INFO("I am fine and working.");
					voz_robot.say("I am fine and working.");
					sleepok(4, n);
				}
				else if(::comando_voz.data == "follow me"){
					
					sleepok(2, n);
					std_msgs::Bool c;
					c.data = 1;
					follow_it.publish(c);
					
				}
				else if(::comando_voz.data == "sleep")
				{
					std_msgs::Bool c;
					c.data = 0;
					follow_it.publish(c);
				}
				else if(::comando_voz.data == "register")
				{
					c.data = 0;
					follow_it.publish(c);
				}
                                                       
                                                                                                              
        }
  }
     
  int main(int argc, char **argv)
  {
         
        ros::init(argc, argv, "control_voz");  

  	ros::NodeHandle n;  
 
        ros::Subscriber speech_sub_= n.subscribe("/recognizer/output", 1, speech);
       
         
        ros::Publisher move_base_pub_=n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1);

	follow_it=n.advertise<std_msgs::Bool>("follow_command", 1);


             
       
        ros::Rate loop_rate(10);
       
        geometry_msgs::Twist mover_base;
       
        sound_play::SoundClient voz_robot;
       
                sleepok(1, n);        
       
        while (ros::ok())
        {              
                        mover_base.linear.x = ::linear_vel;
                        mover_base.angular.z = ::angular_vel;
                       
                        move_base_pub_.publish(mover_base);
                       
                        if (::comando_voz.data == "timmy" && ::start == 0)
                        {
                                voz_robot.say("Ass slam aly kum sir. How can I be of assistance");
				ROS_INFO("Ass slam aly kum sir. How can I be of assistance");
                               
                                sleepok(4, n);
                               
                                ::start = 1;
                                ::stop = 0;
                        }
                        else if (::comando_voz.data == "sleep" && ::stop == 0)
                        {
                                voz_robot.say("Good Bye Sir");
				ROS_INFO("Good Bye Sir");
                               
                                sleepok(4, n);
                               
                                ::stop = 1;
                                ::start = 0;
                        }                      
                       
                        ros::spinOnce();
       
                        loop_rate.sleep();                     
       
                }                    
       
        ros::spin();  
 
        return 0;
  }