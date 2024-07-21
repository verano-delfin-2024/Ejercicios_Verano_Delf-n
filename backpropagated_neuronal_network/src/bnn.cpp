#include <iostream>
#include <iomanip>
#include <vector>
#include "../include/bnn.h"
#include "../include/global_things.h"

using namespace std;

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
		mistakes_per_epoch = 0;
		int mistakes_per_output;
		for(int sample = 0; sample < ts.num_samples; ++sample){
			for(int input = 0; input < ts.num_inputs; ++input){
				input_layer[input] = ts.inputs[sample][input];
			}
			pass();
			//Estimate final cluster's errors
			for(int diff = 0; diff < ts.num_outputs; ++diff){
				final_cluster_errors[diff] = ts.outputs[sample][diff] - output_layer[diff];
				
				double validator = (output_layer[diff] < 0.5) ? 0.0 : 1.0; 
				if(validator != ts.outputs[sample][diff]){
					++mistakes_per_output;
				}
			}

			if(mistakes_per_output != 0){
				++mistakes_per_epoch;
			}

			//Estimate initial cluster errors
			for(int w = 0; w < hidden_layer_size; ++w){
				initial_cluster_errors[neuron_number] = 0.0;
				for(int neuron_number = 0; neuron_number < output_layer_size; ++neuron_number){
					initial_cluster_errors[neuron_number] += final_cluster[neuron_number][w]*output_layer[neuron_number];
				}
			}

			//Estimate correction coefficients per each cluster

			//Initial cluster
			for(int icc_coefficient = 0; ic_ccoefficient < hidden_layer_size; ++icc_coefficient){
				initial_cluster_errors[icc_coefficient] *= learning_rate * hidden_layer[icc_coefficient]*(1.0 - hidden_layer[icc_coefficient]);
			}

			//Final cluster
			for(int fcc_coefficient = 0; fcc_coefficient < output_layer_size; ++fcc_coefficient){
				final_cluster_errors[fcc_coefficient] *= learning_rate * output_layer[fcc_coefficient]*(1.0 - output_layer[fcc_coefficient]);
			}

			//set neuron's weights

			//initial cluster
			for(int ic_neuron = 0; ic_neuron < hidden_layer_size; ++ic_neuron){
				for(int weight = 0; weight < input_layer_size; ++weight){
					initial_cluster[ic_neuron][weight] += initial_cluster_errors[ic_neuron]*input_layer[weight];
				}
				initial_cluster[ic_neuron][input_layer_size] += initial_cluster_errors[ic_neuron];
			}

			//final cluster
			for(int fc_neuron = 0; fc_neuron < output_layer_size; ++fc_neuron){
				for(int weight = 0; weight < hidden_layer_size; ++weight){
					final_cluster[fc_neuron][weight] += final_cluster_errors[fc_neuron]*hidden_layer[weight];
				}
				final_cluster[fc_neuron][hidden_layer_size] += final_cluster_errors[fc_neuron];
			}

		}
		if(mistakes_per_epoch == 0){
			break;
		}
	}
	return mistakes_per_epoch;

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

	cout << "\ninput layer \n";
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





