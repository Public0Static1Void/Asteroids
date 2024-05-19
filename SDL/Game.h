#pragma once
#include "SceneManager.h"
#include "SDL_image.h"
#include "Time.h"
#include <iostream>

class Game {
public:
	Game();
	~Game();

	void InitGame(const char* title, int width, int height, bool fullScreen, int f_p_s);

	void HandleEvents();
	void Update();
	void Render();
	void Clear();

	bool Running();

	int fps;
	float framerate;

	Timer* timer;
private:
	bool isRunning;

	SDL_Window* window;
	SDL_Renderer* renderer;

	int count;
};