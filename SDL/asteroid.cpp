#include "Asteroid.h"

Asteroid::Asteroid(float x, float y, int width, int height, float speed, int s, const char* im_address, bool has_parent)
    : x(x), y(y), speed(speed), directionX(0), directionY(0), size(s), image_address(im_address), parent(has_parent) {

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
        // 1 de 5 asteroides irá dirigido al jugador
        int chase_player = rand() % 5;
        if (chase_player == 0 && !parent) {
            deltaX = player->pRect->x - x;
            deltaY = player->pRect->y - y;
        }
        else {
            deltaX = rand() % 360;
            deltaY = rand() % 360;
        }
        float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

        if (distance != 0) {
            
            directionX = deltaX / distance;
            directionY = deltaY / distance;
        }
        launched = true;
    }
    
    x += directionX * speed;
    y += directionY * speed;

    // Límites de la pantalla
    int screen_w = 1080;
    int screen_h = 540;
    if (x > screen_w) x -= screen_w + asteroidRect->w;
    if (x < -asteroidRect->w) x += screen_w + asteroidRect->w;
    if (y > screen_h) y -= screen_h + asteroidRect->h;
    if (y < -asteroidRect->h) y += screen_h + asteroidRect->h;

    asteroidRect->x = static_cast<int>(x);
    asteroidRect->y = static_cast<int>(y);
}

void Asteroid::SetDir(float x_dir, float y_dir) {
    float distance = std::sqrt(x_dir * x_dir + y_dir * y_dir);
    directionX = x_dir / distance;
    directionY = y_dir / distance;
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