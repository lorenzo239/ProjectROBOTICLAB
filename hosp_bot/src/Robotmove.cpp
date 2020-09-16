#include "../include/Robotmove.h"

void hospitalRobot::Initialization(){
	
	double sq2_2 = sqrt(2)/2.0;	

	for (int i=0; i==100; i++){
		Delivery[i].med=0;
		Delivery[i].food=0;
		Delivery[i].room=-1;
		Delivery[i].req=false;
	}

	for (int i=0; i==4; i++){
		p[i]=0;
		g[i]=0;
	}	
	
	Robot_[0].status = true;
	Robot_[1].status = true;
	
	//Stock BASE
	Qr_pos[0].pos_x =15.50;
	Qr_pos[0].pos_y =-11.05;
	Qr_pos[0].or_z = 0;
	Qr_pos[0].or_w = 1;
	Qr_pos[0].qr = "Base";

	//Stock STANZA 1	
	Qr_pos[1].pos_x =1.37;
	Qr_pos[1].pos_y =4.90;
	Qr_pos[1].or_z = -sq2_2;
	Qr_pos[1].or_w = -sq2_2;
	Qr_pos[1].qr = "Room 1";
 
	//Stock STANZA 2
	Qr_pos[2].pos_x =15.20;
	Qr_pos[2].pos_y =4.90;
	Qr_pos[2].or_z = -sq2_2;
	Qr_pos[2].or_w = -sq2_2;
	Qr_pos[2].qr = "Room 2";
 
	//Stock STANZA 3
	Qr_pos[3].pos_x =22.70;
	Qr_pos[3].pos_y =4.90;
	Qr_pos[3].or_z = -sq2_2;
	Qr_pos[3].or_w = -sq2_2;
	Qr_pos[3].qr = "Room 3";
 
	//Stock STANZA 1.1
	Qr_pos[4].pos_x =3.14;
	Qr_pos[4].pos_y =16.80;
	Qr_pos[4].or_z = -sq2_2;
	Qr_pos[4].or_w = -sq2_2;
	Qr_pos[4].qr = "Release";
 
	//Stock STANZA 2.1
	Qr_pos[5].pos_x =13;
	Qr_pos[5].pos_y =16.80;
	Qr_pos[5].or_z = -sq2_2;
	Qr_pos[5].or_w = -sq2_2;
	Qr_pos[5].qr = "Release";
 
	//Stock STANZA 3.1
	Qr_pos[6].pos_x =24;
	Qr_pos[6].pos_y =16.80;
	Qr_pos[6].or_z = -sq2_2;
	Qr_pos[6].or_w = -sq2_2;
	Qr_pos[6].qr = "Release";
 
	//Stock MEDICINE 
	Qr_pos[7].pos_x =21.13;
	Qr_pos[7].pos_y =-16.87;
	Qr_pos[7].or_z = -sq2_2;
	Qr_pos[7].or_w = sq2_2;
	Qr_pos[7].qr = "Medicine";
 
	//Stock CIBO
	Qr_pos[8].pos_x =26.80;
	Qr_pos[8].pos_y =-7.70;
	Qr_pos[8].or_z = 0;
	Qr_pos[8].or_w = 1;
	Qr_pos[8].qr = "Food";
 
	//Stock MAGAZINO 1
	Qr_pos[9].pos_x = 4;
	Qr_pos[9].pos_y = -4.5;
	Qr_pos[9].or_z = 0;
	Qr_pos[9].or_w = 1;
	Qr_pos[9].qr = "4";
 
	//Stock MAGAZINO 2
	Qr_pos[10].pos_x = 22.5;
	Qr_pos[10].pos_y = 2;
	Qr_pos[10].or_z = -sq2_2;
	Qr_pos[10].or_w = sq2_2;
	Qr_pos[10].qr = "4";
 
	//Stock RICARICA
	Qr_pos[11].pos_x = 10;
	Qr_pos[11].pos_y = -17.50;
	Qr_pos[11].or_z = -sq2_2;
	Qr_pos[11].or_w = -sq2_2;
 

}


hospitalRobot::hospitalRobot(){
			_barcode_sub_1 = _nh.subscribe( "/robot1/qr_codes", 0, &hospitalRobot::barcode_cb_1, this );
			_barcode_sub_2 = _nh.subscribe( "/robot2/qr_codes", 0, &hospitalRobot::barcode_cb_2, this );
			_odom_sub_1 = _nh.subscribe( "/robot1/odom", 0, &hospitalRobot::odom_cb_1, this );
			_odom_sub_2 = _nh.subscribe( "/robot2/odom", 0, &hospitalRobot::odom_cb_2, this );
			}



void hospitalRobot::odom_cb_1( nav_msgs::OdometryConstPtr odom_1) {
	
	if (First_odom_1 == true && odom_1->pose.pose.position.x != 0 && odom_1->pose.pose.position.y != 0){
		p[0] = odom_1->pose.pose.position.x;
		p[1] = odom_1->pose.pose.position.y;
		Distanza_robot_1 = 0;
		First_odom_1 = false;
	}
	
	if (First_odom_1 == false) {	
	p[2] = odom_1->pose.pose.position.x;
	p[3] = odom_1->pose.pose.position.y;
	
	Distanza_robot_1 = sqrt ( ((p[2]-p[0])*(p[2]-p[0])) + ((p[3]-p[1])*(p[3]-p[1])) ) + Distanza_robot_1;	
	p[0] = p[2];
	p[1] = p[3];	

	}
		
} 

void hospitalRobot::odom_cb_2( nav_msgs::OdometryConstPtr odom_2) {

if (First_odom_2 == true && odom_2->pose.pose.position.x != 0 && odom_2->pose.pose.position.y != 0){
		g[0] = odom_2->pose.pose.position.x;
		g[1] = odom_2->pose.pose.position.y;
		Distanza_robot_2 = 0;
		First_odom_2 = false;
	}
	
	if (First_odom_2 == false) {	
	g[2] = odom_2->pose.pose.position.x;
	g[3] = odom_2->pose.pose.position.y;
	
	Distanza_robot_2 = sqrt ( ((g[2]-g[0])*(g[2]-g[0])) + ((g[3]-g[1])*(g[3]-g[1])) ) + Distanza_robot_2;	
	
	g[0] = g[2];
	g[1] = g[3];	

	}
	
} 

void hospitalRobot::barcode_cb_1( std_msgs::StringConstPtr code ) {
	if (Robot_[0].qr != code->data){Robot_[0].qr = code->data ;}	
        
}

void hospitalRobot::barcode_cb_2( std_msgs::StringConstPtr code ) {
	if (Robot_[1].qr != code->data){Robot_[1].qr = code->data ;}
}


bool hospitalRobot::Verify (int robot, int pos){

	if (Robot_[robot].qr == Qr_pos[pos].qr){
		return true;	
	}
	else {return false;}

}


void hospitalRobot::Verify_room (int robot, int pos){
	do {
		if (Verify(robot,Robot_[robot].room+1)==true){Robot_[robot].find=true; cout << "[ROBOT "<<robot<<" INFO] Room "<<Robot_[robot].room+1<<" trovata"<<endl;}	
		else {		
			Robot_[robot].find=false; cout << "[ROBOT "<<robot<<" INFO] Room "<<Robot_[robot].room+1<<" non trovata, destinazione stanza successiva."<<endl;
			pos = pos-1;
			if (robot == 0){dir_1=pos;}
			if (robot == 1){dir_2=pos;}
			Navigation (robot, Qr_pos[pos].pos_x,Qr_pos[pos].pos_y, Qr_pos[pos].or_z ,Qr_pos[pos].or_w);
		}
	}while (Robot_[robot].find!=true);
	
}


void hospitalRobot::Verify_pkg (int robot, int pos){
	
	if (Verify(robot,pos)==true){Robot_[robot].find=true;}
	else {		
		Robot_[robot].find=false;
		
		if (pos == 7){pos = 8;}
		else if (pos == 8){pos = 7;}
		Navigation (robot, Qr_pos[pos].pos_x,Qr_pos[pos].pos_y, Qr_pos[pos].or_z ,Qr_pos[pos].or_w);
		if (Verify(robot,pos)==true){Robot_[robot].find=true;}
		else {Robot_[robot].find=false;}
	}
}



void hospitalRobot::Print_status (){
	cout <<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
	
	step=step+1;
	cout << "STEP :  "<<step<<endl<<endl;	
	cout << setprecision(2) << fixed;
	if (news==true){
		cout<< endl<<endl;
		cout << "* * * NUOVA RICHIESTA "<<endl;
	
		cout <<endl<<"Room : "<< REQ[0].room+1 << "     Medicine : "<< REQ[0].med<<"       Food :"<<REQ[0].food<<endl;
		cout <<"Verifica disponibilità magazino : " ;
		if (Deposito == true){cout<<"Sufficiente"; cout<<endl;}
		if (Deposito == false){cout <<"Insufficiente"; cout<<endl;}
		cout << "Restanti"<<endl;
		cout << "Medicine disponibili : "<<Tot_med<<endl;
		cout << "Cibo disponibile : "<<Tot_food<<endl;
	
		news=false;
	}

	
	
	cout <<endl<<endl;
	cout <<"ROBOT 1 "<<endl<<endl<<" Status : ";
	if (Robot_[0].status == true) {cout << "Disponibile";cout << "               Level Battery : "<<Robot_[0].battery<<" m "<<endl;}
	if (Robot_[0].status == false) {cout << "In servizio";cout << "               Level Battery : "<<Robot_[0].battery<<" m "<<endl;
		if (Robot_[0].lowlvl==true) {cout<<"* Attenzione Batteria Scarica *"<<endl;}
		if (Robot_[0].gotochar==true){cout<<" Destinazione Base di ricarica"<<endl;
			if(dir_1>-1 && dir_1<12){
				cout<<"      Coordinate Base : " <<Qr_pos[dir_1].pos_x<<" , "<<Qr_pos[dir_1].pos_y <<endl;}
		}
		cout <<endl;
		if (Robot_[0].deliv == true){
			cout <<"* Destinazione stanza: "<<Robot_[0].room+1<<endl;
			cout <<"  Tipologia : ";
			if (Robot_[0].type == 1 ){cout<<"Cibo";}
			if (Robot_[0].type == 2 ){cout<<"Medicine";}
			cout <<"         Quantità : "<<Robot_[0].cargo << endl;
	
		}

		if (Robot_[0].deliv == false){cout<<"* * Destinazione BASE"<<endl;}
		if(dir_1>-1 && dir_1<12){cout<<"- Coordinate : " <<Qr_pos[dir_1].pos_x<<" , "<<Qr_pos[dir_1].pos_y<<endl;
			if (dir_1 != 0) {cout<<"                    QR da riconoscere : "<<Qr_pos[dir_1].qr	<<endl;
			cout<<"                    QR riconosciuto :   "<<Robot_[0].qr;
			if (Qr_pos[dir_1].qr == Robot_[0].qr){cout<<"    -> Confermato";}
			else {cout<<"    -> In ricerca";}	
			if (Robot_[0].find==true){cout<<endl<<"Situato avanti al robot";}}
		}
	}

	cout <<endl<<endl;
	cout <<"ROBOT 2"<<endl<<endl<<" Status : ";
	if (Robot_[1].status == true) {cout << "Disponibile";cout << "               Level Battery : "<<Robot_[1].battery<<" m "<<endl;}
	if (Robot_[1].status == false) {cout << "In servizio";cout << "               Level Battery : "<<Robot_[1].battery<<" m "<<endl;
		if (Robot_[1].lowlvl==true) {cout<<"* Attenzione Batteria Scarica *"<<endl;}
		if (Robot_[1].gotochar==true){cout<<" Destinazione Base di ricarica"<<endl;
			if(dir_2>-1 && dir_2<12){
				cout<<"      Coordinate Base : " <<Qr_pos[dir_2].pos_x<<" , "<<Qr_pos[dir_2].pos_y <<endl;}
		}
		cout <<endl;
		if (Robot_[1].deliv == true){
			cout <<"* Destinazione stanza: "<<Robot_[1].room+1<<endl;
			cout <<"  Tipologia : ";
			if (Robot_[1].type == 1 ){cout<<"Cibo";}
			if (Robot_[1].type == 2 ){cout<<"Medicine";}
			cout <<"         Quantità : "<<Robot_[1].cargo << endl;
		}
		if (Robot_[1].deliv == false){cout<<"* * Destinazione BASE"<<endl;}
		if(dir_2>-1 && dir_2<12){cout<<"- Coordinate : " <<Qr_pos[dir_2].pos_x<<" , "<<Qr_pos[dir_2].pos_y <<endl;
			if (dir_2!= 0){cout<<"                    QR da riconoscere : "<<Qr_pos[dir_2].qr<<endl;
			cout<<"                    QR riconosciuto :   "<<Robot_[1].qr;
			if (Qr_pos[dir_2].qr == Robot_[1].qr){cout<<"    -> Confermato";}
			else {cout<<"    -> In ricerca";}
			if (Robot_[1].find==true){cout<<endl<<"Situato avanti al robot";}}
		}
	}
	cout<<endl<<endl;
	if (Occuped == true && Delivery[0].req==true) {PrintDevList ();}
	cout <<endl;
	ros::Duration(1).sleep();
}



bool hospitalRobot::Check (int me, int fo) {

	
	if (Old == true){return true;}
	if (me<Tot_med && fo<Tot_food){
		if (me<Tot_med){
		Tot_med = Tot_med - me;
		}	

		if (fo<Tot_med){
		Tot_food = Tot_food - fo;
		}
		Deposito = true;
		return true;
	}
	
	else{
	Deposito= false;
	return false;
	}
	
}



void hospitalRobot::Battery1 (){
		if (First_bat==true) {
			Robot_[0].battery = Full;
			Robot_[0].lowlvl = false;
			Robot_[0].gotochar = false;
 			Robot_[1].battery = Full; 
			Robot_[1].lowlvl = false;
			Robot_[1].gotochar = false;
			First_bat=false;
			}

		Robot_[0].battery = Full - Distanza_robot_1;
	
		if (Robot_[0].battery < Lowlvl ){
		Robot_[0].lowlvl=true;
		}
	}
		
void hospitalRobot::Battery2 (){
		Robot_[1].battery = Full - Distanza_robot_2;;
	
		if (Robot_[1].battery<Lowlvl ){
		Robot_[1].lowlvl=true;
		}
	}

void hospitalRobot::PrintDevList (){
	cout <<endl;
	cout <<"Robot 1 e Robot 2 in servizio"<<endl;
	cout << "Richieste in attesa : "<<endl;

  	int x=0;
	cout<<endl;
	do{	
		cout<<"* Richiesta numero "<< x+1<<endl;
		cout<<"    Stanza : "<< Delivery[x].room +1 <<endl;
		if (Delivery[x].food>0){cout<<"    Food : "<< Delivery[x].food <<endl;}
		if (Delivery[x].med>0){cout<<"    Medicine : " << Delivery[x].med <<endl;}
		cout <<endl;

		x=x+1;

	}while (Delivery[x].req==true);

		
}


void hospitalRobot::GoToCharge_1 (){
	
	if(Robot_[0].lowlvl==true){
		Robot_[0].gotochar = true;
		Navigation (0, Qr_pos[charg_1].pos_x,Qr_pos[charg_1].pos_y, Qr_pos[charg_1].or_z ,Qr_pos[charg_1].or_w);
		ros::Duration(2).sleep();
		Robot_[0].lowlvl=false;
		Robot_[0].battery=Full;
		First_odom_1 = true ;
		Robot_[0].gotochar =false;
	}	

}

void hospitalRobot::GoToCharge_2 (){

	if(Robot_[1].lowlvl==true){
		Robot_[1].gotochar =true;
		Navigation (1, Qr_pos[charg_2].pos_x,Qr_pos[charg_2].pos_y, Qr_pos[charg_2].or_z ,Qr_pos[charg_2].or_w);
		ros::Duration(2).sleep();		
		Robot_[1].lowlvl=false;
		Robot_[1].battery=Full;
		First_odom_2 = true ;
		Robot_[1].gotochar =false;
		
	}	
	
}


void hospitalRobot::UpdateDevList (){
	int x=0;
	
	do{
		Delivery[x].med = Delivery[x+1].med;
		Delivery[x].food = Delivery[x+1].food;
		Delivery[x].room = Delivery[x+1].room;
		Delivery[x].req = Delivery[x+1].req;
	
		x=x+1;
		
	}while (Delivery[x].req==true);
	
	
	if (Delivery[0].req==false){Occuped=false;}

}



void hospitalRobot::DeliveryList(int me, int fo, int ro){

int x=0;
bool Insert=false;


	do{
		if (Delivery[x].req == false){Insert=true;}
		else {x=x+1;}
	}while (Insert==false);
		
	if (Delivery[x].req==false){
		Delivery[x].med=me;
		Delivery[x].food=fo;
		Delivery[x].room=ro;
		Delivery[x].req=true;
	}

	Occuped = true;
}

void hospitalRobot::Oldcall (){
	REQ[0].med = 0;
	REQ[0].food = 0;
	REQ[0].room = -1;
	REQ[0].med = Delivery[0].med;
	REQ[0].food = Delivery[0].food;
	REQ[0].room = Delivery[0].room;

	UpdateDevList();
	Old = true;  

};

void hospitalRobot::Sorting (){
	
if (Delivery[0].req==true && (Robot_[0].status == true || Robot_[1].status == true)) {Oldcall ();}	
		


if ( (ro!=REQ[0].room || Old == true) && REQ[0].room!= -1)	{	
	news = true;
	me=REQ[0].med;
	fo=REQ[0].food;
	ro=REQ[0].room;
	
	

if (hospitalRobot::Check (me,fo)==true ||  Old == true){
	
		

	if (Robot_[0].status == false && Robot_[1].status == false){
		DeliveryList(me,fo,ro);	
		PrintDevList();
	}
	
	if (Robot_[0].status == true && Robot_[1].status == true){
		
		if (fo>1 && me ==0){
			Robot_[0].cargo = 1;
			Robot_[0].type = 1;
			Robot_[0].status = false;
			Robot_[0].room = ro;
			
			Robot_[1].cargo = 1;
			Robot_[1].type = 1;
			Robot_[1].status = false;
			Robot_[1].room = ro;
			
			if (fo-2>0){
   			DeliveryList(me, fo-2,ro);			
			}
		}


		if (me>2 && fo == 0){
			Robot_[0].cargo = 2;
			Robot_[0].type = 2;
			Robot_[0].status = false;
			Robot_[0].room = ro;
		
			Robot_[1].cargo = me-2;
			Robot_[1].type = 2;
			Robot_[1].status = false;
			Robot_[1].room = ro;

			if (me-4>0){
   			DeliveryList(me-4, fo,ro);			
			}
		}
		
		else {	
			
			Robot_[1].cargo = me;
			Robot_[1].type = 2;
			Robot_[1].status = false;
			Robot_[1].room = ro;
			
			
			Robot_[0].cargo = fo;
			Robot_[0].type = 1;
			Robot_[0].status = false;
			Robot_[0].room = ro;
			

			if (fo-1>0 || me-2>0){
   			DeliveryList(me-2, fo-1,ro);			
			}
		}
	}

	if (Robot_[0].status == false && Robot_[1].status == true){
		
		if (fo>0 && me==0){
			
			Robot_[1].cargo = 1;
			Robot_[1].type = 1;
			Robot_[1].status = false;
			Robot_[1].room = ro;

			if (fo-1>0){
			DeliveryList(me,fo-1,ro);			
			}		
		}


		if (me>2 && fo==0){
			
			Robot_[1].cargo = 2;
			Robot_[1].type = 2;
			Robot_[1].status = false;
			Robot_[1].room = ro;

			if (me-2 > 0){
			DeliveryList(me-2,fo,ro);			
			}
		}
	
		if (me<3 && fo==0){
			
			Robot_[1].cargo = me;
			Robot_[1].type = 2;
			Robot_[1].status = false;
			Robot_[1].room = ro;

		} 		

		else {
			Robot_[1].cargo = 1;
			Robot_[1].type = 1;
			Robot_[1].status = false;
			Robot_[1].room = ro;

			if (fo-1> 0 || me>0){
			DeliveryList(me,fo-1,ro);			
			}
		}
	
	}

	if (Robot_[0].status == true && Robot_[1].status == false){
	
		if (fo>0 && me==0){
			
			Robot_[0].cargo = 1;
			Robot_[0].type = 1;
			Robot_[0].status = false;
			Robot_[0].room = ro;

			if (fo-1>0){
			DeliveryList(me,fo-1,ro);			
			}		
		}


		if (me>2 && fo==0){
			
			Robot_[0].cargo = 2;
			Robot_[0].type = 2;
			Robot_[0].status = false;
			Robot_[0].room = ro;

			if (me-2 > 0){
			DeliveryList(me-2,fo,ro);			
			}
		}

		if (me<3 && fo==0){
			
			Robot_[0].cargo = me;
			Robot_[0].type = 2;
			Robot_[0].status = false;
			Robot_[0].room = ro;

		}

		else {
			Robot_[0].cargo = 1;
			Robot_[0].type = 1;
			Robot_[0].status = false;
			Robot_[0].room = ro;

			if (fo-1> 0 || me>0){
			DeliveryList(me,fo-1,ro);			
			}
		}


	}

	if (Robot_[0].cargo > 0) {Robot_[0].status = false;}
	else {Robot_[0].status = true;}

	if (Robot_[1].cargo > 0) {Robot_[1].status = false;}
	else {Robot_[1].status = true;}

	
}
	Old=false;
}
}


void hospitalRobot::Reset (int rob){
	Robot_[rob].status = true;
	Robot_[rob].travel = false;
	Robot_[rob].cargo = 0;	
	Robot_[rob].type = 0;
	Robot_[rob].room = -1;	
	Robot_[rob].find=false;
}

bool hospitalRobot::Navigation (int robot, float xGoal, float yGoal ,float zGoal, float wGoal){
	int val=robot+1;
	
	
   //define a client for to send goal requests to the move_base server through a SimpleActionClient
   actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("robot"+to_string(val)+"/move_base", true);
	

   //wait for the action server to come up
   while(!ac.waitForServer(ros::Duration(5.0))){
      ROS_INFO("Waiting for the move_base action server to come up");
   }

   move_base_msgs::MoveBaseGoal goal;

   //set up the frame parameters
   goal.target_pose.header.frame_id = "map";

   /* moving towards the goal*/
	
	if (zGoal == wGoal || zGoal == -wGoal ){	
		if (robot==1){xGoal=xGoal+1.15;}
		if (robot==2){xGoal=xGoal-1.15;}}
	else {if (robot==1){yGoal=yGoal+1.15;}
		if (robot==2){yGoal=yGoal-1.15;}}

   goal.target_pose.pose.position.x =  xGoal;
   goal.target_pose.pose.position.y =  yGoal;
   goal.target_pose.pose.position.z =  0.0;
   goal.target_pose.pose.orientation.x = 0.0;
   goal.target_pose.pose.orientation.y = 0.0;
   goal.target_pose.pose.orientation.z = zGoal;
   goal.target_pose.pose.orientation.w = wGoal;
	
	
   	ROS_INFO("Sending goal location Robot %d ",robot+1);
	ac.sendGoal(goal);
	

	bool done = false;

	ros::Rate r(1);
	Robot_[robot].find=false;
	while ( !done ) {


		if ( ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED  ) {
			done = true;
			ROS_INFO("Robot %d SUCCEEDED",robot+1);
		}
		if (ac.getState() == actionlib::SimpleClientGoalState::PREEMPTED && Robot_[robot].gotochar == false && First_start_1==false && First_start_2==false) {
			done = true;
		}

		r.sleep();
	}
   

}



void hospitalRobot::Traveling_1 (){

	if (First_start_1 == true){
		Navigation (0, Qr_pos[0].pos_x,Qr_pos[0].pos_y, Qr_pos[0].or_z ,Qr_pos[0].or_w);
		First_start_1=false;}
	if (Robot_[0].travel == false && Robot_[0].status == false){
		Robot_[0].travel =true;	
		Robot_[0].deliv = true;	
		
		if (Robot_[0].type == 1){dir_1 = 8;}    //stock food
		if (Robot_[0].type == 2){dir_1 = 7;}    //stock med
		Navigation (0, Qr_pos[dir_1].pos_x,Qr_pos[dir_1].pos_y, Qr_pos[dir_1].or_z ,Qr_pos[dir_1].or_w);
		do{ Navigation (0, Qr_pos[dir_1].pos_x,Qr_pos[dir_1].pos_y, Qr_pos[dir_1].or_z ,Qr_pos[dir_1].or_w);
		}while (Robot_[0].gotochar ==true);
		Verify_pkg (0, dir_1);		
		dir_1 = NRoom;		
		Navigation (0, Qr_pos[dir_1].pos_x,Qr_pos[dir_1].pos_y, Qr_pos[dir_1].or_z ,Qr_pos[dir_1].or_w);
		do{Navigation (0, Qr_pos[dir_1].pos_x,Qr_pos[dir_1].pos_y, Qr_pos[dir_1].or_z ,Qr_pos[dir_1].or_w);
		}while (Robot_[0].gotochar ==true);		
		Verify_room (0,dir_1);
		dir_1=dir_1 + NRoom;
		Navigation (0,Qr_pos[dir_1].pos_x,Qr_pos[dir_1].pos_y, Qr_pos[dir_1].or_z ,Qr_pos[dir_1].or_w);	
		do{Navigation (0, Qr_pos[dir_1].pos_x,Qr_pos[dir_1].pos_y, Qr_pos[dir_1].or_z ,Qr_pos[dir_1].or_w);
		}while (Robot_[0].gotochar ==true);	
		dir_1 = 0;
		Robot_[0].deliv = false;		
		Navigation (0, Qr_pos[dir_1].pos_x,Qr_pos[dir_1].pos_y, Qr_pos[dir_1].or_z ,Qr_pos[dir_1].or_w);
		do{ Navigation (0, Qr_pos[dir_1].pos_x,Qr_pos[dir_1].pos_y, Qr_pos[dir_1].or_z ,Qr_pos[dir_1].or_w);
		}while (Robot_[0].gotochar ==true);
		ros::Duration(2).sleep();
		Reset (0);
	}
}

void hospitalRobot::Traveling_2 (){	
	if (First_start_2 == true){
		Navigation (1, Qr_pos[0].pos_x,Qr_pos[0].pos_y, Qr_pos[0].or_z ,Qr_pos[0].or_w);
		First_start_2=false;}	

	if (Robot_[1].travel == false && Robot_[1].status == false){
		Robot_[1].travel = true;
		Robot_[1].deliv = true;	
		
		if (Robot_[1].type == 1){dir_2 = 8;}    //stock food
		if (Robot_[1].type == 2){dir_2 = 7;}    //stock med
		Navigation (1, Qr_pos[dir_2].pos_x,Qr_pos[dir_2].pos_y, Qr_pos[dir_2].or_z ,Qr_pos[dir_2].or_w);
		do{ Navigation (1, Qr_pos[dir_2].pos_x,Qr_pos[dir_2].pos_y, Qr_pos[dir_2].or_z ,Qr_pos[dir_2].or_w);
		}while (Robot_[1].gotochar ==true);
		Verify_pkg (1, dir_2);
		dir_2 = NRoom;
		Navigation (1, Qr_pos[dir_2].pos_x,Qr_pos[dir_2].pos_y, Qr_pos[dir_2].or_z ,Qr_pos[dir_2].or_w);
		do{ Navigation (1, Qr_pos[dir_2].pos_x,Qr_pos[dir_2].pos_y, Qr_pos[dir_2].or_z ,Qr_pos[dir_2].or_w);
		}while (Robot_[1].gotochar ==true);
		Verify_room (1,dir_2);
		dir_2=dir_2 + NRoom;
		Navigation (1, Qr_pos[dir_2].pos_x,Qr_pos[dir_2].pos_y, Qr_pos[dir_2].or_z ,Qr_pos[dir_2].or_w);
		do{ Navigation (1, Qr_pos[dir_2].pos_x,Qr_pos[dir_2].pos_y, Qr_pos[dir_2].or_z ,Qr_pos[dir_2].or_w);
		}while (Robot_[1].gotochar ==true);
		if (Verify (1, dir_2)==true){Robot_[1].find=true; }
		dir_2 = 0;
		Robot_[1].deliv = false;		
		Navigation (1,Qr_pos[dir_2].pos_x,Qr_pos[dir_2].pos_y, Qr_pos[dir_2].or_z ,Qr_pos[dir_2].or_w);
		do{ Navigation (1, Qr_pos[dir_2].pos_x,Qr_pos[dir_2].pos_y, Qr_pos[dir_2].or_z ,Qr_pos[dir_2].or_w);
		}while (Robot_[1].gotochar ==true);
		ros::Duration(2).sleep();
		Reset (1);
	}
}

 
void hospitalRobot::run(){

boost::thread Battery1_t (&hospitalRobot::Battery1, this);
boost::thread Battery2_t (&hospitalRobot::Battery2, this);
boost::thread Sorting_t (&hospitalRobot::Sorting, this);
boost::thread Print_status_t (&hospitalRobot::Print_status, this);
boost::thread Traveling_1_t (&hospitalRobot::Traveling_1, this);
boost::thread Traveling_2_t (&hospitalRobot::Traveling_2, this);
boost::thread GoToCharge_1_t (&hospitalRobot::GoToCharge_1, this);
boost::thread GoToCharge_2_t (&hospitalRobot::GoToCharge_2, this);

ros::Duration(1).sleep();

}



int main( int argc, char** argv) {
	
   	ros::init(argc, argv, "move_base_client");
	hospitalRobot HR;
	Request_info RI;
	
	do {
	cout << "Inserire la durata della batteria in metri : ";
	getline( cin, HR.input);
	stringstream ss(HR.input);
	ss>>HR.Full;
	}while (HR.Full<1);
	cout<<endl<<"Valore accettato : "<<HR.Full<<endl<<endl;
	
	HR.Reset(0);
	HR.Reset(1);

	//REQ[0].med=3;
	//REQ[0].food=1;
	//REQ[0].room= 1;

	HR.Initialization();
	cout<<"* * * * * * * * * * * INIZIALIZZAZIONE"<<endl;
	ros::Duration(1).sleep();
	
	while (ros::ok){
	
	HR.run();

	ros::spinOnce();
	}
	
return 0;
	 
    	

}

