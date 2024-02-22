#include <iostream>
using namespace std;
#include "Robot.h"

int Miner::totalGatheredSelenium;
int Explorer::totalNumberOfSeleniumArea;
float Explorer::totalExploredArea=0;
int Robot::unqID=0;

/*
****************
BEGIN: ROBOT CLASS FUNCTION DECLARATIONS 
****************
*/
Robot::Robot(string RobotType, float speed, int durability, int manufactureCost ,float maintenanceCost){
    this->RobotType=RobotType;
    this->speed=speed;
    this->durability=durability;
    this->manufactureCost=manufactureCost;
    this->maintenanceCost=maintenanceCost;
    
    int i=0;
        if(RobotType=="explorer"){

             this->RobotName[i]='e';//type can be mnr or exp both
             i++;
             this->RobotName[i]='x';//type can be mnr or exp both
             i++;
             this->RobotName[i]='p';//type can be mnr or exp both
             i++;
                                 }
        else if(RobotType=="miner"){
             this->RobotName[i]='m';//type can be mnr or exp both
             i++;
             this->RobotName[i]='i';//type can be mnr or exp both
             i++;
             this->RobotName[i]='n';//type can be mnr or exp both
             i++;
                                   }
    
    this->RobotName[i]='-';
    i++;
    unqID++;
    this->RobotName[i]=unqID;
    this->canMove=true;

}
string const Robot::getName(){
    return this->RobotName;
};

float const Robot::get_speed(){
    return this->speed;
};

string const Robot::get_type(){
    return this->RobotType;
};

void  Robot::operator=(const Robot& Robot){
    this->RobotType=Robot.RobotType;
    this->speed=Robot.speed;
    this->durability=Robot.durability;
    this->manufactureCost=Robot.manufactureCost;
    this->maintenanceCost=Robot.maintenanceCost;
    this->canMove=Robot.canMove;
}

void const Robot::showInfo(){
    cout<<this->RobotType <<endl;
    cout<<this->speed<<endl;
    cout<<this->durability<<endl;
    cout<<this->manufactureCost<<endl;
    cout<<this->maintenanceCost<<endl;
}

bool const Robot::getCanMove(){
    return this->canMove;
}

void Robot::setCanMove(bool move){
    this->canMove=move;
}

float const Robot::getMaintenanceCost(){
    return this->maintenanceCost;
};


/*
****************
END: ROBOT CLASS FUNCTION DECLARATIONS 
****************
*/

/*
****************
BEGIN: EXPLORER CLASS FUNCTION DECLARATIONS 
****************
*/

/*
****************
END: EXPLORER CLASS FUNCTION DECLARATIONS 
****************
*/

void Explorer::explore(){
    int random_value=rand()%99;
    exploredArea=1500;
    totalExploredArea+=1500;
    
    if(random_value>=40){
        detectedSelenium=true;
        totalNumberOfSeleniumArea++; 
    }
    else{
        detectedSelenium=false;
    }
//This exploration should cost you as the robot’s maintenanceCost.
     /*int temp=get_maintenanceCost();
     temp+=450/get_speed();
     set_maintenanceCost(temp);*/
}



void Robot::set_maintenanceCost(float temp){
    maintenanceCost=temp;
};

bool Explorer::move(){
    if(getCanMove()==false){
        return false;
    }
    else{
        return true;
    }
}

int Robot::get_durability(){
    return this->durability;
};

		
void Robot::set_durability(int Durability){
    this->durability=Durability;
};


void Explorer::operator=(Explorer &RobotExplorer ){
 
        this->totalExploredArea=RobotExplorer.totalExploredArea;
		this->totalNumberOfSeleniumArea=RobotExplorer.totalNumberOfSeleniumArea;
		this->exploredArea=RobotExplorer.exploredArea;
		this->detectedSelenium=RobotExplorer.detectedSelenium;
        this->Robot::operator=(RobotExplorer);
}

void const Explorer::showInfo(){

}



float Explorer::getTotalExploredArea(){
    return totalExploredArea;
}
/*
****************
BEGIN: MINER CLASS FUNCTION DECLARATIONS 
****************
*/
void const Miner::showInfo(){

}
void  Miner::mine()
{  
    int Random=(rand()%100)+10;
    int ExtractedNumberOfSelenium=Random*5;	
    this->totalGatheredSelenium += ExtractedNumberOfSelenium;
    int temp=getMaintenanceCost();
    temp+=750/get_speed();
    set_maintenanceCost(temp);	
};



bool Miner::move(){
    if(getCanMove()==false ){//totalNumberOfSeleniumArea>0 Area var mı diye check et
        return false;
    }
    else{
        return true;
    }
}

int Miner::getter_totalGatheredSelenium(){
    return totalGatheredSelenium;
}

void Miner::operator=(Miner &RobotMiner ){
 
        this->gatheredSelenium=RobotMiner.gatheredSelenium;
		this->totalGatheredSelenium=RobotMiner.totalGatheredSelenium;
        this->Robot::operator=(RobotMiner);
}






/*
****************
END: MINER CLASS FUNCTION DECLARATIONS 
****************
*/

