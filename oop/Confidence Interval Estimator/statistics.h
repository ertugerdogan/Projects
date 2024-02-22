#ifndef __STATISTICS_H
#define __STATISTICS_H



#include <vector>
using namespace std;
class StatisticalDistribution{//abstract base class ->one or more pure virtual member functions
    private:
        const double mean;
    public:
        const double getmean();
        vector<double> virtual sample(int,int)=0;//You can figure out the return type and parameters looking at given "main.cpp" code.
        vector<double> calculate_confidence_interval(vector<double>,int,double);//
        StatisticalDistribution(double Mean):mean(Mean){};
};


class NormalDistribution : public StatisticalDistribution{
    private:
        const double stddev;//Standard deviation value
    public:
        NormalDistribution(): StatisticalDistribution(0.0),stddev(1.0){};
        vector<double> sample(int,int);
        const double getstddev();
};

class UniformDistribution : public StatisticalDistribution{
    private:
        const double a;
        const double b;
    public:
        UniformDistribution():StatisticalDistribution(0.0),a(-1.0),b(1.0){};
        vector<double> sample(int,int);
};

class ExponentialDistribution : public StatisticalDistribution{
    private:
        const double lambda;
    public:
       ExponentialDistribution():StatisticalDistribution(1.0),lambda(1.0){};//The constructor should initialize "mean" as 1.0 and "lambda" as 1.0.
       vector<double> sample(int,int);
};

#endif