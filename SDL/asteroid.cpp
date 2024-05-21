#include "Asteroid.h"

Asteroid::Asteroid(float x, float y, float speed)
    : x(x), y(y), speed(speed), directionX(0), directionY(0) {}

void Asteroid::updatePosition(const Player& player) {
    // Calculate direction vector from asteroid to player
    float deltaX = player.pRect.x - x;
    float deltaY = player.pRect.y - y;
    float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    if (distance != 0) {
        // Normalize the direction vector
        directionX = deltaX / distance;
        directionY = deltaY / distance;
    }

    // Update position
    x += directionX * speed;
    y += directionY * speed;
}

void Bullet::LoadSprites(SDL_Renderer* renderer) {
	SDL_Surface* tmpSurface = IMG_Load(image_address);
	bullet_texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
}

void Asteroid::Render(SDL_Renderer* renderer) {
    SDL_RenderCopyEx(renderer, bullet_texture, nullptr, &bullet_rect, rotation, nullptr, SDL_FLIP_NONE);
}