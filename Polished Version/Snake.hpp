#pragma once
#include "SFML/Graphics.hpp"

constexpr unsigned int TurnsPerPoint = 100;
constexpr unsigned int StartTurns = 200;

enum type { apple = 1, wall = 2, body = 3 };

class Snake
{
public:
	Snake();
	~Snake();

	void Render(sf::RenderWindow& window);
	void Update();
	void UpdateMovement();

	std::vector<float> look(float type);

	void SetDir(int dir) { if(dir) m_dir = dir; };

	long GetFitness();

	bool IsDead() { return m_dead; };

	int GetScore() {return m_Score; };

private:
	void InitBody();
	void InitNewApple();
	void AddBody();

	void CheckIfInBounds();
	std::vector<sf::RectangleShape> m_body;
	std::vector<std::deque<short>> m_directions;
	sf::RectangleShape m_apple;

	bool m_dead = false;
	bool m_wallHit = false;
	short m_dir=0;
	short m_oldDir=0;
	sf::Vector2f m_offset = sf::Vector2f(0.43f * WINDOW_WIDTH - MAP_WIDTH * 0.5f * SNAKE_WIDTH, 0.5f * WINDOW_HEIGHT - MAP_HEIGHT * 0.5f * SNAKE_HEIGHT);
	int m_turns = StartTurns - TurnsPerPoint;
	int m_StepsTaken = 0;
	int m_Score = -1;


};

