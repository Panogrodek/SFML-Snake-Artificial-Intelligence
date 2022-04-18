#pragma once
#include "SFML/Graphics.hpp"
#include "stdafx.h"
#include "DeltaTime.hpp"
#include "Game.hpp"
class Application
{
public:
	Application();
	~Application();

	void Run();
private:

	void Init();
	Game m_game;
	void InitWindow();

	virtual void Update();
	virtual void Render();
	virtual void PollEvents();

	sf::RenderWindow m_window;
};

