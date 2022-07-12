#include "stdafx.h"
#include "Layer.hpp"
#include "Math.hpp"
/*
This is a class, that represents a single layer
in our Neural Network.

The layer is made in a way, that allows it to be:
-an input layer,
-a hidden layer,
-or an output layer.

The size is the number of neurons, that we want to input in our layer.
If the layer is a hidden layer, or an output layer we need to give it 
previous layer (because of how weights work).
*/
Layer::Layer(int size, Layer* prev) : //here we initialize the layer, and randomize values inside each and every neuron
	m_size(size), m_prevLay(prev)
{
	initVal();
	RandomizeVal();
}

Layer::~Layer()
{
}

void Layer::AddValues(std::vector<float> dist, int begin, int end) //this function allows us to add values to the layer. Only applied in input layers
{
	int j = 0;
	for (int i = begin; i < end; i++){
		m_values[i] = dist.at(j);
		j++;
	}
}

int Layer::GetMaxValue() //here we receive the max value out of all neurons. We only use this func in output layer
{
	float max = m_values.at(0);
	int index = 0;
	for (int i = 0; i < m_values.size(); i++) {
		if (m_values[i] > max) {
			index = i;
			max = m_values[i];
		}
	}
	return index + 1;
}

void Layer::initVal() //we initialize the sizes of biases, weights and values
{
	std::vector<float> v;
	if (m_prevLay != nullptr) {
		for (int i = 0; i < m_prevLay->GetSize(); i++) {
			v.push_back(0);
		}
	}
	for (int i = 0; i < m_size; i++) {
		m_values.push_back(0);
		m_biases.push_back(0);
		m_weights.push_back(v);
	}
}

void Layer::RandomizeVal() //we randomize all of the biases and weights for all neurons
{
	for (int i = 0; i < m_size; i++) {
		m_biases[i] = float(Math::Get().randomFloat(-1.f, 1.f));

		if(m_prevLay != nullptr)
		for (int j = 0; j < m_prevLay->GetSize(); j++) {
			m_weights[i][j] = float(Math::Get().randomFloat(-1.f, 1.f));
		}
	}
}
