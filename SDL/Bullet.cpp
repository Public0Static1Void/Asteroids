#include "Bullet.h"

using namespace std;

Bullet::Bullet(float x, float y, int width, int height, float sp, const char* im_address) {
	speed = sp;
	image_address = im_address;

	xPos = x; yPos = y;
	bullet_rect.w = width;
	bullet_rect.h = height;

	dir_x = 0; dir_y = 0;

	rotation = 0; radians = 0;

	hasLaunched = false;
}
Bullet::~Bullet() {}

void Bullet::LoadSprites(SDL_Renderer* renderer) {
	SDL_Surface* tmpSurface = IMG_Load(image_address);
	bullet_texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
}

void Bullet::Launch(float rot) {

	if (!hasLaunched) {
		rotation = rot;
		radians = rotation * M_PI / 180;
		hasLaunched = true;
	}

	xPos += speed * sin(radians) * 0.5f;
	yPos += speed * -cos(radians) * 0.5f;

	bullet_rect.x = static_cast<int>(xPos);
	bullet_rect.y = static_cast<int>(yPos);

	cout << "Position: ( " << xPos << ", " << yPos << " )" << endl;
}

void Bullet::RestoreBullet(int x, int y) {
	bullet_rect.x = x;
	bullet_rect.y = y;

	xPos = x; yPos = y;

	hasLaunched = false;
}

void Bullet::Render(SDL_Renderer* renderer) {
	SDL_RenderCopyEx(renderer, bullet_texture, nullptr, &bullet_rect, rotation, nullptr, SDL_FLIP_NONE);
}