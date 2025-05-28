#include "Bullet.h"

using namespace std;

Bullet::Bullet(float x, float y, int width, int height, float sp, const char* im_address, int maxloops) {
	bullet_rect = new SDL_Rect();

	speed = sp;
	image_address = im_address;

	xPos = x; yPos = y;
	bullet_rect->w = width;
	bullet_rect->h = height;

	dir_x = 0; dir_y = 0;

	rotation = 0; radians = 0;

	max_loops = maxloops;

	hasLaunched = false;
}
Bullet::~Bullet() {}

void Bullet::LoadSprites(SDL_Renderer* renderer) {
	SDL_Surface* tmpSurface = IMG_Load(image_address);
	bullet_texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
}

void Bullet::Launch(float rot) {
	if (render) {
		loops++;
		if (loops > max_loops) {
			loops = 0;
			render = false;
		}
	}
	
	if (!hasLaunched) {
		rotation = rot;
		radians = rotation * M_PI / 180;
		hasLaunched = true;
	}

	xPos += speed * sin(radians) * 0.5f;
	yPos += speed * -cos(radians) * 0.5f;

	if (xPos > 1080 + bullet_rect->w) xPos = -bullet_rect->w;
	else if (xPos < -bullet_rect->w) xPos = 1080 - bullet_rect->w;
	if (yPos > 540 + bullet_rect->h) yPos = -bullet_rect->h;
	else if (yPos < -bullet_rect->h) yPos = 540 + bullet_rect->h;

	bullet_rect->x = static_cast<int>(xPos);
	bullet_rect->y = static_cast<int>(yPos);

	//cout << "Position: ( " << xPos << ", " << yPos << " )" << endl;
}

void Bullet::RestoreBullet(int x, int y) {
	bullet_rect->x = x;
	bullet_rect->y = y;

	xPos = x; yPos = y;

	loops = 0;

	hasLaunched = false;
	render = true;
}

void Bullet::Render(SDL_Renderer* renderer) {
	if (!render) return;
	cout << "Bullet collision" << endl;
	SDL_RenderCopyEx(renderer, bullet_texture, nullptr, bullet_rect, rotation, nullptr, SDL_FLIP_NONE);
}

bool Bullet::checkCollision(SDL_Rect* rect) {
	if (!render) return false;
	return SDL_HasIntersection(bullet_rect, rect);
}