#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include <random>

class Math
{
public:
	static Math& Get() { return s_instance; };
	const int randomInt(int min, int max) { return min + std::rand() % (max - min + 1); };

	const float randomFloat(float min, float max)
	{
		if (min == max)
			return min;
		std::random_device rgen;
		std::uniform_real_distribution<> box(min, max);
		return static_cast<float>(box(rgen));
	}

	const float sigmoid(float val) { return 1.f / (1.f + std::pow(2.71828182f, -val)); }; //this is just a sigmoid function, check this for more information https://en.wikipedia.org/wiki/Sigmoid_function

private:
	Math();
	~Math();

	static Math s_instance;
};