#pragma once
#include "Layer.hpp"
class LayerVisualisation
{
public:
	LayerVisualisation(std::vector<Layer>& layers);
	~LayerVisualisation();

	void RenderNeurons(sf::RenderWindow& window);
	void Update();
private:
	void InitLayers();
	void BindWeights();

	void UpdateValues();
	void UpdateWeights();
	std::vector<std::vector<sf::CircleShape>> m_neurons;
	std::vector<sf::Vertex> m_lines;

	std::vector<Layer>& m_layers;

	float m_radius = 15.f;
};

