#include <iostream>
#include <string>
#include "../include/MultiList.h"

using namespace std;

MultiList::MultiList()
{
    head=NULL;
    tail=NULL;
}

MultiList::~MultiList()
{
    DateNode* p1 = head;
    DateNode* n1 = head;
    TSiteNode* p2 = NULL;
    TSiteNode* n2 = NULL;

    while(n1!=NULL){
        n2 = n1->get_up();
        p2 = n2->get_up();
        while(n2!=NULL)
        {
            n2 = p2->get_up();
            delete p2;
            p2 = n2;
        }
        n1=p1->get_next();
        delete p1;
        p1=n1;
    }
}

/*DateNode* MultiList::search(string date)//to find the correct place according to date data
{
DateNode* current=head;//we are starting from the head

DateNode * ptr;//ptr is the pointer that we return 
// if(current->get_next()==NULL && current==head)
    if( current==head){
        if(current->get_date()<date){
            if(current->get_next()==NULL){
                ptr=current;
            }
            else{
                
            }
        }
        else{
            ptr=NULL;
        }
    }
    while(current->get_next()!=NULL){//Until the last node

        if(current->get_date()>date){//If our node size is bigger than input
            if(current->get_prev()==NULL){
              ptr=NULL;
                                     }
            else{
                ptr=current->get_prev(); 
                }
                                     }
        else{
            current=current->get_next();
            if(current->get_next()==NULL){
                if(date>current->get_date()){
                    ptr=current;
                                            }
                else{
                    ptr=current->get_prev();
                    }
                                            }
                                         
            }
                                      }
        

return ptr;

}*/

DateNode* MultiList::search(string date){
    DateNode* current=head;//we are starting from the head

    DateNode * ptr=NULL;//ptr is the pointer that we return 

    while(current!=NULL){
        if(current->get_date()>date  ){
            ptr=current->get_prev();
            break;
        }

        if(!current->get_next()){
            ptr = current;
            break;
        }
        current=current->get_next();
    }

  /*  if(current==head){
        if(current->get_date()<date){
            while(current->get_next()->get_date()<date){
                current=current->get_next();
            }
            ptr= current->get_prev();
        }
        else{
            if(current->get_next()==NULL){
                ptr= NULL;
            }
            
        }
    }*/

    return ptr;
}

/*
void MultiList::add_node(string date,string time,string site_name)
{

    DateNode* node= new DateNode(date); //To add node
    TSiteNode* Up= new TSiteNode(time, site_name);//To add upnode
    DateNode *current;//Current (temp)
    TSiteNode* currenti=NULL;

    if(head==NULL){//if head== NUll we should create list
        head=node;
        head->set_next(NULL);
        head->set_up(Up);
    }
    else{
        current=head;
        DateNode *previous;

        bool exist=false;//bool variable default false
        while(current->get_next()!=NULL){//if get_next is NULL stop
            if(date!=current->get_date()){//if date is not equal to the current.date
                /  if(current=!head){//current is not equal to head
                      previous=current->get_prev();
                      previous->set_next(current);
                  }/
                current=current->get_next();///if date is not equal to the current.date GO
            }
            else{
                exist=true;//if it is equal change the bool value
                //return or break idk
            }
        }

        if(current->get_next()==NULL){
            if(date==current->get_date()){
                exist=true;
            }
            else{

            }
        }

        current=head;
        DateNode *tracker=current;
        TSiteNode *trackeri;
        int counterup=0;

        if(exist==true){//the datenode is already exist in the list.
            //string date="2022/03/08";
            while(current->get_date()!=date){
                current=current->get_next();//we assign current to the head again so we need the find the equal node again
                                            }      

                if(current->get_up()==NULL){
                    current->set_up(Up);
                }   

                else{
                    if(current->get_up()->get_time()<time){//we find the equal node but now we will find correct place for the up node
                    currenti=current->get_up();
                    counterup++;
                        while(currenti->get_up()->get_time()<time && currenti)          {
                            currenti=currenti->get_up();
                            counterup++;
                                }
                        if(currenti->get_up()->get_time()>time){
                            Up->set_up(currenti->get_up());
                            currenti->set_up(Up);
                    }
                               }
                    if(current->get_up()->get_time()>time){
                    counterup++;//to assign the value of current->get_up()
                        for(int i=0;i<counterup;i++){
                            if (i ==0){
                            trackeri=tracker->get_up();
                                      }
                    
                            else      {
                            trackeri=trackeri->get_up();
                                      }
                             //to find the correct place of current->get_up()
                                            }
                       Up->set_up(trackeri);//We add the up node to currect place
                     current->set_up(Up);//We add the up node to currect place
                //upnodelar currenta eklenecek.
                                                  }
                }

                  

                                            
                        }                
        else{
            previous=search(date);//to find where is the place we should add the DateNode
            if(previous==NULL){
                 /previous->set_next(head);
                 head->set_next(previous);
                 head=previous;/
                 node->set_next(head);
                 head->set_prev(node);
                 head=node;
                 node->set_up(Up);
            }
            else{
                node->set_next(previous->get_next());//first we should assign the node->set_next()
                previous->set_next(node);
                node->set_prev(previous);
                node->get_next()->set_prev(node);
                int j=0;
                while(current->get_up()->get_time()<time){//we find the equal node but now we will find correct place for the up node
                    if(j==0){
                        currenti=current->get_up();
                        counterup++;
                    }
                    else{
                        currenti=currenti->get_up();
                        counterup++;
                    }

                }
                if(current->get_up()->get_time()>time){
                    counterup++;//to assign the value of current->get_up()

                    for(int i=0;i<counterup;i++){
                        if(i==0){
                            trackeri=tracker->get_up();//to find the correct place of current->get_up()
                        }
                        else{
                            trackeri=trackeri->get_up();//to find the correct place of current->get_up()

                        }
                    }

                    Up->set_up(trackeri);//We add the up node to currect place
                    currenti->set_up(Up);//We add the up node to currect place
                    //upnodelar currenta eklenecek.
                }
            }
        }

    }
}*/

void MultiList::add_node(string date,string time,string site_name)
{   
    DateNode *current;//Current (temp)
    current=head;
    //current=tail;
    bool exist=false;
    while(current){
        if(current->get_date()==date){
            exist=true;
            break;
        }
        current=current->get_next();
    }
    if(!exist){
        DateNode* node= new DateNode(date);
        DateNode* prev=search(date);
        node->set_up(NULL);
        node->set_prev(prev);
        if(!prev){
            node->set_prev(NULL);
            node->set_next(head);
            head=node;
        }else{
            node->set_next(prev->get_next());
            prev->set_next(node);
            
        }
        if(prev==tail){
            tail=node;
        }else{
            node->get_next()->set_prev(node);
        }
        current=node;
    }
    if((!current->get_next()) && (!current->get_prev())){
        tail = current;
    }
    TSiteNode* TempUp;//To add upnode
    TSiteNode* prevTempUp;
    TempUp=current->get_up();
    prevTempUp=NULL;
    
    while(TempUp){

     if(TempUp->get_time()>time){

         break;
     }
    prevTempUp=TempUp;
    TempUp=TempUp->get_up();

    }

    TSiteNode* newUp= new TSiteNode(time, site_name);
   
   
    if(!prevTempUp){
        newUp->set_up(current->get_up());
        current->set_up(newUp);
    }else{
        newUp->set_up(prevTempUp->get_up());
        prevTempUp->set_up(newUp);
    }



}



void MultiList::remove_node(string date,string time)
{
    DateNode* current=head;//Current DateNode will be using as a sheld
    DateNode* tracker=head;//Tracker
    TSiteNode* currenti;
    TSiteNode* trackeri;

    bool exist=false;
    int upCounter=0;

    while(current->get_date()!=date && current->get_next()!=NULL){
        current=current->get_next();
        if(current->get_date()==date){
            exist=true;
            break;
        }
    }

    if(current->get_date()==date && current->get_next()==NULL){
            exist=true;
        }
    

    currenti=current->get_up();
    trackeri=tracker->get_up();

    if(exist==true){


        if(currenti->get_time()==time){
            current->set_up(NULL);
        }

        else{

        while(currenti->get_time()!=time && currenti->get_up()!=NULL){
            currenti=currenti->get_up();
            upCounter++;// 2 olsun
        }

        for(int i=0;upCounter>i;i++){
            trackeri=trackeri->get_up();
        }

        trackeri->set_up(trackeri->get_up()->get_up());

        }

    }
}

void MultiList::print_list()
{
    DateNode* p_hor=head;
    TSiteNode* p_ver;

    while(p_hor)
    {
        cout<<p_hor->get_date()<<":"<<endl;
        p_ver=p_hor->get_up();
        while(p_ver)
        {
            cout<<p_ver->get_time()<<"->"<<p_ver->get_site_name()<<endl;
            p_ver=p_ver->get_up();
        }
        p_hor=p_hor->get_next();
    }

}