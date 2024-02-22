#ifndef __UTILS_H
#define __UTILS_H

#include "statistics.h"
StatisticalDistribution* choose_function(int);
double many_trials(StatisticalDistribution* , vector<double>,double,int,int,int);


#endif