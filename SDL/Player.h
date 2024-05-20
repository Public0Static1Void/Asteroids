#pragma once
#include <SDL.h>
#include "SDL_image.h"
#include <math.h>
#include <iostream>

class Player {
public:
	Player(int x, int y, int w, int h, float speed, int rotation_speed, const char* pl_address);
	~Player();

	void Move(int dir_x, int dir_y);
	void Shoot();

	void LoadSprites(SDL_Renderer* renderer);


	SDL_Texture* GetTexture() { return playerTex; }
	int GetAngle() { return rotation; }

	SDL_Rect pRect;

	void Render(SDL_Renderer* renderer);

private:
	const char* image_address;

	float speed;
	float max_speed;
	float inertia;
	float rotation_speed;

	float posX, posY;

	int rotation;

	SDL_Texture* playerTex;

};