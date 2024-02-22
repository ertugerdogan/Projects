#include <iostream>
#ifndef _H
#define _H
using namespace std;


class Robot {
	private:
		static int unqID;
		string RobotName;
		string RobotType;
		float speed; 
		int durability; 
		int manufactureCost; 
		float maintenanceCost;
		bool canMove;
	
	public:
	    Robot( string ,float , int , int  ,float  );		
		void operator=(const Robot&);  
		void const showInfo();    
		bool const getCanMove();
		void setCanMove(bool);
		int get_durability();
		void set_durability(int);
		string const getName();
		float const get_speed();
		string const get_type();
		float const getMaintenanceCost();
		void set_maintenanceCost(float temp);
   
}; 

/*totalExploredArea is total area of the field explored by all explorer robots within your crew.
 exploredArea is total area of the field explored by an explorer robot within your crew. 
 totalNumberOfSeleniumArea represents the total number of areas where selenium is found by 
 explorer robots and has not been extracted yet by miner robots detectedSelenium represents 
 whether selenium is detected or not.*/




class Explorer: public Robot{
	private:
		static float totalExploredArea; //maybe inline
		static int totalNumberOfSeleniumArea; //maybe inline 
		float exploredArea;
		bool detectedSelenium;
		friend class CommandCenter;
		friend class Miner;
		
		
	public:
	Explorer(string type,float speed,int durability): Robot( type ,speed , durability , 3000  ,450/speed  ){};
	bool move();
	void explore();
	void operator=(Explorer&);
	void const showInfo();
    static float getTotalExploredArea();



		
};


class Miner: public Robot{
	private:
		static int totalGatheredSelenium;
		int gatheredSelenium;
		friend class CommandCenter;

		
	public:
		Miner(string type,float speed,int durability): Robot( type ,speed , durability , 5000  ,750/speed  ){};
		void  mine();
		bool move();
		void const showInfo();
		void operator=(Miner&);
		static int getter_totalGatheredSelenium();
};


#endif