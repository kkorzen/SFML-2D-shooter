#pragma once

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;
using namespace sf;

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define FPS 60

inline int random(int max, int min = 0) { return rand() % (max - min) + min; }