#include "stdafx.h"
#include "Population.h"
#include "Math.hpp"
/*
This is where all of the snakes from single generation happen to be.
We control every snake in this class, and every neural network.

I didn't give snakes their neural networks, because I thought it would
be easier, if I just edited neural networks here

*/
Population::Population(int size) //here we check if a player is playing or not, and if player is not playing, we push back desired num of snkaes
{
	m_numOfSnakes = size;
	if (!HumanPlaying) {
		InitLayersNum();
		for (int i = 0; i < size; i++) {
			m_snakes.push_back(new Snake());
			m_NN.push_back(new NeuralNetwork(m_layersNum));
		}
	}
	else {
		m_snakes.push_back(new Snake());
	}
}

void Population::InitLayersNum() //here we have number of neurons we want to initialize in every layer. This setup below was best for me, but you can change it if you want
{
	m_layersNum.push_back(24); //input layer
	m_layersNum.push_back(4); //1st hidden layer
  /*m_layersNum.push_back(6);*/ //2nd hidden layer
	m_layersNum.push_back(4);  //output layer
	m_NN.push_back(new NeuralNetwork(m_layersNum));
}

void Population::CalculateSum() //we need fitness sum later
{
	m_fitnessSum = 0.f;
	for (int i = 0; i < m_numOfSnakes; i++) {
		m_fitnessSum += m_NN[i]->GetFitness();
	}
	std::cout << "Fitness sum: " << m_fitnessSum << "\n";
}

void Population::CalculateHighscore()
{

	for (int i = 0; i < m_numOfSnakes; i++)
	{
		if (m_snakes.at(i)->GetScore() > m_highscore)
		{
			m_highscore = m_snakes.at(i)->GetScore();
		}
	}
}

Population::~Population()
{
	for (auto& s : m_snakes) {
		delete s;
	}
	for (auto& n : m_NN) {
		delete n;
	}
}

bool Population::Update() //we update all LIVING snakes here
{
	bool allDead = true;
	if (HumanPlaying) {
		m_snakes.at(0)->SetDir(m_PlayerDir);
		m_snakes.at(0)->Update();
		if(!m_snakes.at(0)->IsDead())	allDead = false;
	}
	else
		for (int i = 0; i < m_snakes.size(); i++) {
			if (!m_snakes.at(i)->IsDead()) {
				m_NN.at(i)->GetLayers()->at(0).AddValues(m_snakes.at(i)->look(apple), 0, 8);
				m_NN.at(i)->GetLayers()->at(0).AddValues(m_snakes.at(i)->look(wall), 8, 16);
				m_NN.at(i)->GetLayers()->at(0).AddValues(m_snakes.at(i)->look(body), 16, 24);

				//m_NN.at(i)->RunNN();//delete
				m_snakes.at(i)->SetDir(m_NN.at(i)->RunNN()->GetMaxValue());
				m_snakes.at(i)->Update();
				allDead = false;
			}
		}

	return allDead;
}

NeuralNetwork* Population::SelectPartner() //this function selects random snake from generation. The more fitness score snake had, the better it chances of being selected
{
	float rand = Math::Get().randomFloat(0, m_fitnessSum);
	float summation = 0;
	for (int i = 0; i < m_numOfSnakes; i++) {
		summation += m_NN[i]->GetFitness();
		if (summation > rand) {
			return m_NN[i];
		}
	}
	return m_NN[0];
}

void Population::FindBestNN() //we find the best snake, that we will save and give to new generation
{
	long max = 0;
	int Index = 0;

	for (int i = 0; i < m_numOfSnakes; i++)
	{
		if (m_NN[i]->GetFitness() > max)
		{
			max = m_NN[i]->GetFitness();
			Index = i;
		}
	}

	if (max >= m_bestFitness) {
		m_bestNN.SetLayers(m_NN[Index]->CloneLayers());
		m_bestFitness = max;
		std::cout << "Best saved score: " << m_bestFitness << "\n";
	}

	std::cout << "Best fitness: " << max << "\n";

}

void Population::NaturalSelection() //here we calculate score from the generation and we select the best snakes to be parents for next generation
{
	CalculateHighscore();
	for (int i = 0; i < m_snakes.size(); i++) {
		m_NN.at(i)->SetFitness(m_snakes.at(i)->GetFitness());
		delete m_snakes.at(i);
	}
	m_snakes.clear();
	FindBestNN();
	CalculateSum();
	std::vector<NeuralNetwork> children;
	for (int i = 0; i < m_numOfSnakes; i++) { //give birth to new snakes.
		NeuralNetwork childNN;
		childNN.InitLayers(m_layersNum);
		childNN.MergeNetworks(SelectPartner(), SelectPartner());
		childNN.Mutate();
		children.push_back(childNN);
	}
	//clear brains of old gen
	for (int i = 0; i < m_NN.size(); i++) {
		delete m_NN.at(i);
	}
	m_NN.clear();
	//
	for (int i = 0; i < m_numOfSnakes; i++) { //initialize new brains for new generation
		m_NN.push_back(new NeuralNetwork(m_layersNum));
		m_NN[i]->SetLayers(children[i].CloneLayers());
	}
	m_NN[0]->SetLayers(m_bestNN.CloneLayers());

	for (int i = 0; i < m_numOfSnakes; i++) { //give birth to new generation
		m_snakes.push_back(new Snake());
	}
}

int Population::GetScore()
{
	for (int i = 0; i < m_snakes.size(); i++) {
		if (!m_snakes.at(i)->IsDead()) {
			
			return m_snakes.at(i)->GetScore();
		}
	}
	return 0;
}

void Population::RenderSnake(sf::RenderWindow& win)
{
	for (int i = 0; i < m_snakes.size(); i++) {
		if (!m_snakes.at(i)->IsDead()) {
			m_snakes.at(i)->Render(win);
			if(!HumanPlaying)
				m_NN.at(i)->Draw(win);
			break;
		}
	}
}