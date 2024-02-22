//pregnant or disabled    5 point
//++80,000      platinium 4 point 
//40.000-80.000 gold      3 point
//25.000-40.000 silver    2 point
//all-25.0000   classic   1 point
//


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Passenger{
    private:
        int ID;
        int miles;
        int disabled;
        int pregnant;
        int minute;
        int checkin_time;
        double priority;
 
    public:
        Passenger(int,int,int,int,int,int);
        double getpriority();
        int getminute();
        int getCheckintime();
        Passenger(const Passenger &passenger1);
        int getfinishtime();
        int getID();        
};


class PriorityQueue
{
private:

    vector<Passenger> A;
    
public:
    int parent(int);
    int Left(int) ;
    int Right(int i);
    void swap(Passenger&, Passenger&);
    void heap_down(int);
    void heap_up(int);
    int size() ;
    bool empty() ;
    void push(Passenger );
    void pop();
    Passenger top();

    
};


