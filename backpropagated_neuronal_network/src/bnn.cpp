#include <iostream>
#include <iomanip>
#include <vector>
#include "../include/bnn.h"
#include "../include/global_things.h"


bnn::bnn()
	:input_layer_size(0), hidden_layer_size(0), output_layer_size(0){}

bnn::bnn(int input_layer_size, int hidden_layer_size, int output_layer_size)
	:input_layer_size(input_layer_size), 
	hidden_layer_size(hidden_layer_size),
	output_layer_size(output_layer_size){}

void bnn::resize_vectors(){
	input_layer.resize(input_layer_size);
	hidden_layer.resize(hidden_layer_size);
	output_layer.resize(output_layer_size);
	initial_cluster.resize(hidden_layer_size, vector<double>(input_layer_size + 1));
	final_cluster.resize(output_layer_size, vector<double>(hidden_layer_size + 1));
}

void bnn::set_random_weights(){
	 for(int i=0; i < hidden_layer_size; ++i){
	 	for(int w=0; w <= input_layer_size; ++w){
	 		initial_cluster[i][w] = generate_random_number(-50, 50) / 1000.0;
	 	}
	 }

	 for(int i=0; i < output_layer_size; ++i){
	 	for(int w=0; w <= hidden_layer_size; ++w){
	 		final_cluster[i][w] = generate_random_number(-50, 50) / 1000.0;
	 	}
	 }
}

void bnn::pass(){

	for(int i = 0; i < hidden_layer_size; ++i){
		hidden_layer[i] = initial_cluster[i][input_layer_size];
		for(int w = 0; w < input_layer_size; ++w){
			hidden_layer[i] += input_layer[w]*initial_cluster[i][w];
		}
		hidden_layer[i] = sigmoid(hidden_layer[i]);
	}

	for(int i = 0; i < output_layer_size; ++i){
		output_layer[i] = final_cluster[i][hidden_layer_size];
		for(int w = 0; w < hidden_layer_size; ++w){
			output_layer[i] += hidden_layer[w]*final_cluster[i][w];
		}
		output_layer[i] = sigmoid(output_layer[i]);
	}	
};

int bnn::backpropagate(
	const training_samples& ts, 
	float learning_rate, 
	int max_epoch
	){

	vector<double> initial_cluster_errors, final_cluster_errors;

	initial_cluster_errors.resize(hidden_layer_size);
	final_cluster_errors.resize(output_layer_size);

	int mistakes_per_epoch;

	for(int epoch = 0; epoch < max_epoch; ++epoch){
		
	}

}

istream& bnn::get(istream& in){
	cin >> input_layer_size >> hidden_layer_size >> output_layer_size;

	resize_vectors();

	for(int i=0; i < input_layer_size;++i){
		cin >> input_layer[i];
	}

	for(int i = 0; i < hidden_layer_size; ++i){
		for(int w = 0; w <= input_layer_size; ++w){
			cin >> initial_cluster[i][w];
		}
	}

	for(int i=0; i < hidden_layer_size;++i){
		cin >> hidden_layer[i];
	}


	for(int i=0; i  < output_layer_size; ++i){
		for(int w = 0; w <= hidden_layer_size; ++w){
			cin >> final_cluster[i][w];
		}
	}

	for(int i=0; i < output_layer_size; ++i){
		cin >> output_layer[i];
	}

	return in;
};

ostream& bnn::show(ostream& out){

	cout << "input layer \n";
	for(int i=0; i < input_layer_size; ++i){
		cout << '[' << input_layer[i]<< "] \t";
	}



	cout << "\n initial cluster \n";
	for(int i=0; i < hidden_layer_size; ++i){
		for(int j=0; j <= input_layer_size; ++j){
			cout << '[' << initial_cluster[i][j] << "]\t";
		}
		cout << "\n";
	}

	cout << "\n hidden layer \n";
	for(int i=0; i < hidden_layer_size; ++i ){
		cout << '[' << hidden_layer[i]<< "] \t";
	}

	cout << "\n final cluster \n";
	for(int i=0; i < output_layer_size; ++i){
		for(int j = 0; j <= hidden_layer_size; ++j){
			cout << '[' << final_cluster[i][j] << "]\t";
		}
		cout << "\n";
	}

	cout << "\n output layer \n";
	for(int i=0; i < output_layer_size; ++i){
		cout << '[' <<  output_layer[i]<<"]\t";
	}
	return out;
};





