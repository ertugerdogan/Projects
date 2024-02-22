#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

struct Calendar {
    string Places;
    double starting_Day;
    double finishing_Day;
    string first_month;
    string second_month;
    int profit;
};

struct daily_program{
    string Place; 
    string Salon_Num;
    string Starting_hour;
    string Ending_hour;
    int capacity;

};


struct Asset {
    string name;
    int price;
    double value;
};

bool compareByEndTime(const daily_program& a, const daily_program& b) {
    return a.Ending_hour < b.Ending_hour;
}

int latestNonConflict(daily_program arr[], int i) {
    for (int j = i - 1; j >= 0; j--) {
        if (arr[j].Ending_hour <= arr[i - 1].Starting_hour)
            return j;
    }
    return -1;
}

pair < int,vector <daily_program> > findMaxProfitRec(daily_program arr[], int n,vector<daily_program> selectedPrograms) {

      if (n == 1) {
        selectedPrograms.push_back(arr[0]);
        return make_pair(arr[0].capacity,selectedPrograms);
    }
    pair<int,vector <daily_program> > temp;
    pair<int,vector <daily_program> > tempExclude;
    int inclProf = arr[n - 1].capacity;
    int i = latestNonConflict(arr, n);
    if (i != -1) {
        vector<daily_program> inclSelectedPrograms = selectedPrograms;
        inclSelectedPrograms.push_back(arr[n - 1]);
        
        temp=findMaxProfitRec(arr, i + 1,inclSelectedPrograms);
        inclProf += temp.first;
        temp.first=inclProf;

        tempExclude=findMaxProfitRec(arr, n - 1,selectedPrograms);
        int exclProf =tempExclude.first;

        if (inclProf > exclProf) {
            selectedPrograms = inclSelectedPrograms;
 
            return temp;
        } else {
            return tempExclude;
        }
    } else {
        vector<daily_program> inclSelectedPrograms = selectedPrograms;
        inclSelectedPrograms.push_back(arr[n - 1]);
        
        temp=make_pair(inclProf,inclSelectedPrograms);
        temp.first=inclProf;

        tempExclude=findMaxProfitRec(arr, n - 1,selectedPrograms);
        int exclProf =tempExclude.first;

        if (inclProf > exclProf) {
            selectedPrograms = inclSelectedPrograms;
 
            return temp;
        } else {
            return tempExclude;
        }
    }
}

pair<int,vector<daily_program> >  findMaxProfit(daily_program arr[], int n) {
    sort(arr, arr + n, compareByEndTime);
    return findMaxProfitRec(arr, n,vector<daily_program>() );
}


//CALENDAR PART



bool compareByEndTimeCalendar(const Calendar& a, const Calendar& b) {

    double finishing_a=a.finishing_Day;
    double starting_b=b.finishing_Day;
    double dif=finishing_a-floor(finishing_a)-(starting_b-floor(starting_b));
        
        if(abs(dif)<0.000001){
           // cout<<"compare "<<finishing_a<<" "<< starting_b <<" "<<dif<<endl;

            return(finishing_a < starting_b);
        }else{
            return dif<0;
        }
        
    return a.finishing_Day < b.finishing_Day;
}

int latestNonConflictCalendar(Calendar arr[], int i) {
    for (int j = i - 1; j >= 0; j--) {
    
        double finishing_j=arr[j].finishing_Day;
        double starting_i=arr[i-1].starting_Day;
        
        double dif=finishing_j-floor(finishing_j)-(starting_i-floor(starting_i));

        if(abs(dif)<0.000001){
            if (arr[j].finishing_Day <= arr[i - 1].starting_Day){
                return j;
            }           
        }else{

            if((dif)<0 ){
                //cout<<finishing_j<<" "<<starting_i<<endl;

                return j;
            }
        }
        
    }
    return -1;
}


int getNumberOfDays(double startingDay, double finishingDay) {
   
    double dif=finishingDay-floor(finishingDay)-(startingDay-floor(startingDay));

    if(abs(dif)<0.0001){
        //cout<<"Başlangıç günü"<<startingDay<<endl;
        //cout<<"Bitiş günü"<<finishingDay<<endl;
        //cout<<"Aradaki gün sayısı"<<static_cast<int>(finishingDay-startingDay)+1<<endl;

        return static_cast<int>(finishingDay-startingDay)+1;
    }
    

    return 32-floor(startingDay)+floor(finishingDay);

}
    





pair<int, vector<Calendar> > findMaxProfitRecCalendar(Calendar arr[], int n, vector<Calendar> selectedCalendars) {
    if (n == 1) {
        selectedCalendars.push_back(arr[0]);
        int totalProfit = arr[0].profit * getNumberOfDays(arr[0].starting_Day, arr[0].finishing_Day);
     
        return make_pair(totalProfit, selectedCalendars);
    }
    pair<int, vector<Calendar> > temp;
    pair<int, vector<Calendar> > tempExclude;
    int inclProf = arr[n - 1].profit * getNumberOfDays(arr[n - 1].starting_Day, arr[n - 1].finishing_Day);


    int i = latestNonConflictCalendar(arr, n);

    if (i != -1) {
        vector<Calendar> inclSelectedCalendars = selectedCalendars;
        inclSelectedCalendars.push_back(arr[n - 1]);
        temp = findMaxProfitRecCalendar(arr, i + 1, inclSelectedCalendars);
        inclProf += temp.first;
        temp.first = inclProf;

        tempExclude = findMaxProfitRecCalendar(arr, n - 1, selectedCalendars);
        int exclProf = tempExclude.first;

        if (inclProf > exclProf) {
            selectedCalendars = inclSelectedCalendars;
            return temp;
        } else {
            return tempExclude;
        }
    } else {
        
        vector<Calendar> inclSelectedPrograms = selectedCalendars;
        inclSelectedPrograms.push_back(arr[n - 1]);
        
        temp=make_pair(inclProf,inclSelectedPrograms);
        temp.first=inclProf;

        tempExclude=findMaxProfitRecCalendar(arr, n - 1,selectedCalendars);
        int exclProf =tempExclude.first;

        if (inclProf > exclProf) {
            selectedCalendars = inclSelectedPrograms;
 
            return temp;
        } else {
            return tempExclude;
        }
    
    }
}


pair<int, vector <Calendar> >  findMaxProfitCalendar(Calendar arr[], int n) {
    sort(arr, arr + n, compareByEndTimeCalendar);
    
    /*for(int i=0;i<n;i++){
        cout<<(arr+i)->starting_Day<<" "<<(arr+i)->finishing_Day<<" "<<(arr+i)->Places<<endl;
    }*/
    return findMaxProfitRecCalendar(arr, n, vector<Calendar>());
}



pair<double, vector<Asset> >selectAssets(const vector<Asset>& assets, int budget) {
int n = assets.size();
double number=0;
vector<vector<double> > dp(n + 1, vector<double>(budget + 1));

for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= budget; j++) {
        if (assets[i - 1].price <= j) {
            dp[i][j] = max(dp[i - 1][j], assets[i - 1].value + dp[i - 1][j - assets[i - 1].price]);
        } else {
            dp[i][j] = dp[i - 1][j];
        }
    }    }

   vector<Asset> selectedAssets;
int i = n, j = budget;
while (i > 0 && j > 0) {
    if (dp[i][j] != dp[i - 1][j]) {
        selectedAssets.push_back(assets[i - 1]);
        number+=assets[i-1].value;
        j -= assets[i - 1].price;
    }
    i--;
}

        return make_pair(number,selectedAssets);;
}



int main(int argc, char* argv[]){

string caseNo=argv[1];
string path="inputs/case_"+caseNo;
string output_path="outputs/case"+caseNo;



ifstream file(path+"/availability_intervals.txt");
string temp;
vector<Calendar> calendars;

vector<int> tempNumbers;

getline(file,temp);
while (getline(file, temp)) {
stringstream ss(temp);
string new_place;
double start, end;


ss >> new_place >> start >> end;

    Calendar calendar;
    calendar.Places = new_place;
    calendar.starting_Day = start;
    calendar.finishing_Day = end;
    calendars.push_back(calendar);
}

//Daily_Schedule.txt
ifstream Schedule(path+"/daily_schedule.txt");
vector<daily_program> Program;
string tempPlace;
int counter=0;
getline(Schedule,temp);
while (getline(Schedule, temp)) {    
stringstream ss(temp);
string Place, Salon_Num, StartAt,EndsAt;
ss >> Place >> Salon_Num >> StartAt>>EndsAt;

    daily_program program;
    program.Place = Place;
    program.Salon_Num = Salon_Num;
    program.Starting_hour = StartAt;
    program.Ending_hour=EndsAt;

    

    Program.push_back(program);
    if(counter==0){
        tempPlace=Place;
        counter++;
    }
    else{
        counter++;
        if(tempPlace==Place){
        
        }else{
         tempNumbers.push_back(counter-1);
         tempPlace=Place;
        }
    }
}

tempNumbers.push_back(counter);



//Capacity txt
ifstream Salon_txt(path+"/capacity.txt");
int i=0;
getline(Salon_txt,temp);
while (getline(Salon_txt, temp)) {    
stringstream ss(temp);
string PlaceName, SalonName;
int Capacity;
ss >> PlaceName >> SalonName >> Capacity;

while(PlaceName==Program[i].Place && SalonName==Program[i].Salon_Num){
    Program[i].capacity=Capacity;
    i++;
    }
    
   }

int size=tempNumbers.size();


int f=0;
vector<daily_program> selectedPrograms;

ofstream file_new3(output_path+"/best_for_eachplace.txt");

file_new3.is_open(); 

for(int i=0;i<size;i++){
      
        vector<daily_program> copied_program(Program.begin()+f, Program.begin() + tempNumbers[i]);

        daily_program* arr = &copied_program[0];

        pair<int,vector<daily_program> > profit = findMaxProfit(arr, copied_program.size());

        file_new3 << profit.second[i].Place<<"-->" << profit.first << endl;
        int size_of_calender=calendars.size();
        for (int m = 0; m < size_of_calender; m++) {
    if (calendars[m].Places == profit.second[i].Place) {
        calendars[m].profit=profit.first;
        }
    }

for (auto it = profit.second.rbegin(); it != profit.second.rend(); ++it) {
    const auto& program = *it;
    file_new3 << program.Place << "\t" << program.Salon_Num << "\t"<<program.Starting_hour << "\t" << program.Ending_hour << "\t"<< endl;
}
file_new3<<endl;

        selectedPrograms.clear();
 
        f=tempNumbers[i];
    }   
    
Calendar* arr2 = &calendars[0];

pair<int, vector<Calendar> > profit2 = findMaxProfitCalendar(arr2, calendars.size());
cout<<endl;
int total_profit_sum=0;

for (auto it = profit2.second.rbegin(); it != profit2.second.rend(); ++it) {
    const auto& program = *it;
    

    double fark=(program.starting_Day)-0.05;
    //cout<<"FARK: "<<fark<<endl;
    double fark2=(program.finishing_Day)-0.06;
    //cout<<"FARK 2: "<<fark2<<endl;
    if(abs(fark - round(fark)) < 0.0001){
        if(abs(fark2 - round(fark2)) < 0.0001){
            //cout<<endl;
            //cout<< "special case"<< program.Places << "\t" << program.starting_Day << "\t"<<program.finishing_Day << "\t"<< endl;
            //cout<<"first"<<(program.profit)*31;
            total_profit_sum+=(program.profit)*31;
            //cout<<"second"<<program.profit*(static_cast<int>(program.starting_Day));
            total_profit_sum-=program.profit*(static_cast<int>(program.starting_Day));
            //cout<<"third"<<program.profit*(static_cast<int>(program.finishing_Day)-1);
            total_profit_sum+=program.profit*(static_cast<int>(program.finishing_Day));
            it->first_month="May";
            it->second_month="June";
            //cout<<"Total profit:"<< total_profit_sum<<endl;
            //cout<<endl;

        }
        else{
        //cout<<endl;
        //cout << program.Places << "\t" << program.starting_Day << "\t"<<program.finishing_Day << "\t"<< endl;
        //cout<<"Anlık kar"<<static_cast<int>(program.finishing_Day-program.starting_Day)*program.profit<<endl;
        total_profit_sum+=(static_cast<int>(program.finishing_Day)-static_cast<int>(program.starting_Day))*program.profit;
        //cout<<"Total profit:"<< total_profit_sum<<endl;
        //cout<<endl;
        it->first_month="May";
        it->second_month="May";
        }
    }

    else if(abs(fark2 - round(fark2)) < 0.0001){
            //cout << program.Places << "\t" << program.starting_Day << "\t"<<program.finishing_Day << "\t"<< endl;
            //cout<<"Anlık kar"<<static_cast<int>(program.finishing_Day-program.starting_Day)*program.profit<<endl;
            total_profit_sum+=(static_cast<int>(program.finishing_Day)-static_cast<int>(program.starting_Day))*program.profit;
            //cout<<"Total profit:"<< total_profit_sum<<endl;
            //cout<<endl;
            it->first_month="June";
            it->second_month="June";
        }
    



}

ofstream file_new(output_path+"/best_tour.txt");


if(file_new.is_open()){
    file_new << "Total Revenue -->"<< total_profit_sum<<endl;
    for (auto it = profit2.second.rbegin(); it != profit2.second.rend(); ++it) {
        const auto& program = *it;
        file_new << program.Places  <<"\t" <<program.first_month <<"\t" << static_cast<int>(program.starting_Day) <<"\t" <<   program.second_month<<"\t"<< static_cast<int>(program.finishing_Day) << "\t"<< endl;
    }
}



cout<<endl;

ifstream assets_file(path+"/assets.txt");
string temp_2;
vector<Asset> assets;

getline(assets_file,temp_2);
while (getline(assets_file, temp_2)) {
stringstream ss(temp_2);
string name_Asset;
int price_Asset;
double value_Asset;


ss >> name_Asset >> price_Asset >> value_Asset;

    Asset temp_Asset;
    temp_Asset.name = name_Asset;
    temp_Asset.price = price_Asset;
    temp_Asset.value = value_Asset;
    assets.push_back(temp_Asset);
}

ofstream file_new1(output_path+"/upgrade_list.txt");

if(file_new1.is_open()){
     pair<double,vector<Asset> > selectedAssets  = selectAssets(assets, total_profit_sum);
     file_new1<<"Total Value --> "<<selectedAssets.first<<endl;

  for (const Asset& asset : selectedAssets.second) {
        file_new1 << asset.name << endl;
       
    }
}

}
 




