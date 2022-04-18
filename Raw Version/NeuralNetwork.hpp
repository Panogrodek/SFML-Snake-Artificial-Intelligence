#pragma once
#include "Layer.hpp"
#include "LayerVisualisation.hpp"
class NeuralNetwork
{
public:
	NeuralNetwork();
	NeuralNetwork(std::vector<int> layers);
	~NeuralNetwork();

	void InitLayers(std::vector<int> layers);
	void Mutate();

	Layer* RunNN();
	std::vector<Layer>* GetLayers() { return &m_layers; };
	void SetLayers(std::vector<Layer> layers) { m_layers = layers; }
	void MergeNetworks(NeuralNetwork* first, NeuralNetwork* other);

	std::vector<Layer> CloneLayers() { return m_layers; };

	void SetFitness(long fitness) { m_fitness = fitness; };
	long GetFitness() { return m_fitness; };

	void InitVisualisation();
	void Draw(sf::RenderWindow& window);
private:
	float m_mutationRate = 2.5f;
	long m_fitness = 0.0f;
	bool m_drawn = false;
	std::vector<Layer> m_layers;
	LayerVisualisation* vis = nullptr;
};

