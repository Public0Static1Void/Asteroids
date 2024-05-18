#include "Game.h"
using namespace std;

Game::Game() {

}
Game::~Game() {

}

void Game::InitGame(const char* title, int width, int height, bool fullScreen) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { // No se ha iniciado todo bien
		isRunning = false;
		return;
	}

	cout << "Init succesful." << endl;

	int flags = 0;
	if (fullScreen)
		flags = SDL_WINDOW_FULLSCREEN;

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
	if (window)
		cout << "Window created at Game.cpp" << endl;
	else
		cout << "Failed to create a window at Game.cpp" << endl;

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer) {
		cout << "Renderer created at Game.cpp" << endl;
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}
	else
		cout << "Renderer failed to create at Game.cpp" << endl;

	isRunning = true; // Se ha creado todo bien y por tanto empieza el juego
}

void Game::HandleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		cout << "Requested a game exit" << endl;
		break;
	}
}

void Game::Update() {
	count++;
	cout << "Loop: " << count << endl;
}

void Game::Render() {
	SDL_RenderClear(renderer);

	// Aquí se añadirán las cosas para dibujarlas

	SDL_RenderPresent(renderer);
}

void Game::Clear() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();
	cout << "Game cleaned" << endl;
}

bool Game::Running() {
	return isRunning;
}