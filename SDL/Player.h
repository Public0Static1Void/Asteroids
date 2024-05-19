#pragma once
#include <SDL.h>

class Player {
public:
	Player();
	~Player();

	SDL_Rect pRect;

	void Move();
	void Shoot();
};