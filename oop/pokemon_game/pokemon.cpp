#include <iostream>
#include <stdio.h>
#include <string.h>

#include "pokemon.h"

using namespace std;

        
       
        
string pokemon::getname(){
            return this->name;
        };

int pokemon::gethpValue(){
            return this->hpValue;
        };
int pokemon::getatkValue(){
            return this->atkValue;
        };

void pokemon::sethpValue(int hp){
        this->hpValue=hp;
    }




