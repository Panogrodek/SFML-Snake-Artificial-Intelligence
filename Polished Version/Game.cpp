#include "stdafx.h"
#include "Game.hpp"

Game::Game(sf::RenderWindow& window) :
	m_wind(window)
{
	popul = new Population(2000);
}

Game::~Game()
{
}

void Game::Update()
{
	m_deltaT += DeltaTime::Get().GetDeltaTime();
	if (HumanPlaying)
		GetKeyInput();
	if (m_deltaT > m_frameTime) {
		m_deltaT = 0.f;

		if (HumanPlaying)
			popul->SetKeyInput(m_KeyInput);

		if (popul->Update()) {
			if (!HumanPlaying) {
				popul->NaturalSelection();
				m_map.SetVariables(popul->GetHighScore(),popul->GetBestFitness(),popul->GetFitnessSum());
			}
			else {
				delete popul;
				popul = new Population(1);
			}
		}

		m_map.SetScore(popul->GetScore());
	}
}

void Game::Render()
{
	m_map.Render(m_wind);
	popul->RenderSnake(m_wind);
}

void Game::GetKeyInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_KeyInput = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_KeyInput = 2;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		m_KeyInput = 3;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		m_KeyInput = 4;
}