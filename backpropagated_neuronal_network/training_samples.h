#pragma once
#include <iostream>
#include "global_things.h"

using namespace std;

struct training_samples{
    int inputs_quantity, outputs_quantity, num_samples;
    double inputs[MAX][MAX+1], outputs[MAX][MAX+1];
    training_samples();
    training_samples(int num_samples, int inputs, int outputs);
    ostream& show(ostream& out);
    istream& get(istream& in);
};