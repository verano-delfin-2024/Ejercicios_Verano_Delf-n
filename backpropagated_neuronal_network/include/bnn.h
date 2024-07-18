#pragma once
#include <iostream>
#include "training_samples.h"
#include <vector>
//#include "global_things.h"

using namespace std; //*

struct bnn{	
	int input_layer_size, hidden_layer_size, output_layer_size;
	vector<double> input_layer, hidden_layer, output_layer;
	vector<vector<double>>initial_cluster, final_cluster;
	bnn();
	bnn(int input_layer_size, int hidden_layer_size, int output_layer_size);
	ostream& show(ostream& out);
	istream& get(istream& in);
	void resize_vectors();
	void pass();
	void set_random_weights();
	int backpropagate(const training_samples& ts, float training_rate, int max_epoch);	
};

