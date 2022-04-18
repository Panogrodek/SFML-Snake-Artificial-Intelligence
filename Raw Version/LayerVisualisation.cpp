#include "stdafx.h"
#include "LayerVisualisation.hpp"
#include "Math.hpp"

/*
This class is the one, responsible for all the neural net you see
on the right side of the screen. 

It has no impact on the Neural Network itself, but helps 
understanding how all of the neurons in each layer are behaving.

*/

LayerVisualisation::LayerVisualisation(std::vector<Layer>& layers) :
	m_layers(layers)
{
	InitLayers();
	BindWeights();
}

LayerVisualisation::~LayerVisualisation()
{
}

void LayerVisualisation::InitLayers()
{
	sf::Vector2f startPos(1260, 0);
	for (int i = 0; i < m_layers.size(); i++) {
		std::vector<sf::CircleShape> vec;
		for (int j = 0; j < m_layers.at(i).GetSize(); j++) {
			sf::CircleShape shape;
			shape.setFillColor(sf::Color::White);
			shape.setRadius(m_radius);
			shape.setPosition(sf::Vector2f(startPos.x + i * 200, startPos.y + 2.5 * j * m_radius));
			vec.push_back(shape);
		}
		m_neurons.push_back(vec);
	}
}

void LayerVisualisation::BindWeights()
{
	for (int i = 1; i < m_layers.size(); i++) {
		for (int j = 0; j < m_layers.at(i).GetSize(); j++) {
			for (int k = 0; k < m_layers.at(i-1).GetSize(); k++) {


				m_lines.push_back(sf::Vertex(sf::Vector2f(
					m_neurons.at(i).at(j).getPosition().x + m_neurons.at(i).at(j).getRadius(),
					m_neurons.at(i).at(j).getPosition().y + m_neurons.at(i).at(j).getRadius())
				));

				m_lines.push_back(sf::Vertex(sf::Vector2f(
					m_neurons.at(i - 1).at(k).getPosition().x + m_neurons.at(i - 1).at(k).getRadius(),
					m_neurons.at(i - 1).at(k).getPosition().y + m_neurons.at(i-1).at(k).getRadius())
				));

			}
		}
	}
}

void LayerVisualisation::UpdateWeights()
{
	int l = 0;
	for (int i = 1; i < m_layers.size(); i++) {
		for (int j = 0; j < m_layers.at(i).GetSize(); j++) {
			for (int k = 0; k < m_layers.at(i-1).GetSize(); k++) {
				m_layers.at(i).GetWeights(i, j);
				sf::Color color;
				if (m_layers.at(i).GetWeights(j, k) > 0) { //red
					color = sf::Color(Math::Get().sigmoid(m_layers.at(i).GetWeights(j, k)) * 255, 0, 0, 255);
				}
				else { //green
					color = sf::Color(0, Math::Get().sigmoid(m_layers.at(i).GetWeights(j, k)) * 255, 0, 255);
				}

				m_lines.at(l).color = color;
				m_lines.at(l + 1).color = color;

				l += 2;
			}
		}
	}

}

void LayerVisualisation::Update()
{
	UpdateValues();
	UpdateWeights();
}

void LayerVisualisation::UpdateValues()
{
	for (int i = 0; i < m_layers.size(); i++) {
		for (int j = 0; j < m_layers.at(i).GetSize(); j++) {
			if (m_layers.at(i).GetValues()->at(j) > 0) {
				//std::cout << i << " " << m_layers.at(i).GetValues()->at(j) << "\n";
				m_neurons.at(i).at(j).setFillColor(sf::Color(191, 255, 0, std::max(80.f, std::min(m_layers.at(i).GetValues()->at(j) * 255.f, 255.f))));
			}
			else
				m_neurons.at(i).at(j).setFillColor(sf::Color(255, 255, 255, 255));
		}
	}
}

void LayerVisualisation::RenderNeurons(sf::RenderWindow& window)
{
	window.draw(m_lines.data(), m_lines.size(), sf::Lines);
	for (int i = 0; i < m_neurons.size(); i++) {
		for (int j = 0; j < m_neurons.at(i).size(); j++) {
			window.draw(m_neurons.at(i).at(j));
		}
	}

}




