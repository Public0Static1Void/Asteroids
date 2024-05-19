#include "Game.h"
using namespace std;

SDL_Texture* playerTex;
SDL_Rect src_Rect, dst_Rect;

Game::Game() {
	timer = new Timer();
}
Game::~Game() {

}

void Game::InitGame(const char* title, int width, int height, bool fullScreen, int f_p_s) {
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
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}
	else
		cout << "Renderer failed to create at Game.cpp" << endl;

	fps = f_p_s;
	framerate = (1000 / fps); // Tiempo a tener entre frames

	isRunning = true; // Se ha creado todo bien y por tanto empieza el juego


	// Cargar texturas
	SDL_Surface* tmpSurface = IMG_Load("Assets/asteroids_nave.png");
	playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
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

	const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

	if (currentKeyStates[SDL_SCANCODE_UP]) {
		dst_Rect.y -= 1;
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN]) {
		dst_Rect.y += 1;
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
		dst_Rect.x += 1;
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		dst_Rect.x -= 1;
	}
}

void Game::Update() {
	count++;
	cout << "Loop: " << count << endl;

	dst_Rect.w = 32;
	dst_Rect.h = 32;

	chrono::high_resolution_clock::time_point after = timer->GetActualTime();
}

void Game::Render() {
	SDL_RenderClear(renderer);

	// Aquí se añadirán las cosas para dibujarlas
	SDL_RenderCopy(renderer, playerTex, NULL, &dst_Rect);

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