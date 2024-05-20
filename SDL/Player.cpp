#include "Player.h"

Player::Player(int x, int y, int w, int h, float sp, int rot_speed, const char* pl_address) {
	posX = x;
	posY = y;

	pRect.w = w;
	pRect.h = h;

	speed = sp;
	max_speed = speed * 2;
	inertia = 0;

	rotation_speed = rot_speed;
	rotation = 0;

	image_address = pl_address;
}
Player::~Player() {

}

void Player::LoadSprites(SDL_Renderer* renderer) {
	SDL_Surface* tmpSurface = IMG_Load(image_address);
	playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
}

void Player::Render(SDL_Renderer* renderer) {
	SDL_RenderCopyEx(renderer, playerTex, nullptr, &pRect, rotation, nullptr, SDL_FLIP_NONE);
}


float x = 0;
float y = 1;

void Player::Move(int dir_x, int dir_y) {
	// Rotación
    rotation += dir_x * rotation_speed;

	if (rotation > 180)
		rotation = -180;
	if (rotation < -180)
		rotation = 180;


	float angle = rotation * M_PI / 180; // Convierte el ángulo a radianes

	inertia += -dir_y * speed * 0.01f; // Añade la inercia en la dirección de movimiento

	if (inertia > max_speed) inertia = max_speed;
	if (inertia < -max_speed) inertia = -max_speed;

	if (dir_y == 0) {
		inertia *= 0.99f;
	}

	posX += inertia * sin(angle); // El coseno de angle da el número de veces que se tiene que sumar a X para avanzar en ese ángulo
	posY += inertia * -cos(angle); // Lo mismo con el seno




	// Límites de la pantalla
	int screen_w = 1080;
	int screen_h = 540;
	if (posX > screen_w) posX -= screen_w + pRect.w;
	if (posX < -pRect.w) posX += screen_w + pRect.w;
	if (posY > screen_h) posY -= screen_h + pRect.h;
	if (posY < -pRect.h) posY += screen_h + pRect.h;

	// Aplica la nueva posición a través de un cast
	pRect.x = static_cast<int>(posX);
	pRect.y = static_cast<int>(posY);

	// Debug
	std::cout << "Position: ( " << posX << ", " << posY << " ), Rotation: " << angle << ", Inertia: " << inertia << std::endl;
}

void Player::Shoot() {

}