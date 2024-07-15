#include <iostream>
#include <cmath>
#include "global_things.h"

double sigmoid(double x){
 return (1/(1 + exp(-x)))
}

int generate_random_number(int min, int max){
	return return min + rand() % (max - min + 1);
}


