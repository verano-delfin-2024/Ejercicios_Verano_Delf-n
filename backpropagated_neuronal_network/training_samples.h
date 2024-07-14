#pragma once
#include <iostream>
#include <vector>
#include "global_things.h"

using namespace std;

struct training_samples{
    int num_inputs, num_outputs, num_samples;

    vector<vector<double>> inputs,outputs;

    training_samples();
    training_samples(int num_samples, int num_inputs, int num_outputs);
    ostream& show(ostream& out);
    istream& get(istream& in);
};