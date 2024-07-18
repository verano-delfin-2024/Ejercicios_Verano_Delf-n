#include <iostream>
#include "../include/training_samples.h"




training_samples::training_samples()
    :num_samples(0){}

training_samples::training_samples(
    int num_samples, int num_inputs, int num_outputs
    )
    :num_samples(num_samples), num_inputs(num_inputs), num_outputs(num_outputs)
    {}

istream& training_samples::get(istream& in){

    cin >> num_samples >> num_inputs >> num_outputs;
    inputs.resize(num_samples, vector<double>(num_inputs));
    outputs.resize(num_samples, vector<double>(num_outputs));
    for(int sample = 0; sample < num_samples; ++sample ){
        for(int input = 0; input < num_inputs; ++input){
            cin >> inputs[sample][input];
        }
        for(int output = 0;output < num_outputs; ++output){
            cin >> outputs[sample][output];
        }
    }
    return in;
}

ostream& training_samples::show(ostream& out){
    cout << "Training set \n"
         << "Samples: " << num_samples << '\t'
         << "Inputs: " << num_inputs << '\t'
         << "Outputs: " << num_outputs << '\n'
         ;

    for(int sample = 0; sample < num_samples; ++sample ){
        for(int input = 0; input < num_inputs; ++input){
            cout << inputs.at(sample).at(input) << '\t';
        }
        for(int output = 0;output < num_outputs; ++output){
            cout << outputs.at(sample).at(output) << '\t';
        }
        cout << '\n';
    }
    return out;
}   