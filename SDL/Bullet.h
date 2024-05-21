#pragma once
#include <SDL.h>
#include <iostream>
#include "SDL_image.h"

class Bullet {
public:
	Bullet(float x, float y, int width, int height, float speed, const char* image_address);
	~Bullet();

	void LoadSprites(SDL_Renderer* renderer);

	void Launch(float rotation);

	void Render(SDL_Renderer* renderer);

	void RestoreBullet(int x, int y);

	bool checkCollision(SDL_Rect* rect);

	SDL_Rect* bullet_rect;
private:
	float speed;
	float dir_x, dir_y;
	float rotation;
	float radians;
	
	float xPos, yPos;

	const char* image_address;


	SDL_Texture* bullet_texture;

	bool hasLaunched;
};