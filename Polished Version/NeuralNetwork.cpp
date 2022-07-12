#include "stdafx.h"
#include "NeuralNetwork.hpp"
#include "Math.hpp"

/*

This is the brain of a snake. Here we can find all layers, and
here we update these layers.

This class is responsible for all of the decisions our snakes make.
Here is also when all of the AI is taken place.

*/
NeuralNetwork::NeuralNetwork()
{

}

NeuralNetwork::NeuralNetwork(std::vector<int> layers)
{
	InitLayers(layers);

}

NeuralNetwork::~NeuralNetwork()
{
	delete vis;
}

void NeuralNetwork::InitLayers(std::vector<int> layers) //our network initializes all of the layers that it was designed to have
{
	m_layers.push_back(Layer(layers.at(0), nullptr));
	for (int i = 1; i < layers.size(); i++) {
		m_layers.push_back(Layer(layers.at(i), &m_layers.at(i - 1)));
	}
}

void NeuralNetwork::InitVisualisation()
{
	vis = new LayerVisualisation(m_layers);
}

/*
when we are done with our network, we randomize some of its biasesand weights
in order to have different children, and not multiply parents infinitely;
*/

void NeuralNetwork::Mutate(){
	for (int i = 0; i < m_layers.size(); i++) {


		for (int j = 0; j < m_layers.at(i).GetSize(); j++) {
			if (m_mutationRate > Math::Get().randomFloat(1.f, 100.f)) {
				m_layers.at(i).GetBiases()->at(j) = Math::Get().randomFloat(-1.0f, 1.0f);
			}
			if (i > 0) {
				for (int k = 0; k < m_layers.at(i-1).GetSize(); k++) {
					if (m_mutationRate > Math::Get().randomFloat(1, 100)) {
						m_layers.at(i).SetWeights(j, k, Math::Get().randomFloat(-1.0f, 1.0f));
					}
				}
			}
			else
				continue;
			
		}
	}
}

//here we pass values from input layer, to output layer. We add according biases and multiply by according weights of each and every neuron. 
Layer* NeuralNetwork::RunNN()
{
	for (int k = 1; k < m_layers.size(); k++) {

		for (int i = 0; i < m_layers[k].GetSize(); i++) {
			m_layers[k].GetValues()->at(i) = m_layers[k].GetBiases()->at(i);
			for (int j = 0; j < m_layers[k-1].GetSize(); j++) {
				m_layers[k].GetValues()->at(i) += m_layers[k-1].GetValues()->at(j) * m_layers[k].GetWeights(i, j);
			}

			m_layers[k].GetValues()->at(i) = Math::Get().sigmoid(m_layers[k].GetValues()->at(i));
		}
	}
	if(m_drawn)
		vis->Update();
	return &m_layers.at(m_layers.size() - 1);
}

//here we cross all of the biases and weights of two Networks in order to create new, based on the previous parents
void NeuralNetwork::MergeNetworks(NeuralNetwork* first, NeuralNetwork* other)
{
	for (int i = 0; i < m_layers.size(); i++) {
		for (int j = 0; j < m_layers.at(i).GetSize(); j++) {
			
			/*i % 2 == 0*/ Math::Get().randomInt(0, 1) ? m_layers.at(i).GetBiases()->at(j) = first->GetLayers()->at(i).GetBiases()->at(j) : m_layers.at(i).GetBiases()->at(j) = other->GetLayers()->at(i).GetBiases()->at(j);

			if (i > 0) {
				for (int k = 0; k < m_layers.at(i - 1).GetSize(); k++) {
					/*i % 2 == 0*/ Math::Get().randomInt(0,1) ? m_layers.at(i).SetWeights(j, k, first->GetLayers()->at(i).GetWeights(j,k)) : m_layers.at(i).SetWeights(j, k, other->GetLayers()->at(i).GetWeights(j, k));
				}
			}
			else
				continue;
		}
	}
}

void NeuralNetwork::Draw(sf::RenderWindow& window)
{
	if (!m_drawn) {
		InitVisualisation();
		m_drawn = true;
	}
	vis->RenderNeurons(window);
}
