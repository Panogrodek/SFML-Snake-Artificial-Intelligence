#pragma once
#include "SFML/Graphics.hpp"
#include "Snake.hpp"
#include "NeuralNetwork.hpp"
class Population
{
public:
	Population(int size);
	~Population();

	void RenderSnake(sf::RenderWindow& win);
	bool Update();
	void SetKeyInput(int dir) { m_PlayerDir = dir; };
	void NaturalSelection();

	int GetScore();
	long GetBestFitness() { return m_bestFitness; };
	long GetFitnessSum() { return m_fitnessSum; };
	short GetHighScore() { return m_highscore; };
private:
	void InitLayersNum();
	void CalculateSum();
	void CalculateHighscore();
	NeuralNetwork m_bestNN;
	std::vector<Snake*> m_snakes;
	std::vector<NeuralNetwork*> m_NN;

	short m_PlayerDir = 0.f;
	short m_numOfSnakes = 0.f;
	long m_bestFitness = 0.f;
	long m_fitnessSum = 0.f;
	short m_highscore = 0.f;
	std::vector<int> m_layersNum;

	NeuralNetwork* SelectPartner();

	void FindBestNN();
	
};

