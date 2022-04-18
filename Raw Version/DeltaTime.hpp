#pragma once
#include "SFML/Graphics.hpp"
class DeltaTime
{
public:
	static DeltaTime& Get() { return s_instance; };
	void RestartClock() { m_deltaT = m_DeltaTimeClock.restart().asSeconds(); };
	float GetDeltaTime() { return m_deltaT; };
private:
	DeltaTime();
	~DeltaTime();

	static DeltaTime s_instance;
	sf::Clock m_DeltaTimeClock;
	float m_deltaT = 0.0f;
};

