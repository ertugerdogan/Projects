#include "statistics.h"
#include <random>
#include <iostream>


using namespace std;

const double StatisticalDistribution::getmean(){
    return this->mean;
}
vector<double> StatisticalDistribution::calculate_confidence_interval(vector<double> random_sample, int sample_size, double  t_value){
  //It will return a thee-element vector: [lower_bound,sample_mean, upper_bound].

  vector<double> vector_new;
  //The term at the left hand side represents the "lower_bound", in the middle "sample_mean" and at   
  //the right hand side upper_bound. "  ̃X" is sample mean, "t" is the "t_value" provided in input text file.
  //"S" is sample standard deviation and "n" is the sample size. You need do calculate "  ̃X" and "S" from
  //your sample. The other variables are given in input file.

  double Ransum=0.0;
  double size = 0.0;
   for (int i = 0; i < sample_size; i++){
    Ransum+=random_sample[i];
    size++;
   }
   double x=Ransum/size;//sample mean

  double stda=0.0;//Standart deviation
   for (int i = 0; i < sample_size; i++){
     double one=(random_sample[i]-x)*(random_sample[i]-x);
     stda+=one;
   }
     stda=stda/((sample_size));
     stda=sqrt(stda);
  double squarenN=sqrt(sample_size);
  double  a=x-((t_value*stda)/squarenN);
  vector_new.push_back(a);
  vector_new.push_back(x);
  double c=x+((t_value*stda)/squarenN);
  vector_new.push_back(c);
  return vector_new;
}


vector<double>  NormalDistribution::sample(int sample_size, int seed_value){

   //Create a sample from a Normal Distribution, given the sample size and seed value for
   //random number generator. Return the sample as a vector. You can generate a random number from
   //a Normal Distribution using the code snippet below. You need to repeat this process to create a
   //sample of given size. For more detail check normal_distribution reference.
    vector<double> vector_new;
    default_random_engine generator;
    generator.seed(seed_value);
    normal_distribution<double> distribution(getmean(),getstddev());
for(int i=0;i<sample_size;i++){   
   double number = distribution(generator);
    vector_new.push_back(number);}
    
  return vector_new;
}

const double NormalDistribution::getstddev(){
  return stddev;
}


vector<double>  UniformDistribution::sample(int sample_size, int seed_value){

//Create a sample from a Uniform Distribution, given the sample size and seed value for
//random number generator. Return the sample as a vector. You can generate a random number from
//a Uniform Distribution using the code snippet below. You need to repeat this process to create a
//sample of given sizexs. For more detail check uniform_real_distribution reference.
  vector<double> vector_new;
  std::default_random_engine generator ;
  generator.seed(seed_value) ;
  std::uniform_real_distribution<double>distribution(a,b);

      for(int i=0;i<sample_size;i++){
          double number = distribution(generator);
          vector_new.push_back(number);}
  
  return vector_new;
}




//"sample": Create a sample from a Exponential Distribution, given the sample size and seed value for
//random number generator. Return the sample as a vector. You can generate a random number from
//a Exponential Distribution using the code snippet below. You need to repeat this process to create a
//sample of given size. For more detail check exponential_distribution reference

vector<double>  ExponentialDistribution::sample(int sample_size, int seed_value){

  vector<double> vector_new;
  std::default_random_engine generator;
  generator.seed(seed_value) ;
  std::exponential_distribution < double > distribution ( lambda ) ;
  for(int i=0;i<sample_size;i++){
     double number = distribution ( generator ) ;
     vector_new.push_back(number);}
 
 
return vector_new;

}



