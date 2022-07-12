#pragma once
#include "SFML/Graphics.hpp"
#include "Population.h"
#include "DeltaTime.hpp"
#include "Map.hpp"
class Game
{
public:
	Game(sf::RenderWindow& window);
	~Game();

	void Update();
	void Render();

private:
	float m_frameTime = 0.005f/*0.005f*/;
	float m_deltaT = 0.0f;
	sf::RenderWindow& m_wind;
	Population* popul;
	Map m_map;
	void GetKeyInput();
	short m_KeyInput = 0.f;
};

