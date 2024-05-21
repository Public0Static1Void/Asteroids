#define ASTEROID_H
#include <cmath>
#include "Player.h"
#include <SDL.h>

class Asteroid {
private:
    float x, y;
    float speed;
    float directionX, directionY;

public:
    Asteroid(float x, float y, float speed);

    void updatePosition(const Player& player);
    void render(SDL_Renderer* renderer);
    float getX() const { return x; }
    float getY() const { return y; }
    void Asteroid::LoadSprites(SDL_Renderer* renderer) {}
    SDL_Rect asteroidRect;
};
