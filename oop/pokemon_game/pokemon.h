#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;


class pokemon{
    
    private:
        string name;
        int hpValue;
        int atkValue;
    public:
    string getname();
    int gethpValue();
    int sethpValue();
    void sethpValue(int hp);
    int getatkValue();
    pokemon(){
        //cout << "Default constructor called!";
        }
    pokemon(string pname, int pattack){
        this->name=pname;
        this->atkValue=pattack;
        this->hpValue=100;
    }
    pokemon(const pokemon &old)  
    {
        name=old.name;
        hpValue=old.hpValue;
        atkValue=old.atkValue;
        //cout << "Copy Constructor called!\n";
    }
       
};

class pokedex{
    //-------------Do Not Change Given Variables-------------//
    //-------------You Can Add New Variables If Neccessary-------------//
    private:
        pokemon pokedexArray[100];
        int value;
    public:
    pokedex(){
        this->value=0;
    }
    int getvalue(){
        return this->value;     
    }
    void setvalue(int value){
        this->value=value;   
    }
    void updatePokedex(pokemon NewPokemon){
        int i=0;
        bool controller=false;
        int size=this->getvalue();
        while(i<=size){
            if(pokedexArray[i].getname()==NewPokemon.getname()){
                controller=true;    
            }
            else{
                i++;
            }
        }
        
        if(controller==false){
            pokemon TempPokemon(NewPokemon);
            pokedexArray[size]=TempPokemon;
            size++;
            this->setvalue(size);
        }
    }

    void printPokedex(){
        int i=0;
        int size;
        size=getvalue();
        while(i<size){
            string name=pokedexArray[i].getname();
            cout<<name << endl;
            i++;
        }

    }
       
};

class player{
    private:
    //-------------Do Not Change Given Variables-------------//
    //-------------You Can Add New Variables If Neccessary-------------//
        string name;
        int pokemonNumber;
        int pokeballNumber;
        int badgeNumber;
        pokemon playerPokemon;
    public:
        pokedex playerPokedex;
        player() {
            this->pokeballNumber=10;
            this->pokemonNumber = 0;
            this->badgeNumber = 0;
         }
        player(string pname, pokemon Pokemon){
            this->name=pname;
            this->playerPokemon=Pokemon;

            this->pokeballNumber=10;
            this->pokemonNumber = 0;
            this->badgeNumber = 0;
        }
        player(string pname, pokemon *Pokemon){
            this->name=pname;
            this->playerPokemon=*Pokemon;

            this->pokeballNumber=10;
            this->pokemonNumber = 0;
            this->badgeNumber = 0;
        }
        int showPokemonNumber(){
            return this->pokemonNumber;
        }

        int showPokeballNumber(){
            return this->pokeballNumber;
        }

        int showBadgeNumber(){
            return this->badgeNumber;
        }

        pokemon getPokemon(){
            return this->playerPokemon;
        }

        string get_name(){
            return this->name;
        }

        void battleWon(){
            //int badgenumberup=1;
            //int pokeballumberup=3;
            int currentpokeballnumber=this->pokeballNumber;
            int currentbadgenumber=this->badgeNumber;
            currentpokeballnumber+=3;
            currentbadgenumber+=1;
            this->badgeNumber=currentbadgenumber;
            this->pokeballNumber=currentpokeballnumber;
        }

        void catchPokemon(){
            this->pokemonNumber+=1;
            this->pokeballNumber-=1;
        }
        
};

class enemy{
    //-------------Do Not Change Given Variables-------------//
    //-------------You Can Add New Variables If Neccessary-------------//
    private:
        string name;
        pokemon enemyPokemon;
    public:
        enemy();
        enemy(string ename,pokemon eenemyPokemon){
            this->name=ename;
            this->enemyPokemon=eenemyPokemon;
        }

        pokemon getPokemon(){
            return this->enemyPokemon;
        }

        string getName(){
            return this->name;
        }
};

#endif