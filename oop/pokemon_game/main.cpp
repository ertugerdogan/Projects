#include <iostream> 
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "pokemon.h"

using namespace std;

int NAME_COUNTER = 0;   //Use this to keep track of the enemy names
int POK_COUNTER = 0;    //Use this to keep track of the pokemon names
int PLAYER_POKEMON_ATTACK = 20; //You don't have to use this variable but its here if you need it
int ENEMY_POKEMON_ATTACK = 10;  //You don't have to use this variable but its here if you need it
//--------------------------------------------------------------//



//-------------Do Not Change These Function Definitions-------------//
string* readEnemyNames(const char*);
string* readPokemonNames(const char*);
player characterCreate(string, int);
void mainMenu();
void fightEnemy(player*, string*, string*);
void catchPokemon(player*, string*);
//------------------------------------------------------------------//


//-------------Do Not Change This Function-------------//
int main(int argc, char* argv[]){
	system("clear");

    string* enemyNames = readEnemyNames(argv[1]);         
    string* pokemonNames = readPokemonNames(argv[2]);
    

    string playerName;
    int pokemonChoice;

    cout << "Welcome to the Pokemon Game! \n" << endl;
    cout << "Please enter your name: "; 
    cin >> playerName;
    cout << "Please choose one of these pokemons as your pokemon: \n1- Bulbasaur \n2- Charmender \n3- Squirtle \nChoice: ";
    cin >> pokemonChoice;

    //---Character Creation--//
    player newPlayer = characterCreate(playerName, pokemonChoice);
    
    int menuChoice;

    while(true){
        mainMenu(); 
        cin>>menuChoice;

        switch (menuChoice){
        case 1:
            fightEnemy(&newPlayer, enemyNames, pokemonNames);
            break;
        case 2:
            catchPokemon(&newPlayer, pokemonNames);
            break;
        case 3:
            cout<<newPlayer.showPokemonNumber()<<endl;
            break;
        case 4:
            cout<<newPlayer.showPokeballNumber()<<endl;
            break;
        case 5:
            cout<<newPlayer.showBadgeNumber()<<endl;
            break;
        case 6:
            cout << endl;
            cout << "------- Pokedex -------" <<endl;
            newPlayer.playerPokedex.printPokedex();
            break;
        case 7:
            //---Deletes Dynamic Arrays From Memory and Exits---//
            delete[] enemyNames;
            delete[] pokemonNames;
            return EXIT_SUCCESS;
            break;
  
        default:
            cout << "Please enter a valid number!!!" << endl;
            break;
        }
    }
    return EXIT_FAILURE;
};
//-----------------------------------------------------//

//-------------Code This Function-------------//
/*string* readEnemyNames(const char* argv){
    ifstream file_in;  
    file_in.open("enemyNames.txt");
    int size=0;
    int i=0;

    while(!file_in.eof()){
        if(NAME_COUNTER<1){
            cin>>size;
            NAME_COUNTER++;
        }
        else{
            //string names[size];
            string *names = new string[size];
            cin>>names[i]; 
            //cin>>names[i];
            i++;
        }
    }

};*/






/*string* readEnemyNames(const char* argv){
    ifstream file_in;  

    file_in.open(argv);

    int index = 0;
    int arrayLength = 0;
    string firstWord;

    if(file_in.is_open())
        {
            file_in >> firstWord;
            file_in >> arrayLength;

            string* arrayOfWords;
            arrayOfWords = new string[arrayLength];

            while(!file_in.eof())
            {
                file_in >> arrayOfWords[index];
                cout << arrayOfWords[index];
                cout << "\n";
                index++;
            }

           //delete [] arrayOfWords;

           return arrayOfWords;
            file_in.close();
        }

}*/


string* readEnemyNames(const char* argv){
    ifstream file;  

    file.open(argv);

    int index = 0;
    int arrayLength = 0;
    int firstWord;

    
    string* arrayOfWords;
    string word;

    if(file.is_open())
        {
            file >> firstWord;
            arrayLength = firstWord;

            arrayOfWords = new string[arrayLength];

            while(!file.eof())
            {
                file >> word;
                arrayOfWords[index] = word;
                index++;
            }


            file.close();
        }
        return arrayOfWords;

};


string* readPokemonNames(const char* argv){
    ifstream file;  

    file.open(argv);

    int index = 0;
    int arrayLength = 0;
    int firstWord;

    string* arrayOfWords;


    if(file.is_open())
        {
            file >> firstWord;
            arrayLength = firstWord;

            arrayOfWords = new string[arrayLength];

            while(!file.eof())
            {
                file >> arrayOfWords[index];
                index++;
            }


            file.close();
        }
        return arrayOfWords;

};
//-----------------------------------------------------//

//-------------Code This Function-------------//
player characterCreate(string playerName, int pokemonChoice){
    //\n1- Bulbasaur \n2- Charmender \n3- Squirtle
    
    string pokemonname;
    string name=playerName;

    if(pokemonChoice==1){
        pokemonname="Bulbasaur";
    }

     if(pokemonChoice==2){
        pokemonname="Charmender";    
    }

    if(pokemonChoice==3){
        pokemonname="Squirtle"; 
    }

    pokemon Pokemon(pokemonname,PLAYER_POKEMON_ATTACK);
    player newPlayer(name,Pokemon);
    /*if(pokemonChoice==1){
        pokemon Bulbasur("Bulbasaur", 100);
        player newPlayer(playerName, Bulbasur);
    }
    if(pokemonChoice==2){
        pokemon Charmender("Charmender", 100);
        player newPlayer(playerName, Charmender);
    }
    if(pokemonChoice==3){
        pokemon Squirtle("Bulbasaur", 100);
        player newPlayer(playerName, Squirtle);
    }*/

    return newPlayer;
};
//--------------------------------------------//

//-------------Do Not Change This Function-------------//
void mainMenu(){
    cout << endl;
    cout << "-------- Menu --------" << endl;
    cout << "1. Fight for a badge" << endl;
    cout << "2. Catch a Pokemon" << endl;
    cout << "3. Number of Pokemons" << endl;
    cout << "4. Number of Pokeballs " << endl;
    cout << "5. Number of Badges" << endl;
    cout << "6. Pokedex" << endl;
    cout << "7. Exit" << endl;
    cout << endl;
    cout << "Choice: ";
};
//-----------------------------------------------------//

//-------------Code This Function-------------//
void fightEnemy(player* newPlayer, string* enemyNames, string* pokemonNames){

//pokemon* badguypokemon=new pokemon("Alakazam",10);
pokemon* badguypokemon=new pokemon(pokemonNames[POK_COUNTER],10);

POK_COUNTER++;
//string* namebadguy=enemyNames;
//player *badguy=new player(*namebadguy,badguypokemon);

player *badguy=new player(enemyNames[NAME_COUNTER],*badguypokemon);

//badguy->playerPokedex.updatePokedex(*badguypokemon);
newPlayer->playerPokedex.updatePokedex(*badguypokemon);
int choice;

cout << "You encounter with " << badguy->get_name() << " and his/hers pokemon " << badguypokemon->getname() << endl << badguypokemon->getname() <<" Health: 100 Attack: 10\n1- Fight\n2- Runaway\nChoice: ";

cin >> choice;
//newPlayer->getPokemon().gethpValue();
int playerHealth = 100;


//newPlayer->getPokemon().gethpValue();
  while(choice==1){
      if(badguypokemon->gethpValue()==20){
          //////
          playerHealth -= 10;
          //////
          badguypokemon->sethpValue(0);
               cout<<"Your Pokemons Health: "<<playerHealth<<endl<<badguy->get_name()<<" Pokemons Health: "<<badguypokemon->gethpValue()<<endl<<"You Won!"<<endl;
               
               newPlayer->battleWon();
               break;
           }
           else{
               //////
                    playerHealth -= 10;
               //////
       badguypokemon->sethpValue(badguypokemon->gethpValue()-20);
       newPlayer->getPokemon().sethpValue(newPlayer->getPokemon().gethpValue()-10);
       cout<<"Your Pokemons Health: "<<playerHealth<<endl<<badguy->get_name()<<" Pokemons Health: "<<badguypokemon->gethpValue()<<endl;
       cout<<"1- Fight"<<endl<<"2- Runaway"<<endl<< "Choice: ";
       cin >> choice;
               }
           
   }

   if(choice==2){

   }

delete badguy;
delete badguypokemon;
};
//--------------------------------------------//

//-------------Code This Function-------------//
void catchPokemon(player* newPlayer, string* pokemonNames){
     int choice;
     pokemon* catchedpokemon=new pokemon(pokemonNames[POK_COUNTER],ENEMY_POKEMON_ATTACK);
     POK_COUNTER++;
    
   cout <<"You encounter with "<<catchedpokemon->getname()<<" Health: "<< catchedpokemon->gethpValue() <<" Attack: "<< catchedpokemon->getatkValue()<<endl<< "1- Catch"<<endl<<"2- Runaway"<<endl<<"Choice: ";
   cin >> choice;
   if(choice==1){
       cout <<"You catch "<<catchedpokemon->getname()<<endl;
       newPlayer->playerPokedex.updatePokedex(*catchedpokemon);
       newPlayer->catchPokemon();
   }

   if(choice==2){
       newPlayer->playerPokedex.updatePokedex(*catchedpokemon);
   }

   delete catchedpokemon;
};
//--------------------------------------------//
