#define ASTEROID_H
#include <cmath>
#include "Player.h"
#include <iostream>
#include <SDL.h>
#include "Vector2.h"

class Asteroid {
private:
    float x, y;
    float directionX, directionY;


public:
    Asteroid(float x, float y, int width, int height, float speed, int size, const char* im_address, bool has_parent);

    void LoadSprites(SDL_Renderer* renderer);

    void updatePosition(const Player* player);
    void Render(SDL_Renderer* renderer);

    float getX() const { return x; }
    float getY() const { return y; }

    Vector2 GetDir() { return Vector2(directionX, directionY); }
    void SetDir(float x_dir, float y_dir);

    SDL_Rect* asteroidRect;
    SDL_Texture* asteroid_texture;

    bool checkCollision(const SDL_Rect* otherRect);

    const char* image_address;
    bool launched;

    int size;

    float rotation;
    float speed;

    bool dead = false;
    bool parent;
};