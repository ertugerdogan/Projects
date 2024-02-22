#include "utils.h"


using namespace std;

StatisticalDistribution* choose_function(int expression){

    
    StatisticalDistribution *dist;
    if(expression==0){
        dist= new NormalDistribution();
    }else if(expression==1){
        dist= new UniformDistribution();
    }else if(expression==2){
        dist=new ExponentialDistribution();
    }else{
        dist=nullptr;
        throw "Unidentified distribution function!";    
    }
    return dist;
};

///Warning: Do not forget to increment seed_value by one at each trial. Otherwise, you will get the same sample at each trial.


double many_trials(StatisticalDistribution *dist , vector<double> random_sample,double t_value, int trials, int sample_size, int seed_value){
    //Create a random sample and calculate the confidence interval for many times (repeat
    //the number of times given as "trials"). Then, return the precision described below:
    //Success describes how many times your calculated confidence interval covered the theoretical mean.
    
    //precision=success/trials
    //1-calculatesuccess 
    double success=0.0;
        for(int i=0;i<trials;i++){
        std::vector<double> rand_sample=dist->calculate_confidence_interval(random_sample, sample_size, t_value);
        seed_value++;
        random_sample = dist->sample(sample_size, seed_value);
        if(rand_sample[0]<dist->getmean()  && dist->getmean()<rand_sample[2]){
            success++;}}
        double precision=success;
        precision/=trials;
        return precision;
};
//Warning: Do not forget to increment seed_value by one at each trial. Otherwise, you will
//get the same sample at each trial

//You can figure out what numbers in the test cases represent by examining "main.cpp" file.
