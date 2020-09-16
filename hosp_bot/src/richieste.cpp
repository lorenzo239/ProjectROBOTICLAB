#include "ros/ros.h"
#include "hosp_bot/info_req.h"
#include <iostream>
#include <stdlib.h>

using namespace std;


int main(int argc, char** argv ) {

	ros::init(argc, argv, "richieste_invio");
	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<hosp_bot::info_req>("richieste_invio");
	hosp_bot::info_req msg;

	int temp =0;
	string input;
	
	while (ros::ok()) {
	cout <<endl<< "Premere invio per richiesta casuale" << endl;
	
	
				
		getline( cin, input);

		msg.request.room = rand()%3;
		
		if (temp!=msg.request.room){

			msg.request.food = rand()%3;

			if (msg.request.food == 0){
			msg.request.meds = rand()%5;
			}
			if (msg.request.food == 2){
			msg.request.meds =0;			
			}
			else {msg.request.meds = rand()%3;}

			cout <<"La stanza "<<msg.request.room+1<<" ha richiesto :"<<endl;
			cout <<msg.request.food<<" quantità di cibo"<<endl;
			cout<<msg.request.meds<<" quantità di medicine"<<endl;
   			temp=msg.request.room;	 	
		}

		
	
	if(client.call(msg)) {
		cout<<endl<<"Request sent!"<<endl;
		} else {
		ROS_ERROR("Failed to send request!");
		
	}

	}
	return 0;
}


