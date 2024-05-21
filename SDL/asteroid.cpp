#include "Asteroid.h"

Asteroid::Asteroid(float x, float y, int width, int height, float speed, int s, const char* im_address)
    : x(x), y(y), speed(speed), directionX(0), directionY(0), size(s), image_address(im_address) {

    asteroidRect = new SDL_Rect();

    asteroidRect->w = width;
    asteroidRect->h = height;

    rotation = 0;
}

void Asteroid::updatePosition(const Player* player) {
    
    float deltaX;
    float deltaY;
    if (!launched)
    {
        deltaX = player->pRect->x - x;
        deltaY = player->pRect->y - y;

        float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

        if (distance != 0) {
            
            directionX = deltaX / distance;
            directionY = deltaY / distance;
        }
        launched = true;
    }
    
    x += directionX * speed;
    y += directionY * speed;

    if (x < 0 - asteroidRect->w) x += 1080;
    if (x > 1080 + asteroidRect->w) x -= 1080;
    if (y < 0 - asteroidRect->h) y += 540;
    if (y > 540 + asteroidRect->h) y -= 540;

    asteroidRect->x = static_cast<int>(x);
    asteroidRect->y = static_cast<int>(y);

    std::cout << "Position: ( " << asteroidRect->x << ", " << asteroidRect->y << " )\n";
}

void Asteroid::LoadSprites(SDL_Renderer* renderer) {
    SDL_Surface* tmpSurface = IMG_Load(image_address);
    asteroid_texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
}

void Asteroid::Render(SDL_Renderer* renderer) {
    SDL_RenderCopyEx(renderer, asteroid_texture, nullptr, asteroidRect, rotation, nullptr, SDL_FLIP_NONE);
}

bool Asteroid::checkCollision(const SDL_Rect* otherRect) {
    if (dead) return false;
    return SDL_HasIntersection(asteroidRect, otherRect);
}