#pragma once
#include <SDL.h>
#include <string>
class Scene {
public:
	Scene(int playerSpeed, int asteroidSpeed, int roundIncrease);
	~Scene();

	void Update();
};