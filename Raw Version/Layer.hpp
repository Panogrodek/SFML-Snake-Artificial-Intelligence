#pragma once
#include "SFML/Graphics.hpp"
class Layer
{
public:
	Layer(int m_size, Layer* prev);
	~Layer();

	Layer* GetPrev() { return m_prevLay; };
	int GetSize() { return m_size; };

	std::vector<float>* GetValues() { return &m_values; };
	std::vector<float>* GetBiases() { return &m_biases; };
	float GetWeights(int i_ind, int j_ind) { return m_weights[i_ind][j_ind]; };

	void SetWeights(int i_ind, int j_ind, float value) { m_weights.at(i_ind).at(j_ind) = value; };
	void AddValues(std::vector<float> dist, int begin, int end);

	int GetMaxValue();

private:
	void initVal();
	void RandomizeVal();
	Layer* m_prevLay = nullptr;
	int m_size = 0;

	//all of these things are seperate for each neuron
	std::vector<float> m_values;
	std::vector<std::vector<float>> m_weights;
	std::vector<float> m_biases;
};

