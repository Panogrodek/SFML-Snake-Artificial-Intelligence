#pragma once
#include "SFML/Graphics.hpp"
class Map
{
public:
	Map();
	~Map();
	
	void Render(sf::RenderWindow& win);
	void SetVariables(int Highscore, float bestFitness, float FitnessSum);
	void SetScore(int score);
private:
	void InitTiles();
	void InitTex();
	void InitText();
	void InitFont();

	sf::RectangleShape m_Ui;
	std::vector<sf::RectangleShape> m_tiles;
	sf::Texture m_tex;
	sf::Font m_font;
	std::vector<sf::Text> m_texts;
	int score;
	int Highscore;
	float bestFitness;
	int gen = 1;
};

