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

void Asteroid::render(SDL_Renderer* renderer) {
    SDL_Rect asteroidRect = { static_cast<int>(x), static_cast<int>(y), 20, 20 };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red color
    SDL_RenderFillRect(renderer, &asteroidRect);
}