#include "stdafx.h"
#include "Snake.hpp"
#include "Math.hpp"
Snake::Snake()
{
	InitBody();
	m_dir = 1;
	InitNewApple();
	m_dir = 0;
}

Snake::~Snake()
{
}

void Snake::InitBody()
{
	//body
	sf::RectangleShape body;
	std::deque<short> directions;
	body.setFillColor(sf::Color::Green);
	body.setSize(sf::Vector2f(SNAKE_WIDTH, SNAKE_HEIGHT));
	body.setPosition(m_offset.x + Math::Get().randomInt(0, MAP_WIDTH-1) * SNAKE_WIDTH, m_offset.y + Math::Get().randomInt(0, MAP_HEIGHT-1) * SNAKE_HEIGHT);
	m_directions.push_back(directions);
	m_body.push_back(body);
	m_body.at(0).setFillColor(sf::Color::Cyan);
	//apple
	m_apple.setFillColor(sf::Color::Red);
	m_apple.setSize(sf::Vector2f(SNAKE_WIDTH, SNAKE_HEIGHT));
}

void Snake::InitNewApple()
{
	m_Score += 1;
	AddBody();
	m_turns += TurnsPerPoint;
	if (m_turns > 500) //500 is the max number of turns a snake can have
		m_turns = 500;

	m_apple.setPosition(m_offset.x + Math::Get().randomInt(0, MAP_WIDTH-1) * SNAKE_WIDTH, m_offset.y + Math::Get().randomInt(0, MAP_HEIGHT-1) * SNAKE_HEIGHT);
	bool posSet = false;
	while (!posSet) {
		posSet = true;
		for (int i = 0; i < m_body.size(); i++) {
			if (std::floor(m_apple.getPosition().x) == std::floor(m_body.at(i).getPosition().x) && std::floor(m_apple.getPosition().y) == std::floor(m_body.at(i).getPosition().y)) {
				m_apple.setPosition(m_offset.x + Math::Get().randomInt(0, MAP_WIDTH - 1) * SNAKE_WIDTH, m_offset.y + Math::Get().randomInt(0, MAP_HEIGHT - 1) * SNAKE_HEIGHT);
				posSet = false;
			}
		}
	}
}

void Snake::AddBody()
{
	sf::RectangleShape body;
	body.setFillColor(sf::Color::Green);
	body.setSize(sf::Vector2f(SNAKE_WIDTH, SNAKE_HEIGHT));
	switch (m_dir) {
	case 1: //left
		body.setPosition(m_body.at(m_body.size()-1).getPosition() + sf::Vector2f(SNAKE_WIDTH,0));
		break;
	case 2: //right
		body.setPosition(m_body.at(m_body.size() - 1).getPosition() + sf::Vector2f(-SNAKE_WIDTH, 0));
		break;
	case 3: //up
		body.setPosition(m_body.at(m_body.size() - 1).getPosition() + sf::Vector2f(0, SNAKE_HEIGHT));
		break;
	case 4: //down
		body.setPosition(m_body.at(m_body.size() - 1).getPosition() + sf::Vector2f(0, -SNAKE_HEIGHT));
		break;
	}	
	std::deque<short> directions;
	m_body.push_back(body);
	directions = m_directions.at(m_directions.size() - 1);
	directions.push_front(m_dir);
	m_directions.push_back(directions);

}

void Snake::CheckIfInBounds()
{
	//collision is here
	if (m_body[0].getPosition().x < m_offset.x || m_body[0].getPosition().x >= m_offset.x + MAP_WIDTH * SNAKE_WIDTH || m_body[0].getPosition().y < m_offset.y || m_body[0].getPosition().y >= m_offset.y + MAP_WIDTH * SNAKE_HEIGHT) {
		m_dead = true;
		m_wallHit = true;
	}
	for (int i = 1; i < m_body.size(); i++) {
		if (m_body[0].getPosition() == m_body.at(i).getPosition())
			m_dead = true;
	}
}

void Snake::Update()
{
	if (m_dir && m_turns > 0) {
		m_turns -= 1;
		m_StepsTaken += 1;
		UpdateMovement();
		if (std::floor(m_apple.getPosition().x) == std::floor(m_body.at(0).getPosition().x) && std::floor(m_apple.getPosition().y) == std::floor(m_body.at(0).getPosition().y)) {
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
	case 1: //left
		if (m_oldDir != 2) 
			m_oldDir = m_dir;
		else
			m_dir = m_oldDir;
		break;
	case 2: //right
		if (m_oldDir != 1) 			
			m_oldDir = m_dir;
		else
			m_dir = m_oldDir;
		break;
	case 3: //up
		if (m_oldDir != 4)
			m_oldDir = m_dir;
		else
			m_dir = m_oldDir;
		break;
	case 4: //down
		if (m_oldDir != 3)
			m_oldDir = m_dir;
		else
			m_dir = m_oldDir;
		break;
	}

	for (int i = 0; i < m_body.size(); i++) {
		m_directions.at(i).push_back(m_dir);
		switch (m_directions.at(i).front()){
		case 1: //left
			m_body[i].move(-1.f * SNAKE_WIDTH, 0.f);
			break;
		case 2: //right
			m_body[i].move(SNAKE_WIDTH, 0.f);
			break;
		case 3: //up
			m_body[i].move(0.f, -1.f * SNAKE_HEIGHT);
			break;
		case 4: //down
			m_body[i].move(0.f, SNAKE_HEIGHT);
			break;
			}
		m_directions.at(i).pop_front();
	}
}

long Snake::GetFitness() 
{
	long val = m_StepsTaken + (std::pow(2, m_Score) + std::pow(m_Score, 2.1) * 500) - (std::pow(m_Score, 1.2) * std::pow((0.25 * m_StepsTaken), 1.3));
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
		tempPos += sf::Vector2f(x * SNAKE_WIDTH, y * SNAKE_HEIGHT);
		while (tempPos.x > m_offset.x - SNAKE_WIDTH && tempPos.x < m_offset.x + MAP_WIDTH * SNAKE_WIDTH && tempPos.y > m_offset.y - SNAKE_HEIGHT && tempPos.y < m_offset.y + MAP_HEIGHT * SNAKE_HEIGHT && !pushed) {
			

			if (sf::Vector2f(tempPos.x, tempPos.y) == m_apple.getPosition() && type == apple) {
				distances.push_back(1.f);
				pushed = true;
			}
			for (auto& b : m_body) {
				if (sf::Vector2f(tempPos.x, tempPos.y) == b.getPosition() && type == body) {
					distances.push_back(1.f);
					pushed = true;
				}
			}
			tempPos += sf::Vector2f(x * SNAKE_WIDTH, y * SNAKE_HEIGHT);
			dist++;
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

