#pragma once
#include <iostream>
#include <vector>
#include "global_things.h"


struct training_samples{
    int num_inputs, num_outputs, num_samples;
    std::vector<vector<double>> inputs,outputs;
    training_samples();
    training_samples(int num_samples, int num_inputs, int num_outputs);
    std::ostream& show(ostream& out);
    std::istream& get(istream& in);
};