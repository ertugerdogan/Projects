#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <list>


using namespace std;

enum COLOR
{
    RED,
    BLACK
};

class Node
{
public:
    string process_name;
    int arrival_time;
    int process_max_time;
    int current_vrun_time;
    COLOR color;
    Node *left, *right, *parent;

    Node(string process_name, int arrival_time, int process_max_time) : process_name(process_name), arrival_time(arrival_time), process_max_time(process_max_time)
    {
        parent = left = right = NULL;
        current_vrun_time = 0;
        color = RED;
    }
    Node *UncleNode()//It returns the uncle node
    {
        if (parent == NULL or parent->parent == NULL)
            return NULL;
        if (parent->isOnLeft())
            return parent->parent->right;
        else
            return parent->parent->left;
    }
    bool isOnLeft() { return this == parent->left; }
    Node *sibling()//It returns the sibling node
    {
        if (parent == NULL)
            return NULL;
        if (isOnLeft())
            return parent->right;
        return parent->left;
    }
    void move_down(Node *nParent)
    {
        if (parent != NULL)
        {
            if (isOnLeft())
            {
                parent->left = nParent;
            }
            else
            {
                parent->right = nParent;
            }
        }
        nParent->parent = parent;
        parent = nParent;
    }

    bool has_redChild()//It returns true if red child exist
    {
        return (left != NULL and left->color == RED) or
               (right != NULL and right->color == RED);
    }
};

class RedBlackTree
{
    Node *root;
    void leftRotate(Node *x)//LEFT ROTATE FUNCTION is used to maintain the balance of the tree.
    {
        Node *nParent = x->right;
        if (x == root)
            root = nParent;

        x->move_down(nParent);
        x->right = nParent->left;
        if (nParent->left != NULL){
            nParent->left->parent = x;
        }
        nParent->left = x;
    }

    void rightRotate(Node *x)//RIGHT ROTATE FUNCTION is used to maintain the balance of the tree.
    {
        Node *nParent = x->left;
        if (x == root){
            root = nParent;
        }
        x->move_down(nParent);
        x->left = nParent->right;
        if (nParent->right != NULL){
            nParent->right->parent = x;
        }
        nParent->right = x;
    }

    void color_swap(Node *x1, Node *x2)//SWAPS THE COLORS
    {
        COLOR temp;
        temp = x1->color;
        x1->color = x2->color;
        x2->color = temp;
    }

    void Valueswap(Node *u, Node *v)//SWAPS THE VALUES
    {
    std::swap(u->process_name, v->process_name);
    std::swap(u->arrival_time, v->arrival_time);
    std::swap(u->process_max_time, v->process_max_time);
    std::swap(u->current_vrun_time, v->current_vrun_time);
    }
    void Red_fix(Node *x)//It fixed colors after insert and update
    {
        if (x == root)
        {
            x->color = BLACK;
            return;
        }
        Node *parent = x->parent, *grandparent = parent->parent, *UncleNode = x->UncleNode();
        if (parent->color != BLACK)
        {
            if (UncleNode != NULL && UncleNode->color == RED)
            {
                parent->color = BLACK;
                UncleNode->color = BLACK;
                grandparent->color = RED;
                Red_fix(grandparent);
            }
            else
            {
                if (parent->isOnLeft())
                {
                    if (x->isOnLeft())
                    {
                        color_swap(parent, grandparent);
                    }
                    else
                    {
                        leftRotate(parent);
                        color_swap(x, grandparent);
                    }
                    rightRotate(grandparent);
                }
                else
                {
                    if (x->isOnLeft())
                    {
                        rightRotate(parent);
                        color_swap(x, grandparent);
                    }
                    else
                    {
                        color_swap(parent, grandparent);
                    }
                    leftRotate(grandparent);
                }
            }
        }
    }
    Node *successor(Node *x)// comes  after a given node in an in-order traversal
    {
        Node *temp = x;

        while (temp->left != NULL)
            temp = temp->left;

        return temp;
    }
    Node *BST_replace(Node *x)
    {
        if (x->left != NULL and x->right != NULL)
            return successor(x->right);
        if (x->left == NULL and x->right == NULL)
            return NULL;
        if (x->left != NULL)
            return x->left;
        else
            return x->right;
    }
    void deleteNode(Node *v)
    {
        Node *u = BST_replace(v);
        bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
        Node *parent = v->parent;

        if (u == NULL)
        {
            if (v == root)
            {
                root = NULL;
            }
            else
            {
                if (uvBlack)
                {
                    fixDoubleBlack(v);
                }
                else
                {
                    if (v->sibling() != NULL)
                        v->sibling()->color = RED;
                }
                if (v->isOnLeft())
                {
                    parent->left = NULL;
                }
                else
                {
                    parent->right = NULL;
                }
            }
            delete v;
            return;
        }

        if (v->left == NULL or v->right == NULL)
        {
            if (v == root)
            {
                v->process_name = u->process_name;
                v->arrival_time = u->arrival_time;
                v->process_max_time = u->process_max_time;
                v->current_vrun_time = u->current_vrun_time;
                v->left = v->right = NULL;
                delete u;
            }
            else
            {
                if (v->isOnLeft())
                {
                    parent->left = u;
                }
                else
                {
                    parent->right = u;
                }
                delete v;
                u->parent = parent;
                if (uvBlack)
                {
                    fixDoubleBlack(u);
                }
                else
                {
                    u->color = BLACK;
                }
            }
            return;
        }
        Valueswap(u, v);
        deleteNode(u);
    }

    void fixDoubleBlack(Node *x)//t is called when a black node is deleted and its sibling is also black.
    {
        if (x == root)
            return;

        Node *sibling = x->sibling(), *parent = x->parent;
        if (sibling == NULL)
        {
            fixDoubleBlack(parent);
        }
        else
        {
            if (sibling->color == RED)
            {
                parent->color = RED;
                sibling->color = BLACK;
                if (sibling->isOnLeft())
                {
                    rightRotate(parent);
                }
                else
                {
                    leftRotate(parent);
                }
                fixDoubleBlack(x);
            }
            else
            {
                if (sibling->has_redChild())
                {
                    if (sibling->left != NULL and sibling->left->color == RED)
                    {
                        if (sibling->isOnLeft())
                        {
                            sibling->left->color = sibling->color;
                            sibling->color = parent->color;
                            rightRotate(parent);
                        }
                        else
                        {
                            sibling->left->color = parent->color;
                            rightRotate(sibling);
                            leftRotate(parent);
                        }
                    }
                    else
                    {
                        if (sibling->isOnLeft())
                        {
                            sibling->right->color = parent->color;
                            leftRotate(sibling);
                            rightRotate(parent);
                        }
                        else
                        {
                            sibling->right->color = sibling->color;
                            sibling->color = parent->color;
                            leftRotate(parent);
                        }
                    }
                    parent->color = BLACK;
                }
                else
                {
                    sibling->color = RED;
                    if (parent->color == BLACK)
                        fixDoubleBlack(parent);
                    else
                        parent->color = BLACK;
                }
            }
        }
    }

    void inorder(Node *x)//Inorder traverse function.
    {
        if (x == NULL){
            return;
        }
        inorder(x->left);
        if(x->right!=NULL || (x->parent!=NULL && x->right==NULL && x->left==NULL) ){
            if(x->color == RED){
            cout << x->process_name << ":" << x->current_vrun_time << "-Red;";
        }
        else if(x->color == BLACK){
            cout << x->process_name << ":" << x->current_vrun_time << "-Black;";
        }
        }
        else{
            if(x->color == RED){
            cout << x->process_name << ":" << x->current_vrun_time << "-Red";
        }
        else if(x->color == BLACK){
            cout << x->process_name << ":" << x->current_vrun_time << "-Black";
        }
        }
        inorder(x->right);
    }
public:
    int min_vruntime = 0;
    RedBlackTree() { root = NULL; }
    Node *getRoot() { return root; }
    Node *search(int n)//It finds the place for new upcoming node. After this function
    {
        Node *temp = root;
        while (temp != NULL)
        {
            if (n < temp->current_vrun_time)
            {
                if (temp->left == NULL)
                    break;
                else
                    temp = temp->left;
            }
            else
            {
                if (temp->right == NULL)
                    break;
                else
                    temp = temp->right;
            }
        }
        return temp;
    }
    void insertWithUpdate(string process_name, int arrival_time, int process_max_time,int current_vrun_time)//It will be used with update. 
    {
        Node *newNode = new Node(process_name, arrival_time, process_max_time);
        newNode->current_vrun_time = current_vrun_time;
        if (root != NULL)
        {
            Node *temp = search(newNode->current_vrun_time);
            newNode->parent = temp;
            if (newNode->current_vrun_time < temp->current_vrun_time)
                temp->left = newNode;
            else
                temp->right = newNode;
            Red_fix(newNode);
        }
        else
        {
            newNode->color = BLACK;
            root = newNode;    
        }
    }
    void insert(string process_name,int arrival_time,int process_max_time)
    {
        Node *newNode = new Node(process_name, arrival_time, process_max_time);
        if (root == NULL)
        {
            newNode->color = BLACK;
            root = newNode;
        }
        else
        {
            Node *temp = search(newNode->current_vrun_time);
            newNode->parent = temp;
            if (newNode->current_vrun_time < temp->current_vrun_time)
                temp->left = newNode;
            else
                 temp->right = newNode;
            Red_fix(newNode);
        }
    }
    void printInOrder()//It prints the values inorder traverse
    {
        if (root == NULL)
            cout << "Tree is empty" << endl;
        else
            inorder(root);
    }

 
    Node *getInorderFirstNode(Node *root)//It gives the first node on inorder traverse
    {
        if (!root)
            return nullptr;

        Node *curr = root;
        while (curr->left)
        {
            curr = curr->left;
        }
        return curr;
    }


    void Update(Node *x,list<string> &Finished_p)//To update the values, delete the tree first. Then add it again with updated features.
    {
        min_vruntime = x->current_vrun_time;
        string name = x->process_name;
        int arrival_time = x->arrival_time;
        int p_vrun_time = x->process_max_time;
        int c_vrun_time = x->current_vrun_time + 1;
        if(x->parent != nullptr && c_vrun_time == x->parent->current_vrun_time){
            min_vruntime+=1;
            x->current_vrun_time = c_vrun_time;
            cout << "," << "Incomplete" ;
            return;
        }
        else if(x->right != nullptr && c_vrun_time == x->right->current_vrun_time){
            min_vruntime+=1;
            x->current_vrun_time = c_vrun_time;
            cout << "," << "Incomplete";
            return;
        }
        else{
            deleteNode(x);
            if (x->process_max_time == c_vrun_time)
            {
                Finished_p.push_back(name);

                cout << "," << "Complete"; // if Process is finished
                return;
            }
            else
            {
                 cout << "," << "Incomplete" ;
                 insertWithUpdate(name, arrival_time, p_vrun_time, c_vrun_time);// if  Process is not finished
            }
        }
    }
};

int main()
{
    std::ofstream out("output.txt");

    // Redirect the output of cout to the output file
    std::cout.rdbuf(out.rdbuf());
    auto begin = std::chrono::high_resolution_clock::now();
    RedBlackTree tree;//Red black tree
    list<Node> datas;// I pushed these nodes to the list to keep them until the time comes.  
    list<string> Finished_p;//A list that I use when printing the finished processes at the end. It contains process names.
    int process_number;
    int max_time;
    int current_cpu_time=0;
    string line;
    fstream file("input.txt", ios::in);
    file.is_open();
    string var,var_1, var_2, var_3;
    getline(file, line);
    stringstream strheader(line);
    getline(strheader, var, ' ');
    process_number = stoi(var);
    getline(strheader, var);
    max_time = stoi(var);
    
    while (getline(file, line))
    {
        stringstream str(line);
        getline(str, var_1, ' ');
        getline(str, var_2, ' ');
        getline(str, var_3);
        Node *node = new Node(var_1, stoi(var_2), stoi(var_3));
        datas.push_back(*node);
    }
      
    while(current_cpu_time<=max_time){//time simulation 
        while (datas.front().arrival_time == current_cpu_time)//Insert to tree, pop from datas 
        {
            tree.insert(datas.front().process_name, datas.front().arrival_time, datas.front().process_max_time);
            datas.pop_front();
        }
        if (tree.getRoot() != NULL)
        {
            cout<<current_cpu_time<<"," << tree.getInorderFirstNode(tree.getRoot())->process_name << "," << tree.getInorderFirstNode(tree.getRoot())->current_vrun_time << ","<< tree.min_vruntime << ",";
            tree.printInOrder();
            tree.Update(tree.getInorderFirstNode(tree.getRoot()),Finished_p);
            if(process_number == Finished_p.size()){
               cout << "d"<<endl;
             break;}else{
               cout << endl;
            }
            
        }else{
            cout <<current_cpu_time << ",-,-,-,-,-" << endl;
            }
        current_cpu_time++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    cout<<endl;
    cout << "Scheduling finished in " << time.count()* 1e-6 << " ms." << endl;
    cout << Finished_p.size() << " of " << process_number << " processes are completed."<<endl;
    cout << "The order of completion of the tasks: ";
    if(Finished_p.size()!=0){
        while(Finished_p.size() != 1){
        cout << Finished_p.front() << "-";
        Finished_p.pop_front();
    }
    cout << Finished_p.front()<<endl;
    }
    return 0;
}