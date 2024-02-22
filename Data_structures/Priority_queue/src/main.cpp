#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

#include "Passenger.h"
#include "Agent.h"


//case 1

//8 3 0

// 8 passenger, 3 agent,0=demestic

//1 70000 0 0 1 10 --> Gold Tier
//3 500 1 0 3 8    --> Disabled
//2 80001 0 0 3 15 --> Platinum Tier
//4 30000 0 0 3 20 --> Silver Tier
//5 200000 0 0 5 7 --> Platinum Tier
//6 20000 0 0 6 8  --> Classic Tier
//7 0 0 1 11 12    --> Pregnant
//8 50000 0 0 20 7 --> Gold Tier

//Check - in is complete on time in 38 minutes .

//case 2

//2 1 1

//2 passenger, 1 agent , 1=international

//1 10000 0 1 10 20
//2 5000 0 0 178 3

// ID, miles,  disabled, pregnant, minute, check-in time


//We expect you to implement the priority queue with heaps.

int main(int argc, char** argv){

    int time;
    int passenger_count,agent_count;
    
    int ID, miles,  disabled, pregnant, minute, checkin_time;
    int current_time=0;
    int pop_count=0;

    vector<Passenger> my_list;
    vector<Agent> agent_list;
    
    PriorityQueue passengerhouse;

    ifstream myfile(argv[1]);
        myfile >> passenger_count >> agent_count >> time;
        for(int i=0;i<passenger_count;i++){
            myfile>>ID>>miles>>disabled>>pregnant>>minute>>checkin_time;
            Passenger *temp= new Passenger( ID,miles, disabled, pregnant, minute,checkin_time);
            my_list.push_back(*temp);
            delete temp;
        }

    myfile.close();
        for(int i=0;i<agent_count;i++){
            Agent *temp= new Agent();
            agent_list.push_back(*temp);
            delete temp;
        }
    if(time==0){
        time=120;//domestic;
    }else if(time==1){
        time=180;//international
    }
    
    int passenger_tracker=0;

    bool NotFinish=true;
    int EmptyAgentCount=0;
    while(NotFinish){
        while(my_list[passenger_tracker].getminute()==current_time && passenger_tracker<passenger_count){
            Passenger temp=my_list[passenger_tracker];
            passengerhouse.push(temp);
            passenger_tracker++;
        }
        for(int i=0;i<agent_count;i++){
            if(agent_list[i].getwaitingtime()!=0){
                if(agent_list[i].full){
                agent_list[i].ReduceWaitingtime();}
            }else{
                agent_list[i].EmptyIt();// time is done
            }        
        }  
        for(int i=0;i<agent_count;i++){
            if(!agent_list[i].full && !passengerhouse.empty()){//If agenta is empty
                agent_list[i].FullIt();
                cout<<"Agent "<<i+1<< " takes passenger "<<passengerhouse.top().getID()<<" at minute "<< current_time<<endl;
                agent_list[i].setwaitingtime(passengerhouse.top().getCheckintime()-1);
                passengerhouse.pop();
                pop_count++;
            }
        }           
       if(pop_count==passenger_count){
           for(int i=0;i<agent_count;i++){
              if(!agent_list[i].full){
                  EmptyAgentCount++;
            }
            }
            if(EmptyAgentCount==agent_count){
                    NotFinish=false;
                }
            EmptyAgentCount=0;    
        }
        if(NotFinish){
            current_time++;
        }
            
    }

    if(current_time>time){
        cout<<"Check in failed to be completed on time it took "<<current_time<<" minutes ";
    }else{
        cout<<"Check in is complete on time in "<<current_time<<" minutes ";}  
       
    return EXIT_SUCCESS;
}
