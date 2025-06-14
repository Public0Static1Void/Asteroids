#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include "SDL_image.h"
#include <math.h>
#include <iostream>

#include "Bullet.h"
#include "Time.h"

class Player {
public:
	Player(int x, int y, int w, int h, float speed, int rotation_speed, const char* pl_address, int f_p_s);
	~Player();

	void Move(int dir_x, int dir_y, Timer* timer);
	void Shoot();

	void LoadSprites(SDL_Renderer* renderer);


	SDL_Texture* GetTexture() { return playerTex; }
	int GetAngle() { return rotation; }

	SDL_Rect* pRect;

	void Render(SDL_Renderer* renderer);

	const float getX() { return posX; }
	const float getY() { return posY; }

	void SetPosition(int x, int y) { posX = x; posY = y; }

	int loop_count;
	int lives = 3;

	static const int bullet_num = 10;
	Bullet* bullet[bullet_num];

	bool damaged = false;
	float invulnerable_time = 0;

private:
	int fps = 0;

	const char* image_address;

	float damaged_timer = 0, rendered_timer = 0;

	float speed;
	float max_speed;
	float inertia;
	float rotation_speed;

	float posX, posY;

	int rotation;

	SDL_Texture* playerTex;

	int current_bullet = 0;

	int delay = 25;

	Mix_Chunk* move_sound;
	Mix_Chunk* shoot_sound;

	bool rendered = false;
};