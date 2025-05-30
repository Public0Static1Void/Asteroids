#pragma once
#include <SDL.h>
#include <iostream>
#include "SDL_image.h"

class Bullet {
public:
	Bullet(float x, float y, int width, int height, float speed, const char* image_address, int maxloops);
	~Bullet();

	void LoadSprites(SDL_Renderer* renderer);

	void Launch(float rotation);

	void Render(SDL_Renderer* renderer);

	void RestoreBullet(int x, int y);

	bool checkCollision(SDL_Rect* rect);

	void SumY(int am) { xPos += am; }

	SDL_Rect* bullet_rect;
	bool render;
private:
	float speed;
	float dir_x, dir_y;
	float rotation;
	float radians;
	
	int max_loops;
	int loops = 0;

	float xPos, yPos;

	const char* image_address;


	SDL_Texture* bullet_texture;

	bool hasLaunched;
};