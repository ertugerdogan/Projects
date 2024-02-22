#pragma once
#include "MultiNode.h"
#include <string>

using namespace std;

class MultiList{
    private:
        DateNode* head;
        DateNode* tail;

    public:
        MultiList();
        ~MultiList();
        void add_node(string,string,string);
        void remove_node(string,string);
        void print_list();
        DateNode* search(string);
};