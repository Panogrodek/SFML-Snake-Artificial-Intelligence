#include "stdafx.h"
#include "Map.hpp"
#include <sstream>
Map::Map()
{
	InitTiles();
	InitTex();
	InitText();
}

Map::~Map()
{
}

void Map::Render(sf::RenderWindow& win)
{
	win.draw(m_Ui);
	for (auto& t : m_tiles) {
		win.draw(t);
	}
	for (auto& t : m_texts) {
		win.draw(t);
	}
}

void Map::SetScore(int score)
{
	std::stringstream ss;
	ss << "Score: " << score;
	m_texts.at(2).setString(ss.str());
}

void Map::SetVariables(int Highscore, float bestFitness, float FitnessSum)
{
	std::stringstream ss;
	ss << "Highscore: " << Highscore;
	m_texts.at(3).setString(ss.str());
	ss.str("");
	ss << "Best Fitness: " << bestFitness;
	m_texts.at(4).setString(ss.str());
	ss.str("");
	ss << "Fitness sum: " << FitnessSum;
	m_texts.at(5).setString(ss.str());
	ss.str("");
	gen++;
	ss << "Generation: " << gen;
	m_texts.at(0).setString(ss.str());
}

void Map::InitTiles()
{
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			sf::RectangleShape tile;
			(x+y) % 2 == 1 ? tile.setFillColor(sf::Color(20, 87, 32,255)) : tile.setFillColor(sf::Color(9, 135, 32,255));
			
			tile.setOutlineColor(sf::Color::White);
			tile.setOutlineThickness(1.f);
			tile.setSize(sf::Vector2f(SNAKE_WIDTH, SNAKE_HEIGHT));
			tile.setPosition(0.43f * WINDOW_WIDTH - MAP_WIDTH * 0.5f * SNAKE_WIDTH + x * SNAKE_WIDTH, 0.5f * WINDOW_HEIGHT - MAP_HEIGHT * 0.5f * SNAKE_HEIGHT + y * SNAKE_HEIGHT);
			m_tiles.push_back(tile);
		}
	}
}

void Map::InitTex()
{
	if (!m_tex.loadFromFile("res/UI.png")) {
		std::cout << "Could not load texture for UI!\n";
	}
	m_Ui.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	m_Ui.setTexture(&m_tex);
	m_Ui.setPosition(0, 0);
}

void Map::InitText()
{
	InitFont();
	sf::Text Gen;
	Gen.setFont(m_font);
	Gen.setCharacterSize(36.f);
	Gen.setString("Generation: 1");
	Gen.setPosition(0.12f * WINDOW_WIDTH - (Gen.getGlobalBounds().width * 0.5f), 0.2f * WINDOW_HEIGHT);
	Gen.setOutlineColor(sf::Color::Black);
	Gen.setOutlineThickness(3.f);
	m_texts.push_back(Gen);

	sf::Text Mutation;
	Mutation.setFont(m_font);
	Mutation.setCharacterSize(28.f);
	std::stringstream ss;
	ss << "Mutation Rate: " << MutationRate;
	Mutation.setString(ss.str());
	Mutation.setPosition(0.12f * WINDOW_WIDTH - (Gen.getGlobalBounds().width * 0.5f), 0.3f * WINDOW_HEIGHT);
	Mutation.setOutlineColor(sf::Color::Black);
	Mutation.setOutlineThickness(3.f);
	m_texts.push_back(Mutation);

	sf::Text Score;
	Score.setFont(m_font);
	Score.setCharacterSize(32.f);
	Score.setString("Score: 0");
	Score.setPosition(0.12f * WINDOW_WIDTH - (Gen.getGlobalBounds().width * 0.5f), 0.35f * WINDOW_HEIGHT);
	Score.setOutlineColor(sf::Color::Black);
	Score.setOutlineThickness(3.f);
	m_texts.push_back(Score);

	sf::Text Highscore;
	Highscore.setFont(m_font);
	Highscore.setCharacterSize(32.f);
	Highscore.setString("Highscore: 0");
	Highscore.setPosition(0.12f * WINDOW_WIDTH - (Gen.getGlobalBounds().width * 0.5f), 0.405f * WINDOW_HEIGHT);
	Highscore.setOutlineColor(sf::Color::Black);
	Highscore.setOutlineThickness(3.f);
	m_texts.push_back(Highscore);

	sf::Text BestFitness;
	BestFitness.setFont(m_font);
	BestFitness.setCharacterSize(16.f);
	BestFitness.setString("Best Fitness: 0");
	BestFitness.setPosition(0.12f * WINDOW_WIDTH - (Gen.getGlobalBounds().width * 0.5f), 0.455f * WINDOW_HEIGHT);
	BestFitness.setOutlineColor(sf::Color::Black);
	BestFitness.setOutlineThickness(3.f);
	m_texts.push_back(BestFitness);

	sf::Text FitnessSum;
	FitnessSum.setFont(m_font);
	FitnessSum.setCharacterSize(16.f);
	FitnessSum.setString("Fitness sum: 0");
	FitnessSum.setPosition(0.12f * WINDOW_WIDTH - (Gen.getGlobalBounds().width * 0.5f), 0.485f * WINDOW_HEIGHT);
	FitnessSum.setOutlineColor(sf::Color::Black);
	FitnessSum.setOutlineThickness(3.f);
	m_texts.push_back(FitnessSum);
}

void Map::InitFont()
{
	if (!m_font.loadFromFile("res/Pixeled.ttf")) {
		std::cout << "Could not load Font for UI!\n";
	}
}
