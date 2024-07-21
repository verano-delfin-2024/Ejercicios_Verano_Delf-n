#pragma once
#include <iostream>
#include "training_samples.h"
#include <vector>
#include "global_things.h"


struct bnn{	
	int input_layer_size, hidden_layer_size, output_layer_size;
	std::vector<double> input_layer, hidden_layer, output_layer;
	std::vector<std::vector<double>>initial_cluster, final_cluster;
	bnn();
	bnn(int input_layer_size, int hidden_layer_size, int output_layer_size);
	std::ostream& show(ostream& out);
	std::istream& get(istream& in);
	void resize_vectors();
	void pass();
	void set_random_weights();
	int backpropagate(const training_samples& ts, double training_rate, int max_epoch);	
};

