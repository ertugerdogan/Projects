#include <iostream>
#include "Robot.h"
using namespace std;
class Crew{
	private:
		friend class CommandCenter;
		int maxExplorers;
		int maxMiners;
		int crewManufactureCost;
		float crewMaintenanceCost;
		int explorerCrewSize;
		int minerCrewSize;
		Explorer **ExplorerCrew;
		Miner **MinerCrew;
		
	public:
	Crew(int maxExplorerss,int maxMinerss,int explorerCrewSize,int minerCrewSize){

		//Fill ExplorerCrew and MinerCrew with using manufactureRobot.
		if(1<=maxExplorerss && maxExplorerss<=5 ){
			this->maxExplorers=maxExplorerss;
		}
		
		else{
			this->maxExplorers=2;
		}

		if(1<=maxMinerss && maxMinerss<=5){
			this->maxMiners=maxMinerss;
		}
		
		else{
			this->maxMiners=2;
		}
		
		if(explorerCrewSize<0 || explorerCrewSize>maxExplorers){
			this->explorerCrewSize=maxExplorers;
		}
		else{
			this->explorerCrewSize=explorerCrewSize;
		}

		if(minerCrewSize<0 || minerCrewSize>maxMiners){
			this->minerCrewSize=maxMiners;
		}
		
		else{
			this->minerCrewSize=minerCrewSize;
		}

		for(int i=0;i<explorerCrewSize;i++){
        Robot* temporary = manufactureRobot("explorer");
        //Explorer* explorer=new Explorer(temporary->get_type(), temporary->get_speed(), temporary->get_durability());
		this->ExplorerCrew[i]=new Explorer(temporary->get_type(), temporary->get_speed(), temporary->get_durability());
        //this->ExplorerCrew[i]=explorer;
        //delete temporary, explorer;
		delete temporary;
        }

        for(int i=0;i<minerCrewSize;i++){
           Robot* temporary = manufactureRobot("miner");

           //Miner* miner=new Miner(temporary->get_type(), temporary->get_speed(), temporary->get_durability());
           //this->MinerCrew[i]=miner;
		   this->MinerCrew[i]=new Miner(temporary->get_type(), temporary->get_speed(), temporary->get_durability());
           delete temporary;
        }


	};

	Robot* manufactureRobot(string);
	Robot* manufactureRobot();
	void initMovement();
	void updateDurability();
	void operator+=(Robot*);
	void operator-=(string name);
	void const showInfo();
	Explorer** getExplorers();
	Miner** getMiners();
	int getExplorerCrewSize();
	float getCrewMaintenanceCost();
	int getMinerCrewSize();
	void setCrewMaintenanceCost(float);


};

class CommandCenter{
	private:
		const int neededSelenium;
		const float searchArea;
		const int seleniumWorth;
		int turnCount;
		float totalCrewMaintenanceCost;
		float profit;
	public:
	   CommandCenter();
	   CommandCenter(int,int,int);
	   bool isGameEnded();
	   void calculateProfit(const Crew&);
	   void operator++();
	   void const showInfo(); 
	   
};

