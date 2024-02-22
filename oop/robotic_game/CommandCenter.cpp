#include "CommandCenter.h"
#include "Robot.h"
#include <iostream>
using namespace std;


void Crew::operator+=(Robot* ROBOT){
    if(ROBOT->get_type()=="explorer"){
        Explorer* explorer=new Explorer(ROBOT->get_type(), ROBOT->get_speed(),ROBOT->get_durability());
        if(explorerCrewSize<maxExplorers){
           this->ExplorerCrew[explorerCrewSize]=explorer;
           this->explorerCrewSize++; 
        }

        delete explorer;
    }
    else if(ROBOT->get_type()=="miner"){
        Miner* miner=new Miner(ROBOT->get_type(), ROBOT->get_speed(),ROBOT->get_durability());
        if(minerCrewSize<maxMiners){
        this->MinerCrew[minerCrewSize]=miner;
        this->minerCrewSize++;
        }
        delete miner;
    }
};



Robot* Crew::manufactureRobot(string Name){

    if(Name=="explorer"){
        explorerCrewSize=0;
        int durability=rand()%5+1;
        float speed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        speed+=1.5;
        Explorer* explorer=new Explorer(Name, speed,durability);
        explorer=new Explorer(Name, speed,durability);
        //durability=rand()%6;
        /*ExplorerCrew[explorerCrewSize]=explorer;
        explorerCrewSize++;*/
        return explorer;
    }
    
    else if(Name=="miner"){
        minerCrewSize=0;
        int durability=rand()%3+2;
        float speed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        speed+=0.5;
        Miner* miner=new Miner(Name, speed,durability);
        miner=new Miner(Name, speed,durability);
        
        /*MinerCrew[minerCrewSize]=miner;
        minerCrewSize++;*/
        return miner;        
    }
    else{
        return NULL;
    }
                              }



void Crew::initMovement(){
    int i=0;
    int j=0;
    while(i<this->explorerCrewSize){
    this->ExplorerCrew[i]->setCanMove(true);
    i++;
                                   }

    while(j<this->minerCrewSize){
    this->MinerCrew[i]->setCanMove(true);
    j++;
                                   }
}


int Crew::getMinerCrewSize(){
    return this->minerCrewSize;
}

void Crew::updateDurability(){
    for(int i=0;i<minerCrewSize;i++){
        int new_durability;
       if(MinerCrew[i]->get_durability()!=0){
           new_durability=MinerCrew[i]->get_durability();
           new_durability--;
           MinerCrew[i]->set_durability(new_durability);
       } 
       else if(MinerCrew[i]->get_durability()==0){
           if(minerCrewSize>1){
               minerCrewSize-=1;
                   for(int j=i;j<minerCrewSize;j++){//i =2
                       MinerCrew[j]=MinerCrew[j+1];
                   }
               }
           }
           else{

           }
       }

    for(int i=0;i<explorerCrewSize;i++){
       int new_durability;
       if(ExplorerCrew[i]->get_durability()!=0){
           new_durability=ExplorerCrew[i]->get_durability();
           new_durability--;
           ExplorerCrew[i]->set_durability(new_durability);
       }  
    }

}

Robot* Crew::manufactureRobot(){////OVERLOADING
    string type;
    cout<<"Type:";
    cin>>type;
    int durabilityoF = rand() % 5 + 1;
    float speedoF =  static_cast <float> (rand()) /( static_cast <float> (RAND_MAX));
    speedoF+=1.5;
    if(type == "explorer"){
        Explorer* explorer= new Explorer(type,speedoF,durabilityoF);
        return explorer;
    }
    else if(type == "miner"){
        Miner* miner= new Miner(type,speedoF,durabilityoF);
        return miner;
    }
    else{
        cout<<"Wrong Choice!";
        return NULL;
    }
}

void Crew::operator-=(string name){
    bool miner=false;

    if(name[0]=='m' && name[1]=='n' && name[2]=='r'){
        miner=true;
    }

    if(name[0]=='e' && name[1]=='x' && name[2]=='p'){
        miner=false;
    }
bool isFind=false;
   
    if(miner==true){
        for(int i=0;i<minerCrewSize;i++){
            if(MinerCrew[i]->getName()==name){
                isFind=true;
            }
            if(isFind==true){
                MinerCrew[i]=MinerCrew[i+1];
            }
            else if(minerCrewSize==1){
                return;
            }
        }
        minerCrewSize--;
    }

    if(miner==false){
        for(int i=0;i<explorerCrewSize;i++){
            if(ExplorerCrew[i]->getName()==name){
                isFind=true;
            }
            if(explorerCrewSize==1){
                return;
            }
            else if(isFind==true ){
ExplorerCrew[i]=ExplorerCrew[i+1];
            }
            
        }
        explorerCrewSize--;
    }

};

void const CommandCenter::showInfo(){
    cout<<" ";
       }; 

void const Crew::showInfo(){
   
    for(int i=0;i<explorerCrewSize;i++){
        ExplorerCrew[i]->showInfo()   ;
    }
    for(int i=0;i<minerCrewSize;i++){
        MinerCrew[i]->showInfo()   ;
    }
     
    cout<<crewManufactureCost;
};

Explorer** Crew::getExplorers(){
    return ExplorerCrew;
}

Miner** Crew::getMiners(){
    return MinerCrew;
}


int Crew::getExplorerCrewSize(){
    return this->explorerCrewSize;
};

float Crew::getCrewMaintenanceCost(){
    return this->crewMaintenanceCost;
};


void Crew::setCrewMaintenanceCost(float CrewMaintenanceCost){
    this->crewMaintenanceCost=CrewMaintenanceCost;
}


/*
****************
END: CREW CLASS FUNCTION DECLARATIONS 
****************
*/

/*
****************
BEGIN: COMMANDCENTER CLASS FUNCTION DECLARATIONS 
****************
*/

void CommandCenter::operator++(){
	turnCount++;
	};

bool CommandCenter::isGameEnded(){
    if(Explorer::getTotalExploredArea() >= searchArea){// game ends{
        if(Miner::getter_totalGatheredSelenium() >= neededSelenium && profit>0){
            cout<<"Congrats!";
            }
            return true;
    }
    else{
            cout<<"Mission Failed!";
            return false;
        }
};


CommandCenter::CommandCenter( int seleniumAim, int exploreArea, int seleniumWorth):
neededSelenium(seleniumAim),searchArea(exploreArea),seleniumWorth(seleniumWorth){
};


//Source of the expenses are crewMaintenanceCost and crewManufactureCost.Source
//of the revenue is selenium. Calculate profit according to this.

void CommandCenter::calculateProfit(const Crew& crew){
   
   float x=0.0;
   x+=Miner::totalGatheredSelenium*seleniumWorth;
   x-=crew.crewMaintenanceCost;
   x-=crew.crewManufactureCost;
   cout<<"Profit:"<<x<<endl;
};
/*
****************
END: COMMANDCENTER CLASS FUNCTION DECLARATIONS 
****************
*/
