#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

//Settings : 
constexpr unsigned WINDOW_WIDTH = 1920;
constexpr unsigned WINDOW_HEIGHT = 1080;

constexpr  float SNAKE_WIDTH = 38;
constexpr  float SNAKE_HEIGHT = 38; //note: i Did not check what would have happened if you gave seperete WIDTH and HEIGHT values, its best if our snake is a square
constexpr int MAP_WIDTH = 20;
constexpr int MAP_HEIGHT = 20;
constexpr const bool HumanPlaying = false;

//AI
const float MutationRate = 2.5f;