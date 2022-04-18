#include "stdafx.h"
#include "Game.hpp"

Game::Game(sf::RenderWindow& window) :
	m_wind(window)
{
	popul = new Population(1000);
}

Game::~Game()
{
}

void Game::Update()
{
	m_deltaT += DeltaTime::Get().GetDeltaTime();
	if (m_deltaT > m_frameTime) {
		m_deltaT = 0.f;

		if (HumanPlaying)
			popul->SetKeyInput(GetKeyInput());

		if (popul->Update()) {
			popul->NaturalSelection();
		}
	}
}

void Game::Render()
{
	popul->RenderSnake(m_wind);
}

int Game::GetKeyInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		return 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		return 2;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		return 3;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		return 4;
}