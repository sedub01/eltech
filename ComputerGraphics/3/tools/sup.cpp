// support class cpp file

#include <cmath>

#include "../include/sup.h"

int rightRound(double num){
    return (int)(num<0?num-0.5:num+0.5);
}

double deg2rad(double a){
   return (M_PI*a) / 180.0;
}
