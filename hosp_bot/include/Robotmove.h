#include "ros/ros.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cmath>
#include "move_base_msgs/MoveBaseGoal.h"
#include <move_base_msgs/MoveBaseAction.h>
#include "geometry_msgs/Pose.h"
#include <actionlib/client/simple_action_client.h>
#include "boost/thread.hpp"
#include "std_msgs/Int32.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include <fstream>
#include "hosp_bot/info_req.h" 
#include <nav_msgs/Odometry.h> 
#include <unistd.h>

using namespace std;
	
struct QR_POS {
  float pos_x;
  float pos_y;
  float or_z;
  float or_w;
  string qr;
} ;

struct BOT {
  int cargo = 0;   
  int type = 0 ;    // 1 = food , 2= med
  int room = -1 ;
  bool status = true ;     // false se ha richieste, true se non ha richieste
  bool travel = false ;      // false se non viaggia, true se viaggia
  float battery ;
  bool lowlvl;
  bool gotochar;
  bool deliv;
  bool find = false;
  string qr ;
} ;

struct ReQ {
  int med = 0;
  int food = 0;
  int room = -1;
} ;

struct Extra {
  int med = 0;
  int food = 0;
  int room = -1;
  bool req=false;  // false non ci sono richieste in coda
} ;

QR_POS Qr_pos [12];
BOT Robot_ [1];
Extra Delivery [100];
ReQ REQ [1];

class hospitalRobot {

		
	private:

		ros::NodeHandle _nh;
		ros::Subscriber _barcode_sub_1;
		ros::Subscriber _barcode_sub_2;
		ros::Subscriber _odom_sub_1;
		ros::Subscriber _odom_sub_2;

		
	
	public:
		string input;
		hospitalRobot();
		bool First_bat = true;
		bool First_start_1 = true;
		bool First_start_2 = true;
		bool First_odom_1 = true;
		bool First_odom_2 = true; 
		int Tot_med=10;
		int Tot_food=10;
		int Full;
		int Lowlvl=50;	
		int charg_1=11;
		int charg_2=11;
		int step=0;
		int NRoom =3;
		int dir_2;
		bool Old = false;  //false se la stanza è diversa
		int dir_1;
		int med;
		int food;
		int room;
		bool news = false;
		bool Deposito = false;
		bool Occuped = false;
		bool recharg = false;	
		int me= 0;
		int fo= 0;
		int ro= -1;	
		float p[4];
		float g[4];
		float Distanza_robot_1 = 0;
		float Distanza_robot_2 = 0;

		move_base_msgs::MoveBaseGoal goal;

		bool Navigation (int robot, float xGoal, float yGoal , float zGoal, float wGoal);
		void Initialization();
		void Sorting ();
		void barcode_cb_1( std_msgs::StringConstPtr code );
		void barcode_cb_2( std_msgs::StringConstPtr code );
		void odom_cb_1( nav_msgs::OdometryConstPtr odom_1 );
		void odom_cb_2( nav_msgs::OdometryConstPtr odom_2 );
		void DeliveryList(int me, int fo, int ro);
		void UpdateDevList ();
		void PrintDevList ();
		void Traveling_1 ();
		void Traveling_2 ();
		bool Check (int me, int fo);
		void run ();
		void Oldcall ();
		void Battery1 ();
		void Battery2 ();
		void Print_status ();
		void GoToCharge_1 ();
		void GoToCharge_2 ();
		void Reset (int rob);
		bool Verify (int robot, int pos);
		void Verify_room (int robot, int pos);
		void Verify_pkg (int robot, int pos);
	
};

class Request_info {

	private:

		ros::NodeHandle nh;
		ros::ServiceServer _request_serv;

	public:
	
	Request_info(){		
			_request_serv= nh.advertiseService("richieste_invio", &Request_info::request_callback, this);	
	}
	
	bool request_callback (hosp_bot::info_req::Request &req, hosp_bot::info_req::Response &res) {
						
			REQ[0].med=req.meds;
			REQ[0].food=req.food;
			REQ[0].room=req.room;
			res.ok=true;
			
			return true;
		}

};

