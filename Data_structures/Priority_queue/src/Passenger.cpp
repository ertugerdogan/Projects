#include "Passenger.h"

Passenger::Passenger(int id,int miles, int disabled, int pregnant,int minute, int checkin_time){
    this->ID=id;
    this->miles=miles;
    this->disabled=disabled;
    this->pregnant=pregnant;
    this->minute=minute;
    this->checkin_time=checkin_time;
    this->priority=0;
  
 
       /*if(disabled==1 || pregnant==1){
            this->priority+=1000000000; //other solution
        }
        this->priority+=miles;*/

        if(disabled==1 || pregnant==1){
            this->priority += 101.0;
        }
        this->priority += 100.0-(100.0/(miles+1.0));


};

double Passenger::getpriority(){
    return priority;
};

int Passenger::getminute(){
    return minute;
};

int Passenger::getCheckintime(){
    return checkin_time;
}

int Passenger::getID(){
    return ID;
}


Passenger::Passenger(const Passenger &passenger1){
    ID=passenger1.ID;
    checkin_time=passenger1.checkin_time;
    disabled=passenger1.disabled;
    pregnant=passenger1.pregnant;
    minute=passenger1.minute;
    checkin_time=passenger1.checkin_time;
    priority=passenger1.priority;
}

int PriorityQueue::size() {
        return A.size();
    }

bool PriorityQueue::empty() {
        return size() == 0;
    }


void PriorityQueue::push(Passenger key)
    {
        A.push_back(key);
        int index = size() - 1;
        heap_up(index);
    }

void PriorityQueue::pop(){       
            A[0] = A.back();
            A.pop_back();
            heap_down(0);  
    }


Passenger  PriorityQueue::top()
    {
            return A[0];    
    }


int PriorityQueue::parent(int i) {
        return (i - 1) / 2;
    } 

int PriorityQueue::Left(int i) {
        return (2*i + 1);
    }

int PriorityQueue::Right(int i) {
        return (2*i + 2);
    }

 void PriorityQueue::swap(Passenger &a, Passenger &b){
        Passenger temp=b;
        b=a;
        a=temp;
    }    

void PriorityQueue::heap_down(int i)
    {
        int left = Left(i);
        int right = Right(i);
        int largest = i;

        if (left < size() && A[left].getpriority() > A[i].getpriority()) {
            largest = left;
        }
        if (right < size() && A[right].getpriority() > A[largest].getpriority()) {
            largest = right;
        }

        if (largest != i)
        {
            swap(A[i], A[largest]);
            heap_down(largest);
        }
    }    

 void PriorityQueue::heap_up(int i)
    {
        if (i && A[parent(i)].getpriority() < A[i].getpriority())
        {
            swap(A[i], A[parent(i)]);
            heap_up(parent(i));
        }
    }    

