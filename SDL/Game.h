#pragma once
#include "SceneManager.h"
#include <iostream>

class Game {
public:
	Game();
	~Game();

	void InitGame(const char* title, int width, int height, bool fullScreen);

	void HandleEvents();
	void Update();
	void Render();
	void Clear();

	bool Running();

private:
	bool isRunning;

	SDL_Window* window;
	SDL_Renderer* renderer;

	int count;
};