#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
using namespace std;

class Compare
{
public:
    bool operator()(pair<int,int> a, pair<int,int> b)
    {
        bool cond = a.second<b.second;
        if (a.second == b.second) 
            cond = a.first > b.first;
        return cond;
    }
};

int main(int argc, char const *argv[]){
    int number_of_cities,number_of_bakeries;
    float threshold;
    vector<int> bakeries;
    ifstream f(argv[1]);

    string line;
    getline(f, line);
    stringstream ss(line);
    ss >> number_of_cities >> number_of_bakeries >> threshold;
    vector<vector<int>> Graph(number_of_cities, vector<int>(number_of_cities, -1));

    vector<bool> city_transported(number_of_cities, false);

    vector<vector<int>> cities(number_of_cities, vector<int>(3));

    vector<priority_queue<pair<int,int>,vector<pair<int,int>>,Compare>> Baker_priorityq(number_of_bakeries);

    getline(f, line);
    stringstream ss2(line);
    vector<queue<int>> newDestinations(number_of_bakeries);

    for(int i = 0; i < number_of_bakeries; i++){//bakery vector completed
        string temp_bakery;
        ss2 >> temp_bakery;
        int temp_bakery_int = stoi(temp_bakery);
        bakeries.push_back(temp_bakery_int);
    }
    int i=0;
    while(getline(f, line)){//city variables assigned to 2D vector.
        stringstream ss3(line);
        ss3 >> cities[i][0]  >> cities[i][1]  >> cities[i][2];
        city_transported[i]=false;
        i++;
    }
    int k = 0, j = 0;
    while (k < number_of_cities) {
        while (j < number_of_cities) {
            Graph[k][j] = -1;
            Graph[j][k] = -1;
            int plow = (cities[k][2] >= cities[j][2]) ? (cities[k][2] - cities[j][2]) : (cities[j][2] - cities[k][2]);
            float mean = (cities[k][2] + cities[j][2]) / 2.0;
        if (plow <= mean * threshold && plow!=0) {
            Graph[k][j] = plow;
            Graph[j][k] = plow;
            }
        j++;
        }
    k++;
    j = k;
} 
    int m = 0;
   while (m < number_of_bakeries) {
       city_transported[bakeries[m]] = true;
       int j = 0;
        while (j < number_of_cities) {
            if (Graph[bakeries[m]][j] > 0 && !city_transported[j] && bakeries[m] != j) {//
                Baker_priorityq[m].emplace(make_pair( j,Graph[bakeries[m]][j]));
            }
            j++;
        }
        m++;
}
    int current_city = 0;
    while (current_city < number_of_cities) {
    int bakery_move = current_city - (current_city / number_of_bakeries) * number_of_bakeries; // to iterate everyone  0 1 2
    while (!Baker_priorityq[bakery_move].empty()) {
        int next_station = Baker_priorityq[bakery_move].top().first;
        Baker_priorityq[bakery_move].pop();
        bool Istrue = city_transported[next_station];
        if (!Istrue) {
            newDestinations[bakery_move].push(next_station);
            city_transported[next_station] = true;
            for (int j = 0; j < number_of_cities; j++) {
                if (Graph[next_station][j] > 0 && !city_transported[j])
                    Baker_priorityq[bakery_move].emplace(make_pair(j, Graph[next_station][j]));
            }
            break;
        }
    }
    current_city++;
}
ofstream outputFile("prim.txt");
int size = bakeries.size();
for (int i = 0; i < size; i++) {
    outputFile << "k" << i << " ";
    outputFile << newDestinations[i].size() + 1 << endl;
    outputFile << bakeries[i];
    if (!newDestinations[i].empty()) {
        outputFile << "->";
        while (!newDestinations[i].empty()) {
            outputFile << newDestinations[i].front();
            newDestinations[i].pop();
            if (!newDestinations[i].empty()) {
                outputFile << "->";
            }
        }
    }
    outputFile << endl;
}
outputFile.close();
exit(0);
}