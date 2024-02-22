#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "math.h"

using namespace std;

bool any_bool = false;
string STARTING_DATE;
string STARTING_TIME;
string ENDING_DATE;
string ENDING_TIME;

struct Data{
        float priority;

        Data(float);
        float getpriority();

        Data(const Data &passenger1);
};


class PriorityQueue
{
public:

    vector<Data> A;
    vector<Data> A_max;
    
    int parent(int);
    int Left(int) ;
    int Right(int i);
    void swap(Data&, Data&);
    void minheap_down(int);
    void heap_down(int);
    void minheap_up(int);
    void heap_up(int);
    int size() ;
    bool empty() ;
    void push(Data );
    void minpush(Data );
    void pop();
    void minpop();
    Data top();
    float top_pri();
    double mean();
    double stdev();
    void heapSort();
    float getMedian();
    float getFirstq();
    float getThirdq();
    int partition(int,int);
    void insertionSort();

};



void PriorityQueue::insertionSort()
{
   int i,  j;
   double key;
   for (i = 1; i < A.size(); i++)
   {
key = A[i].priority;
j = i - 1;

        while (j >= 0 && A[j].priority > key)
        {
            A[j + 1].priority = A[j].priority;
            j = j - 1;
        }
        A[j + 1].priority = key;
}
}


void PriorityQueue::heapSort()
{
    int n = A.size();
    n = n;
    for (int i = n / 2 - 1; i >= 0; i--)
    {heap_down(i);}
 
    for (int i = n - 1; i >= 0; i--) {
    swap(A[0], A[i]);
    heap_down(0);
    }
    int a = 0;
}

float PriorityQueue::getMedian()
{   
    int size=A.size();
    if(A.size()%2==0){
        int n=(A.size())/2;
        return (A[n-1].priority+A[n].priority)/2;
    }
    else{
        int n=(A.size()-1)/2;
        return (A[n].priority);
    }
}


float PriorityQueue::getFirstq()
{   
    int size=A.size();
    int n=size;
    int x;
    if(n%4==0){
        x=(n)/4;
        return (A[x-1].priority)*0.25+(A[x+1-1].priority)*0.75;
    }
    else if((n-1)%4==0){
        x=(n-1)/4;
        return (A[(n+3)/4-1].priority);
    }
    else if((n-2)%4==0){
        x=(n+2)/4;
        return (A[x].priority*0.25 + A[x-1].priority*0.75);
    }
    else if((n-3)%4==0){
        x=(n-3)/4;
        double some = (A[x+1-1].priority)*0.50+(A[x+2-1].priority)*0.50;
        return (A[x+1-1].priority)*0.50+(A[x+2-1].priority)*0.50;
    }
}


float PriorityQueue::getThirdq()
{
    int size=A.size();
    int n=size;
    int x;
    if(n%4==0){
        x=(n)/4;
        return (A[3*x-1].priority)*0.75+(A[3*x+1-1].priority)*0.25;
    }
    else if((n-1)%4==0){
        x=(n-1)/4;
        return A[(3*n + 1)/4-1].priority;
    }
    else if((n-2)%4==0){
        x=(3*n+2)/4;
        return (A[x-1].priority*0.75 + A[x-2].priority*0.25);
    }
    else if((n-3)%4==0){
        x=(n-3)/4;
        return (A[3*x+2-1].priority)*0.50+(A[3*x+3-1].priority)*0.50;
    }

}
Data::Data(float priority){
    this->priority=priority;
}

float Data::getpriority(){
    return priority;
};

Data::Data(const Data &data1){
    priority=data1.priority;
}

int PriorityQueue::size() {
        return A.size();
    }

bool PriorityQueue::empty() {
        return size() == 0;
    }


void PriorityQueue::push(Data key)
    {
        A.push_back(key);
        int index = size() - 1;
        heap_up(index);
    }
void PriorityQueue::minpush(Data key)
    {
        A.push_back(key);
        int index = size() - 1;
        minheap_up(index);
    }

void PriorityQueue::pop(){       
            A[0] = A.back();
            A.pop_back();
            heap_down(0);  
    }
void PriorityQueue::minpop(){       
            A[0] = A.back();
            A.pop_back();
            minheap_down(0);  
    }

Data  PriorityQueue::top()
    {
            return A[0];    
    }

float  PriorityQueue::top_pri()
{
        return A[0].priority;    
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

 void PriorityQueue::swap(Data &a, Data &b){
        Data temp=b;
        b=a;
        a=temp;
    }
double PriorityQueue::mean(){
        int size=A.size();
        double sum=0;
        double mean = 0;
        for(int i=0;i<size;i++){
            sum+=A[i].priority;
        }
        mean=sum/size;
        return mean;
    }

double PriorityQueue::stdev(){

        int size=A.size();
        double mean = PriorityQueue::mean();
        double stdev = 0;

        for(int i=0;i<size;i++){
            stdev+=(A[i].priority-mean)*(A[i].priority-mean)/(size-1);
        }
        return sqrt(stdev);
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



void PriorityQueue::minheap_down(int i)
    {
        int left = Left(i);
        int right = Right(i);
        int smallest = i;

        if (left < size() && A[left].getpriority() < A[i].getpriority()) {
            smallest = left;
        }
        if (right < size() && A[right].getpriority() < A[smallest].getpriority()) {
            smallest = right;
        }

        if (smallest != i)
        {
            swap(A[i], A[smallest]);
            minheap_down(smallest);
        }
    }   


  void PriorityQueue::minheap_up(int i)
    {
        if (i && A[parent(i)].getpriority() > A[i].getpriority())
        {
            swap(A[i], A[parent(i)]);
            minheap_up(parent(i));
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


vector<int> read_statistics(){
    
    int statistics_num;
    cin >> statistics_num;
    

    vector <int> statistic_avaliable;
    for(int i = 0; i < 7; i++){
        statistic_avaliable.push_back(0);
    }

    for(int i = 0; i < statistics_num; i++){
        string statistic;
        cin >> statistic;

        if(statistic == "mean"){
            statistic_avaliable[0] = 1;
        }else if(statistic == "std"){
            statistic_avaliable[1] = 1;
        }
        else if(statistic == "min"){
            statistic_avaliable[2] = 1;
        }
        else if(statistic == "firstq"){
            statistic_avaliable[3] = 1;
        }
        else if(statistic == "median"){
            statistic_avaliable[4] = 1;
        }
        else if(statistic == "thirdq"){
            statistic_avaliable[5] = 1;
        }
        else if(statistic == "max"){
            statistic_avaliable[6] = 1;
        }
    }
    return statistic_avaliable;
}

void print_func(PriorityQueue Pq, PriorityQueue &Pq_max, vector <int> statistic_avaliable){

    cout << STARTING_DATE << " ," << STARTING_TIME << " ," << ENDING_DATE << " ," << ENDING_TIME;

    if(statistic_avaliable[0] == 1){
        double mean = Pq.mean();
        cout << " ," << mean;        
    }
    if(statistic_avaliable[1] == 1){
        double stdev = Pq.stdev();
        cout << " ," << stdev;    
    }
    if(statistic_avaliable[2] == 1){
        Pq.minheap_down(0);
        double min = Pq.top_pri();
        cout << " ," << min;   
    }
    if(statistic_avaliable[3] == 1){
        int size = Pq.A.size();

        //Pq.quickSort(0, size - 1);
        Pq.insertionSort();

        double firq = Pq.getFirstq();
        cout << " ," << firq; 
    }
    if(statistic_avaliable[4] == 1){
        int size = Pq.A.size();
        //Pq.quickSort(0, size - 1);
        Pq.insertionSort();


        double median = Pq.getMedian();
        cout << " ," << median; 
    }
    if(statistic_avaliable[5] == 1){
        int size = Pq.A.size();
        //Pq.quickSort(0, size - 1);
        Pq.insertionSort();


        double thirq = Pq.getThirdq();
        cout << " ," << thirq; 
    }
    if(statistic_avaliable[6] == 1){
        
        Pq.heap_down(0);
        double max = Pq_max.top_pri();
        cout << " ," << max;   
    }
    
    return;
}

void add_value(string value, PriorityQueue &Pq, PriorityQueue &Pq_max, vector <int> statistic_avaliable, string line){
    

    int value_start_index = 0;
    int value_end_index = line.find(',');
    string date = line.substr(value_start_index, value_end_index);
    value_start_index = value_end_index + 1;
    value_end_index = line.find(',', value_end_index + 1);

    string time = line.substr(value_start_index, value_end_index - value_start_index);
    value_start_index = value_end_index + 1;
    value_end_index = line.find(',', value_end_index + 1);

    float gap = stof(line.substr(value_start_index, value_end_index - value_start_index));
    value_start_index = value_end_index + 1;
    value_end_index = line.find(',', value_end_index + 1);

    float grp = stof(line.substr(value_start_index, value_end_index - value_start_index));
    value_start_index = value_end_index + 1;
    value_end_index = line.find(',', value_end_index + 1);

    float v = stof(line.substr(value_start_index, value_end_index - value_start_index));
    value_start_index = value_end_index + 1;
    value_end_index = line.find(',', value_end_index + 1);

    float gi = stof(line.substr(value_start_index, value_end_index - value_start_index));
    
    
    if(value == "gap"){
    Data temp = Data(gap);
    Pq.minpush(temp);
    }else if(value == "grp"){
    Data temp = Data(grp);
    Pq.minpush(temp);
    }else if(value == "v"){
    Data temp = Data(v);
    Pq.minpush(temp);
    }else if(value == "gi"){
    Data temp = Data(gi);
    Pq.minpush(temp);
    }
    if(statistic_avaliable[6] == 1){
        if(value == "gap"){
        Data temp = Data(gap);
        Pq_max.push(temp);
        }else if(value == "grp"){
        Data temp = Data(grp);
        Pq_max.push(temp);
        }else if(value == "v"){
        Data temp = Data(v);
        Pq_max.push(temp);
        }else if(value == "gi"){
        Data temp = Data(gi);
        Pq_max.push(temp);
        }
    }

    if(!any_bool){
        STARTING_DATE = date;
        STARTING_TIME = time;
        any_bool = true;
    }
    ENDING_DATE = date;
    ENDING_TIME = time;
    
    
}

void read_values(vector <int> statistic_avaliable, PriorityQueue &Pq, PriorityQueue &Pq_max){
    string line;
    cin >> line;

    int index = line.find(',');
    string value = line.substr(0,index);
    int number_of_lines = stoi(value);

    string important_quantity = line.substr(line.find(',') + 1, line.size() - 1);
    
    for(int i = 0; i < number_of_lines; i++){
        cin >> line;
        if(line == "print"){
            print_func(Pq, Pq_max, statistic_avaliable);
        }else if(line == "add"){
        }
    }
}

void print_to_txt(string output_file_path, PriorityQueue Pq, PriorityQueue &Pq_max, vector <int> statistic_avaliable){

    ofstream output_txt;
    output_txt.open(output_file_path, ios::app);

    for(int i = 0; i < 7; i++){
    }
    
    output_txt << STARTING_DATE << "," << STARTING_TIME << "," << ENDING_DATE << "," << ENDING_TIME;
    if(statistic_avaliable[0] == 1){
        double mean = Pq.mean();
        output_txt << "," << mean;
    }
    if(statistic_avaliable[1] == 1){
        double stdev = Pq.stdev();
        output_txt << "," << stdev;    
    }
    if(statistic_avaliable[2] == 1){
        Pq.minheap_down(0);
        double min = Pq.top_pri();
       
        output_txt << "," << min;   
    }
    if(statistic_avaliable[3] == 1){
        int size = Pq.A.size();
        //Pq.quickSort(0, size - 1);
        Pq.insertionSort();


        double firq = Pq.getFirstq();
    
        output_txt << "," << firq; 
    }
    if(statistic_avaliable[4] == 1){
        int size = Pq.A.size();
        //Pq.quickSort(0, size - 1);
        Pq.insertionSort();


        double median = Pq.getMedian();
       
        output_txt << "," << median; 
    }
    if(statistic_avaliable[5] == 1){
        int size = Pq.A.size();
        //Pq.quickSort(0, size - 1);
        Pq.insertionSort();


        double thirq = Pq.getThirdq();
       
        output_txt << "," << thirq; 
    }
    if(statistic_avaliable[6] == 1){
        
        Pq.heap_down(0);
        double max = Pq_max.top_pri();
      
        output_txt << "," << max;   
    }
    output_txt << endl;   
    output_txt.close();
}

void read_txt_file(string file_name, PriorityQueue &Pq, PriorityQueue &Pq_max, string output_file_path){

    ifstream txt_file(file_name);
    string line;
    getline(txt_file, line);
    int statistics_num = stoi(line);


    vector <int> statistic_avaliable;
    for(int i = 0; i < 7; i++){
        statistic_avaliable.push_back(0);
    }
    for(int i = 0; i < statistics_num; i++){
        string statistic;
        getline(txt_file, line);
        statistic = line;
     

        if(statistic == "mean"){
            statistic_avaliable[0] = 1;
        }else if(statistic == "std"){
            statistic_avaliable[1] = 1;
        }
        else if(statistic == "min"){
            statistic_avaliable[2] = 1;
        }
        else if(statistic == "firstq"){
            statistic_avaliable[3] = 1;
        }
        else if(statistic == "median"){
            statistic_avaliable[4] = 1;
        }
        else if(statistic == "thirdq"){
            statistic_avaliable[5] = 1;
        }
        else if(statistic == "max"){
            statistic_avaliable[6] = 1;
        }
    }

    getline(txt_file, line);
    getline(txt_file, line);

    int index = line.find(',');
    string value = line.substr(0,index);
    int number_of_lines = stoi(value);

    string important_quantity = line.substr(line.find(',') + 1, line.size() - 1);
    
    for(int i = 0; i < number_of_lines; i++){
        getline(txt_file, line);
        if(line == "print"){
            print_to_txt(output_file_path, Pq, Pq_max, statistic_avaliable);
        }else if(line == "add"){
            i++;
            getline(txt_file, line);
            add_value(important_quantity, Pq, Pq_max, statistic_avaliable, line);
        }
    }
}



int main(int argc, char **argv){
 
    PriorityQueue Pq;
    PriorityQueue Pq_max;
    
    string file_path = argv[1];

    string output_file_path = "output.txt";
    ofstream output_txt(output_file_path);
    output_txt.close();
    read_txt_file(file_path, Pq, Pq_max, output_file_path);
    
    return 0;
}