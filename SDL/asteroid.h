#define ASTEROID_H
#include <cmath>
#include "Player.h"
#include <iostream>
#include <SDL.h>

class Asteroid {
private:
    float x, y;
    float speed;
    float directionX, directionY;


public:
    Asteroid(float x, float y, int width, int height, float speed, int size, const char* im_address);

    void LoadSprites(SDL_Renderer* renderer);

    void updatePosition(const Player* player);
    void Render(SDL_Renderer* renderer);

    float getX() const { return x; }
    float getY() const { return y; }


    SDL_Rect asteroidRect;
    SDL_Texture* asteroid_texture;

    bool checkCollision(const SDL_Rect* otherRect);

    const char* image_address;
    bool launched;

    int size;

    float rotation;

    bool dead = false;
};