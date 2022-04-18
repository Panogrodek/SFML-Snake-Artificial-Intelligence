#include "stdafx.h"
#include "Snake.hpp"
#include "Math.hpp"
Snake::Snake()
{
	InitBody();
	InitNewApple();
}

Snake::~Snake()
{
}

void Snake::InitBody()
{
	//body
	sf::RectangleShape body;
	body.setFillColor(sf::Color::Green);
	body.setSize(sf::Vector2f(SNAKE_WIDTH, SNAKE_HEIGHT));
	body.setPosition(Math::Get().randomInt(0, MAP_WIDTH-1) * SNAKE_WIDTH, Math::Get().randomInt(0, MAP_HEIGHT-1) * SNAKE_HEIGHT);
	m_body.push_back(body);
	//apple
	m_apple.setFillColor(sf::Color::Red);
	m_apple.setSize(sf::Vector2f(SNAKE_WIDTH, SNAKE_HEIGHT));
}

void Snake::InitNewApple()
{
	m_Score += 1;
	m_apple.setPosition(Math::Get().randomInt(0, MAP_WIDTH-1) * SNAKE_WIDTH, Math::Get().randomInt(0, MAP_HEIGHT-1) * SNAKE_HEIGHT);
	m_turns += TurnsPerPoint;
	if (m_turns > 500) //500 is the max number of turns a snake can have
		m_turns = 500;

}

void Snake::CheckIfInBounds()
{
	//collision is here
	if (m_body[0].getPosition().x < 0 || m_body[0].getPosition().x >= MAP_WIDTH * SNAKE_WIDTH || m_body[0].getPosition().y < 0 || m_body[0].getPosition().y >= MAP_WIDTH * SNAKE_HEIGHT) {
		m_dead = true;
		m_wallHit = true;
	}
}

void Snake::Update()
{
	if (m_dir && m_turns > 0) {
		m_turns -= 1;
		m_StepsTaken += 1;
		UpdateMovement();
		if (m_body[0].getPosition() == m_apple.getPosition()) {
			InitNewApple();
		}
		CheckIfInBounds();
	}
	else if(m_turns == 0)
		m_dead = true;
}

void Snake::UpdateMovement()
{
	switch (m_dir) {
	case 1:
		if (m_oldDir != 2) {
			m_body[0].move(-1.f * SNAKE_WIDTH, 0.f);
			m_oldDir = m_dir;
		}
		else
			m_body[0].move(SNAKE_WIDTH, 0.f);
		break;
	case 2:
		if (m_oldDir != 1) {
			m_body[0].move(SNAKE_WIDTH, 0.f);
			m_oldDir = m_dir;
		}
		else
			m_body[0].move(-1.f * SNAKE_WIDTH, 0.f);
		break;
	case 3:
		if (m_oldDir != 4) {
			m_body[0].move(0.f, -1.f * SNAKE_HEIGHT);
			m_oldDir = m_dir;
		}
		else
			m_body[0].move(0.f, SNAKE_HEIGHT);
		break;
	case 4:
		if (m_oldDir != 3) {
			m_body[0].move(0.f, SNAKE_HEIGHT);
			m_oldDir = m_dir;
		}
		else
			m_body[0].move(0.f,-1.f * SNAKE_HEIGHT);
		break;
	}
}

long Snake::GetFitness() 
{
	int val = m_StepsTaken + (std::pow(2, m_Score) + std::pow(m_Score, 2.1) * 500) - (std::pow(m_Score, 1.2) * std::pow((0.25 * m_StepsTaken), 1.3));
	if (m_wallHit)
		val *= 0.1;
	if (val < 0)
		return 0;
	else
		return val;
}

std::vector<float> Snake::look(float type) //this function checks in all 8 directions for the desired type: wall or apple. It returns distance in all 8 directions to desired type
{
	std::vector<float> distances;
	sf::Vector2f startPos = m_body[0].getPosition();
	int x = -2, y = -1;
	for (int i = 0; i < 8; i++) {
		bool pushed = false;
		sf::Vector2f tempPos = startPos;
		x += 1;
		if (x > 1) {
			y += 1;
			x = -1;
		}
		if (x == 0 && y == 0) {
			x += 1;
		}
		float dist = 1;

		while (tempPos.x + x * SNAKE_WIDTH > -SNAKE_WIDTH && tempPos.x + x * SNAKE_WIDTH < MAP_WIDTH * SNAKE_WIDTH && tempPos.y + y * SNAKE_HEIGHT > -SNAKE_HEIGHT && tempPos.y + y * SNAKE_HEIGHT < MAP_HEIGHT * SNAKE_HEIGHT && !pushed) {
			dist++;

			if (sf::Vector2f(tempPos.x + x * SNAKE_WIDTH, tempPos.y + y * SNAKE_HEIGHT) == m_apple.getPosition() && type == apple) {
	
				/*distances.push_back(dist);*/
				distances.push_back(1.f);
				pushed = true;
			}
			tempPos += sf::Vector2f(x * SNAKE_WIDTH, y * SNAKE_HEIGHT);
		}
		
		if (!pushed) {
			if (type == wall)
				distances.push_back(float(1/(dist)));
			else
				distances.push_back(0);
		}

	}
	//int j = 1;
	//for (auto i : distances) {
	//	std::cout << "POSITION: " <<j << " " << i << "\n";
	//	j++;
	//}
	return distances;
}

void Snake::Render(sf::RenderWindow& window)
{
	for (auto& b : m_body) {
		window.draw(b);
	}
	window.draw(m_apple);
}

