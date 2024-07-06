  #include <iostream>
  #include <iomanip>
  #include <cmath>


  using namespace std;

  int const MAX = 100;

  double sigmoidFunction(double x){
    return (1/(1 + exp(-x)));
  }

  int generateRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
  }

  struct training_samples{
    int samplesNumber, inputSize, outputSize;
    double inputs[MAX][MAX], outputs[MAX][MAX];
    training_samples();
    training_samples(int samples, int inputs, int outputs);
    ostream& show(ostream& out);
    istream& get(istream& in);
  };

  training_samples::training_samples()
    :samplesNumber(0){
    }

  training_samples::training_samples(
    int sn, int is, int os
  ):samplesNumber(sn), inputSize(is), outputSize(os){

  }

  istream& training_samples::get(istream& in){
    in >> samplesNumber >> inputSize >> outputSize;
    for (int sn = 0; sn < samplesNumber; ++sn){
      for(int is = 0; is < inputSize; ++is){
        in >> inputs[sn][is];
      }
      for(int os = 0; os < outputSize; ++os){
        in >> outputs[sn][os];
      }
    }
    return in;
  }

  ostream& training_samples::show(ostream& out){
    out << "\n TRAINING DATA \n";
    out << "\nNumber of samples: " << samplesNumber;
    out << "\nInputs Size: " << inputSize;
    out << "\nOutputs Size: " << outputSize << "\n\n";

    for (int sn = 0; sn < samplesNumber; ++sn){
      for(int is = 0; is < inputSize; ++is){
        out << " Input [" << inputs[sn][is] << "]\t" ;
      }
      for(int os = 0; os < outputSize; ++os){
        out << " Output [" << outputs[sn][os] << "]\n";
      }
    }
    return out;
  }

  struct backpropagation_neural_network{

    int inputLayerSize, hiddenLayerSize, outputLayerSize;
    double inputLayer[MAX], 
            hiddenLayer[MAX], 
            outputLayer[MAX], 
            initialCluster[MAX][MAX+1], 
            finalCluster[MAX][MAX+1];
    backpropagation_neural_network();
    backpropagation_neural_network(int inputLayerSize, int hiddenLayerSize, int outputLayerSize);

    ostream& show(ostream& out);
    istream& get(istream& in);

    void pass();
    void setRandomWeights();
    int backpropagate(const training_samples& ts, float training_rate, int max_epoch);
    

  };

  backpropagation_neural_network::backpropagation_neural_network()
    :inputLayerSize(0), hiddenLayerSize(0), outputLayerSize(0)
    {}

  backpropagation_neural_network::backpropagation_neural_network(int i, int h, int o)
    :inputLayerSize(i), hiddenLayerSize(h), outputLayerSize(o)
    {}

  istream& backpropagation_neural_network::get(istream& in){

    in >> inputLayerSize >> hiddenLayerSize >> outputLayerSize;

    int initialClusterWeights = inputLayerSize + 1;
    for (int i = 0; i < hiddenLayerSize; ++i){
      for(int w = 0;  w < initialClusterWeights; ++w){
          in >> initialCluster[i][w];
      }
    }

    int finalClusterWeights = hiddenLayerSize + 1;
    for (int i = 0; i < outputLayerSize; ++i){
      for (int w = 0; w < finalClusterWeights; ++w){
        in >> finalCluster[i][w];
      }
    }

    return in;
  }

  ostream& backpropagation_neural_network::show(ostream& out){

      out << "Input Layer \n[";
      for(int i = 0; i < inputLayerSize; ++i){
          out << "\t" << inputLayer[i] ;
      }   
      out << "]\n\n";

      int initialClusterNeuronsWeight = inputLayerSize + 1;
      out << "Initial cluster \n";
      for (int i = 0; i < hiddenLayerSize; ++i){
        for (int weights = 0; weights < initialClusterNeuronsWeight; ++weights){
            out <<"[ "  << initialCluster[i][weights] << "]\t";
        }
        out << "\n";
      }
      out << "\n\n";

      out << "Hidden Layer \n[";
      for (int i = 0; i < hiddenLayerSize; ++i){
          out << setprecision(5) << hiddenLayer[i] << "\t";
      }
      out << "]\n\n";

      int finalClusterNeuronsWeight = hiddenLayerSize + 1;
      out << "Final Cluster \n";
      for (int i = 0; i < outputLayerSize; ++i){
        for (int weights = 0; weights < finalClusterNeuronsWeight; ++weights){
          out <<"[ " << finalCluster[i][weights] << "]\t";
        }
        out<<"\n";
      }
      out <<"\n\n";

      out<<"Output Layer\n[";
      for(int i = 0; i < outputLayerSize; ++i){
        out << setprecision(5) << outputLayer[i] << "\t";
      }
      out << "]\n\n";

    return out;
  }

  void backpropagation_neural_network::pass(){


    for(int i = 0; i < hiddenLayerSize; ++i){ 
      hiddenLayer[i] = initialCluster[i][inputLayerSize];
      for(int weight = 0; weight < inputLayerSize; ++weight){
        hiddenLayer[i] += initialCluster[i][weight]*inputLayer[weight];
      }
      hiddenLayer[i] = sigmoidFunction(hiddenLayer[i]);
    }

    for(int i = 0; i < outputLayerSize; ++i){ 
      outputLayer[i] = finalCluster[i][hiddenLayerSize];
      for(int weight = 0; weight < hiddenLayerSize; ++weight){
        outputLayer[i] += finalCluster[i][weight]*hiddenLayer[weight];
      }
      outputLayer[i] = sigmoidFunction(outputLayer[i]);
    }

  }

  void backpropagation_neural_network::setRandomWeights(){

    int initialClusterNeuronsWeight = inputLayerSize + 1;
    int finalClusterNeuronsWeight = hiddenLayerSize + 1;  

    for(int i = 0; i < hiddenLayerSize; ++i){
      for(int weight = 0; weight < initialClusterNeuronsWeight; ++weight){
        initialCluster[i][weight] = generateRandomNumber(-50,+50)/1000.0;
      }
    }

    for(int i = 0; i < outputLayerSize; ++i){
      for(int weight = 0; weight < finalClusterNeuronsWeight; ++weight){
        finalCluster[i][weight] = generateRandomNumber(-50,+50)/1000.0;
      }
    }

  }

  int backpropagation_neural_network::backpropagate(
    const training_samples& ts, float training_rate, int max_epoch
  ){
    double initialClusterErrors[MAX];
    double finalClusterErrors[MAX];
    //The function have to returns an integer value, so mistakesPerEpoch  is that value;
    //mistakesPerEpoch is working like a counter for each epoch, allowing the program know when stop the backpropagate cycle, because if the mistakes is equal to 0, it means networks learned the concept
    int mistakesPerEpoch;
    for(int epoch = 0; epoch < max_epoch; ++epoch){
      mistakesPerEpoch = 0;
      //mistakesOutputs counters the result errors in the output layer of each sample, that increment the value of mistakesPerEpoch;
      int mistakesPerOutput;
      for (int  ns = 0; ns < ts.samplesNumber; ++ns) {
        for(int iv = 0; iv < inputLayerSize; ++iv){
          inputLayer[iv] = ts.inputs[ns][iv];
        }
        pass();
        
        //Calculate the gross errors of the final cluster.
        for(int ev = 0; ev < outputLayerSize; ++ev){
          finalClusterErrors[ev] = ts.outputs[ns][ev] - outputLayer[ev]; 
          //if the result is greater o equal that 0.5 it is 1.0, but 0.0;
          //Ternary operator
          double result = (outputLayer[ev] >= 0.5) ? 1.0 : 0.0;
          if(result != ts.outputs [ns][ev]){
            ++mistakesPerOutput;
          }
        }

        if(mistakesPerOutput != 0){
          ++mistakesPerEpoch;
        }

        //Estimate the gross errors of the initial cluster
        for(int ev = 0; ev < hiddenLayerSize; ++ev){
          initialClusterErrors[ev] = 0.0;
          for(int nn = 0; nn < outputLayerSize; ++nn){
            initialClusterErrors[ev] += finalClusterErrors[nn]*finalCluster[nn][ev];
          }
        }

        //Calculate the fixed coefficient for each neuron's weights, this coefficient (fixed error) will be saved in the errors arrays created in the previous step.
        //final cluster neurons:
        for(int ae = 0; ae < outputLayerSize; ++ae){
          finalClusterErrors[ae] *= training_rate*(outputLayer[ae]*(1.0 - outputLayer[ae]));
        }
        //initial cluster neurons:
        for(int ae = 0;ae < hiddenLayerSize; ++ae){
          initialClusterErrors[ae]*=training_rate*(hiddenLayer[ae]*(1.0 - hiddenLayer[ae]));
        }

        //fix the neurons weights
        //initial cluster neurons:
        for(int nn = 0; nn < hiddenLayerSize; ++nn){
          for(int weight = 0; weight < inputLayerSize; ++weight){
            initialCluster[nn][weight] += initialClusterErrors[nn]*inputLayer[weight];
          }
            initialCluster[nn][inputLayerSize] += initialClusterErrors[nn];
        }

        //final cluster neurons
        for(int nn = 0; nn < outputLayerSize; ++nn){
          for(int weight = 0; weight < hiddenLayerSize; ++weight){
            finalCluster[nn][weight] += finalClusterErrors[nn]*hiddenLayer[weight];
          }
            finalCluster[nn][hiddenLayerSize] += finalClusterErrors[nn];
        }
        if(mistakesPerEpoch == 0){
          cout << "\nTotal Epochs executed = " << epoch << "\n";
          break;
        }
      }
    }
    cout << "\nTotal Epochs specified in the code = " << max_epoch << "\n";
    return 0;
  }


  int main(){

    training_samples ts;
    ts.get(cin);
    ts.show(cout);
    backpropagation_neural_network bnn (
      ts.inputSize, 3, ts.outputSize
    );
    bnn.setRandomWeights();
    bnn.show(cout);
    int mistakes = bnn.backpropagate(ts,0.5,1000);
    cout << "Mistakes: " << mistakes << "\n\n";
    cout << "Definitive Backpropagate Neural Network \n\n";
    bnn.show(cout);
 
    
  return 0;
  }