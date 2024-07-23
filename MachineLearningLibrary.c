#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct {
    double* weights;
    double bias;
    double output;
} Neuron;
typedef struct {
    int numNeurons;
    Neuron* neurons;
} Layer;
typedef struct {
    int numInputs;
    int numHidden;
    int numOutputs;
    Layer* hiddenLayer;
    Layer* outputLayer;
} NeuralNetwork;
Neuron* createNeuron(int numInputs) {
    Neuron* neuron = (Neuron*) malloc(sizeof(Neuron));
    neuron->weights = (double*) malloc(numInputs * sizeof(double));
    neuron->bias = 0.0;
    neuron->output = 0.0;
    return neuron;}
Layer* createLayer(int numNeurons, int numInputs) {
    Layer* layer = (Layer*) malloc(sizeof(Layer));
    layer->numNeurons = numNeurons;
    layer->neurons = (Neuron*) malloc(numNeurons * sizeof(Neuron));
    for (int i = 0; i < numNeurons; i++) {
        layer->neurons[i] = *createNeuron(numInputs);}
    return layer;}
NeuralNetwork* createNeuralNetwork(int numInputs, int numHidden, int numOutputs) {
    NeuralNetwork* network = (NeuralNetwork*) malloc(sizeof(NeuralNetwork));
    network->numInputs = numInputs;
    network->numHidden = numHidden;
    network->numOutputs = numOutputs;
    network->hiddenLayer = createLayer(numHidden, numInputs);
    network->outputLayer = createLayer(numOutputs, numHidden);
    return network;}
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));}
void forwardPropagate(NeuralNetwork* network, double* inputs) {
    for (int i = 0; i < network->numHidden; i++) {
        double sum = 0.0;
        for (int j = 0; j < network->numInputs; j++) {
            sum += inputs[j] * network->hiddenLayer->neurons[i].weights[j];}
        sum += network->hiddenLayer->neurons[i].bias;
        network->hiddenLayer->neurons[i].output = sigmoid(sum);}
    for (int i = 0; i < network->numOutputs; i++) {
        double sum = 0.0;
        for (int j = 0; j < network->numHidden; j++) {
            sum += network->hiddenLayer->neurons[j].output * network->outputLayer->neurons[i].weights[j];}
        sum += network->outputLayer->neurons[i].bias;
        network->outputLayer->neurons[i].output = sigmoid(sum);}}
void train(NeuralNetwork* network, double* inputs, double* targets) {
    forwardPropagate(network, inputs);
    double* outputErrors = (double*) malloc(network->numOutputs * sizeof(double));
    for (int i = 0; i < network->numOutputs; i++) {
        outputErrors[i] = targets[i] - network->outputLayer->neurons[i].output;}
    for (int i = 0; i < network->numHidden; i++) {
        double error = 0.0;
        for (int j = 0; j < network->numOutputs; j++) {
            error += outputErrors[j] * network->outputLayer->neurons[j].weights[i];}
        error *= network->hiddenLayer->neurons[i].output * (1 - network->hiddenLayer->neurons[i].output);
        for (int j = 0; j < network->numInputs; j++) {
            network->hiddenLayer->neurons[i].weights[j] += 0.1 * error * inputs[j];}
        network->hiddenLayer->neurons[i].bias += 0.1 * error;}
    for (int i = 0; i < network->numOutputs;i++) {
        for (int j = 0; j < network->numHidden; j++) {
            network->outputLayer->neurons[i].weights[j] += 0.1 * outputErrors[i] * network->hiddenLayer->neurons[j].output;}
        network->outputLayer->neurons[i].bias += 0.1 * outputErrors[i];}}
void freeNeuralNetwork(NeuralNetwork* network) {
    free(network->hiddenLayer->neurons);
    free(network->hiddenLayer);
    free(network->outputLayer->neurons);
    free(network->outputLayer);
    free(network);}
int main() {
    NeuralNetwork* network = createNeuralNetwork(2, 4, 1);
    double inputs[] = {0.0, 0.5};
    double targets[] = {0.0};
    for (int i = 0; i < 10000; i++) {
        train(network, inputs, targets);}
    forwardPropagate(network, inputs);
    printf("Output: %f\n", network->outputLayer->neurons[0].output);
    freeNeuralNetwork(network);
    return 0;}
