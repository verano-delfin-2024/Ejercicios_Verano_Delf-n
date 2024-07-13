#include <iostream>
#include "training_samples.h"

using namespace std;


training_samples::training_samples()
    :num_samples(0){}

training_samples::training_samples(
    int samples, int ii, int oo
    )
    :num_samples(samples), inputs_quantity(ii), outputs_quantity(oo){}

istream& training_samples::get(istream& in){
    cin >> num_samples >> inputs_quantity >> outputs_quantity;
    for(int sample = 0; sample < num_samples; ++sample ){
        for(int input = 0; input < inputs_quantity; ++input){
            cin >> inputs[sample][input];
        }
        for(int output = 0;output < outputs_quantity; ++output){
            cin >> outputs[sample][output];
        }
    }
    return in;
}

ostream& training_samples::show(ostream& out){
    cout << "Training set \n\n"
         << "Samples: " << num_samples << '\t'
         << "Inputs: " << inputs_quantity << '\t'
         << "Outputs: " << outputs_quantity << '\n\n';

    for(int sample = 0; sample < num_samples; ++sample ){
        for(int input = 0; input < inputs_quantity; ++input){
            cout << inputs[sample][input] << '\t';
        }
        for(int output = 0;output < outputs_quantity; ++output){
            cout << outputs[sample][output] << '\t';
        }
        cout << '\n';
    }
    return out;
}   