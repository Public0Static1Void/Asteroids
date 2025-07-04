#include "Player.h"
using namespace std;
Player::Player(int x, int y, int w, int h, float sp, int rot_speed, const char* pl_address, int f_p_s) {
	pRect = new SDL_Rect();
	
	posX = x;
	posY = y;

	pRect->w = w;
	pRect->h = h;

	speed = sp;
	max_speed = speed * 2;
	inertia = 0;

	rotation_speed = rot_speed;
	rotation = 0;

	image_address = pl_address;

	loop_count = 0;
	fps = f_p_s;

	// Sonidos
	move_sound = Mix_LoadWAV("Assets/s_ship_move.wav");
	shoot_sound = Mix_LoadWAV("Assets/s_shoot.wav");
	if (!move_sound) {
		cout << "no move sound!" << endl;
	}

	for (int i = 0; i < bullet_num; i++)
		bullet[i] = new Bullet(-10, 0, 5, 5, max_speed * 4, "Assets/asteroids_bala.png", fps / 2);
}
Player::~Player() {

}

void Player::LoadSprites(SDL_Renderer* renderer) {
	SDL_Surface* tmpSurface = IMG_Load(image_address);
	playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	for (int i = 0; i < bullet_num; i++)
		bullet[i]->LoadSprites(renderer);
}

void Player::Render(SDL_Renderer* renderer) {
	// El jugador parpadear� mientras sea invulnerable
	if (!damaged) {
		SDL_RenderCopyEx(renderer, playerTex, nullptr, pRect, rotation, nullptr, SDL_FLIP_NONE);
	}
	else {
		if (!rendered) {
			SDL_RenderCopyEx(renderer, playerTex, nullptr, pRect, rotation, nullptr, SDL_FLIP_NONE);
			rendered = true;
		}
	}
	for (int i = 0; i < bullet_num; i++)
		bullet[i]->Render(renderer);
}


float x = 0;
float y = 1;

void Player::Move(int dir_x, int dir_y, Timer* timer) {
	Mix_PlayChannel(-1, move_sound, 0);

	// Rotaci�n
    rotation += dir_x * rotation_speed;

	if (rotation > 180)
		rotation = -180;
	if (rotation < -180)
		rotation = 180;

	for (int i = 0; i < bullet_num; i++)
		bullet[i]->Launch(rotation);

	float angle = rotation * M_PI / 180; // Convierte el �ngulo a radianes

	inertia += -dir_y * speed * 0.01f; // A�ade la inercia en la direcci�n de movimiento

	if (inertia > max_speed) inertia = max_speed;
	if (inertia < -max_speed) inertia = -max_speed;

	if (dir_y == 0) {
		inertia *= 0.99f;
	}

	posX += inertia * sin(angle); // El coseno de angle da el n�mero de veces que se tiene que sumar a X para avanzar en ese �ngulo
	posY += inertia * -cos(angle); // Lo mismo con el seno

	// L�mites de la pantalla
	int screen_w = 1080;
	int screen_h = 540;
	if (posX > screen_w) posX -= screen_w + pRect->w;
	if (posX < -pRect->w) posX += screen_w + pRect->w;
	if (posY > screen_h) posY -= screen_h + pRect->h;
	if (posY < -pRect->h) posY += screen_h + pRect->h;

	// Aplica la nueva posici�n a trav�s de un cast
	pRect->x = static_cast<int>(posX);
	pRect->y = static_cast<int>(posY);

	// Timers ------------------------------------
	if (damaged) {
		damaged_timer += ((float)fps / 1000);
		if (damaged_timer >= invulnerable_time) {
			damaged = false;
			damaged_timer = 0;
		}
	}
	if (rendered) {
		rendered_timer += ((float)fps / 1000);
		if (rendered_timer >= 0.25f) {
			rendered = false;
			rendered_timer = 0;
		}
	}
}

void Player::Shoot() {
	if (loop_count < delay) return;

	Mix_PlayChannel(-1, shoot_sound, 0);

	bullet[current_bullet]->RestoreBullet(pRect->x + pRect->w / 2, pRect->y + pRect->h / 2);

	current_bullet++;
	if (current_bullet >= bullet_num)
		current_bullet = 0;

	loop_count = 0;
}