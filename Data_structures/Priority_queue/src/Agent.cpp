#include "Agent.h"

void Agent::FullIt(){
    full=true;
};

void Agent::EmptyIt(){
    full=false;
};

Agent::Agent(){
    full=false;
};

int Agent::getwaitingtime(){
    return waitingtime;
};

void Agent::setwaitingtime(int Time){
    this->waitingtime=Time;
};

void Agent::ReduceWaitingtime(){
    waitingtime--;
};
