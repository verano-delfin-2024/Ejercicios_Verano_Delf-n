#pragma once
#include <iostream>
#include "training_samples.h"
#include "global_things.h"

struct bnn{
	
	int input_layer_size, hidden_layer_size, output_layer_size;
	vector<double> input_layer, hidden_layer, output_layer;
	vector<vector<double>>initial_cluster, final_cluster;

	bnn();
	

}

