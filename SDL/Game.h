#pragma once
#include "SceneManager.h"
#include "SDL_image.h"
#include "Time.h"
#include "Player.h"
#include "asteroid.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

class Game {
public:
	Game(SDL_Window* win, SDL_Renderer* rend);
	~Game();

	void InitGame(const char* title, int width, int height, bool fullScreen, int f_p_s);

	void HandleEvents();
	void Update();
	void Render();
	void Clear();

	bool Running();

	void SaveScore(int score);

	int fps;
	float framerate;

	Timer* timer;
private:
	void createAsteroid(int num, int size, Asteroid* parent);

	bool isRunning;

	SDL_Window* window;
	SDL_Renderer* renderer;

	int count;

	Player* player;
	Asteroid* asteroid_mini;
	Asteroid* asteroid_mid;
	Asteroid* asteroid_big;

	void SpawnAsteroids(int num);

	void ShowText(int x, int y, const char* phrase, SDL_Color color);

	int round = 0;

	int score = 0;

	std::vector<Asteroid*> asteroids = {};

	TTF_Font* font;
};