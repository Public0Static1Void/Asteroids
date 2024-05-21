#include "BigAsteroid.h"

BigAsteroid::BigAsteroid(SDL_Renderer* rend)
	: Asteroid(rend) {

	int random = rand() % 3;

	switch (random) {
	case 0:
		width = 73;
		height = 71;
		padding = Vector2(0.0f, 52.0f);

		break;

	case 1:
		width = 73;
		height = 73;
		padding = Vector2(78.0f, 52.0f);

		break;

	case 2:
		width = 97;
		height = 91;
		padding = Vector2(156.0f, 0.0f);

		break;

	}

	velocity = CalculatePositionInRadius(40);
	angularVelocity = 40 - (rand() % 81); //Entre -40 y 40

	radius = CalculateRadius(width, height);

	score = 50;

}