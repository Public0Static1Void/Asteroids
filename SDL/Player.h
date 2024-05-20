#pragma once
#include <SDL.h>
#include "SDL_image.h"
#include <math.h>
#include <iostream>

#include "Bullet.h"
#include "Time.h"

class Player {
public:
	Player(int x, int y, int w, int h, float speed, int rotation_speed, const char* pl_address);
	~Player();

	void Move(int dir_x, int dir_y, Timer* timer);
	void Shoot();

	void LoadSprites(SDL_Renderer* renderer);


	SDL_Texture* GetTexture() { return playerTex; }
	int GetAngle() { return rotation; }

	SDL_Rect pRect;

	void Render(SDL_Renderer* renderer);

	const float getX() { return posX; }
	const float getY() { return posY; }

	int loop_count;

private:
	const char* image_address;

	float speed;
	float max_speed;
	float inertia;
	float rotation_speed;

	float posX, posY;

	int rotation;

	SDL_Texture* playerTex;

	static const int bullet_num = 10;
	Bullet* bullet[bullet_num];

	int current_bullet;

	int delay = 30;
};