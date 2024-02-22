#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <map>

using namespace std;

int NODE_NUMBER = 0;
bool PATHFOUND = false;

class Node{
        public:
        int number;
        int x,y,p;
        bool next_to_source = false;

        Node(int x, int y, int p){
            this->x=x;
            this->y=y;
            this->p=p;
            number = NODE_NUMBER;
            NODE_NUMBER++;
        }
};


bool BFS(vector<vector<Node>>& adj, int src, int d_point, int v,int former[], int dist[])
{
    list<int> list_one;
    bool visited_nodes[v];    
    for (int i = 0; i < v; i++) {
        visited_nodes[i] = false;
        dist[i] = v;
        former[i] = -1;}

    visited_nodes[src] = true;
    dist[src] = 0;
    list_one.push_back(src);
    while (!list_one.empty()) {
        int u = list_one.front();
        list_one.pop_front();
        int size = adj[u].size();
        for (int i = 0; i < size; i++) {
            if (visited_nodes[adj[u][i].number] == false) {
                visited_nodes[adj[u][i].number] = true;
                dist[adj[u][i].number] = dist[u] + 1;
                former[adj[u][i].number] = u;
                list_one.push_back(adj[u][i].number);
                if (adj[u][i].number == d_point)
                    return true;
            }
        }
    }
    return false;
}

void printShortestDistance(vector<vector<Node>>& adj, int s, int d_point, int v)
{
    ofstream file("bfs.txt");
    int former[v], dist[v];

    if (BFS(adj, s, d_point, v, former, dist) == false) {
        file << "BFS:"<<endl;
        file<< "-1";
        return;
    }
    vector<int> path;
    int temp = d_point;
    path.push_back(temp);
    while (former[temp] != -1) {
        path.push_back(former[temp]);
        temp = former[temp];
    }if (file.is_open()) { 
       file << "BFS:"<<endl;
       file<<dist[d_point]<<" ";
       int path_size = path.size();
        for (int i = path_size - 1; i >= 0; i--){
            if(i!=0){
               file << path[i] << "->"; 
            }else{
               file << path[i];
            }}
    file.close();
    }            
}

vector<int> DFS(vector<vector<Node>>& adj, int v, vector<int> path, map<int, bool>& truth_map, int start, vector<int> &true_path, map<int,int> neighbors)
{     
    if(PATHFOUND){
        return true_path;
    }
    int num_nextvert;
    truth_map[v] = true;

    int size = adj[v].size();
    for(int i = 1; i < size; i++){
        num_nextvert = adj[v][i].number;
        int num_adjacent = neighbors.count(v);
        if(num_adjacent == 1 && !PATHFOUND && path.size() > 1){
            PATHFOUND = true;
            true_path = path;
        }if(!truth_map[num_nextvert]){
            path.push_back(num_nextvert);
            DFS(adj, num_nextvert, path, truth_map, start, true_path, neighbors);
            path.pop_back();
        }
    }
    return true_path;
}

map<int,int> find_vertices(vector<vector<Node>>& adj, int sorucekid){
    map<int,int> adjacents;
    int size2 = adj[sorucekid].size();
    for(int i = 0; i < size2; i++){
        adjacents[adj[sorucekid][i].number] = 0;
    }
    return adjacents;
}

void create_graph(vector<vector<Node>>& adj){
    int size = adj.size();
    int Graphto2d[size][size];

    ofstream file3("graph.txt");
    if(file3.is_open()){
        for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            Graphto2d[i][j] = 0;
        }
    }
    file3<<"Graph:"<<endl;
    for(int i = 0; i < size; i++){
        int size2 = adj[i].size();
        for(int j = 0; j < size2; j++){
            Graphto2d[i][adj[i][j].number] = 1;           
        }
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(i == j){
                Graphto2d[i][j] = 0;
            }
            file3 << Graphto2d[i][j] << " ";
        }
        file3 << endl;
    }
    file3.close();
    }  
}

int main(int argc, char const *argv[]){
    string inputxt = argv[1];
    ifstream f(inputxt);

    string line;

    vector<vector <Node> > adjList;

    string firstline;
    int num_of_kids, sourcekid, targetkid;

    getline(f, firstline);
    stringstream ss(firstline);
    ss >> num_of_kids >> sourcekid >> targetkid;
    
    while(getline(f,line)){
        stringstream ss(line);
        int x, y, p;
        ss >> x >> y >> p;
        Node newNode(x,y,p);  

        float distance;
        adjList.push_back(vector<Node>{newNode});  

        int size = adjList.size();
        for(int j = 0; j < size - 1; j++){

            Node tempnode = adjList[j][0];
            distance=(newNode.x-tempnode.x)*(newNode.x-tempnode.x)+(newNode.y-tempnode.y)*(newNode.y-tempnode.y);
            
            if(distance <= newNode.p && distance <= tempnode.p){
                adjList[j].push_back(newNode);
                adjList[adjList.size() - 1].push_back(tempnode);
            }
        }
        }
    map<int,int> adjacents = find_vertices(adjList, sourcekid);
    map<int, bool> truth_map;
    int size2 = adjList.size();
    for(int i = 0; i < size2; i++){truth_map[i] = false;}

    vector<int> path1;

    path1 = DFS(adjList, sourcekid, path1, truth_map, sourcekid, path1, adjacents);

    ofstream file2("dfs.txt");
     
    if(file2.is_open()){
        file2 << "DFS:"<<endl;
        int size3 = path1.size();

        if(path1.size() == 0){
           file2 << "-1";
        }else{
            file2 << size3 + 1 << " " << sourcekid << "->";
            int path_size = path1.size();
        for(int i = 0; i < path_size; i++){
            file2 << path1[i] << "->";
        }
        file2 << sourcekid;
    }
    file2.close();
    }
    cout << endl;
    printShortestDistance(adjList, sourcekid, targetkid, adjList.size());
      
    create_graph(adjList);
    exit(0);
}