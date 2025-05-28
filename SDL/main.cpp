#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

#include "SceneManager.h"
#include "Time.h"
#include "Game.h"

using namespace std;
using namespace chrono;

#include "Player.h"

#include "SceneManager.h"
#include "GameScene.h"
#include "MainMenuScene.h"

int main(int argc, char* argv[]) {
	/*
	SDL_Init(SDL_INIT_EVERYTHING);

	SceneManager sceneManager;
	Scene main_scene = sceneManager.CreateScene(800, 400, new std::string("Main scene"));

	Timer timer;

	while (main_scene.on_run) {
		
		main_scene.ClearScreen(sceneManager.renderer); // Limpia la pantalla

		high_resolution_clock::time_point before = Timer::GetActualTime(); // Tiempo al empezar el bucle

		// -- Lógica del juego ------------------------------------------------------



		// --------------------------------------------------------------------------

		high_resolution_clock::time_point after = Timer::GetActualTime(); // Tiempo al finalizar el bucle
		timer.UpdateDeltaTime(before, after);
		
		cout << timer.deltaTime * 100000 << endl;

		main_scene.Render(sceneManager.renderer);
	}
	*/
	bool con = true;
	while (con) {
		cout << "Asteroids ------\n1- Play\n2- Exit\n3- Credits\n\n-- > ";
		int input = 0;
		cin >> input;
		switch (input) {
		case 1:
			cout << "Starting..." << endl;
			Timer::Wait(2.2f);
			con = false;
			break;
		case 2:
			cout << ":/" << endl;
			return 0;
		case 3:
			cout << "-- Code --------------" << endl << "Daniel Gonzalez\nHugo Ahmed\n\n\n";
		}
	}

	/*
	Game* game = new Game();

	game->InitGame("Asteroids", 1080, 540, false, 120);

	while (game->Running()) {
		high_resolution_clock::time_point before = game->timer->GetActualTime();

		game->HandleEvents();
		game->Update();
		game->Render();

		high_resolution_clock::time_point after = game->timer->GetActualTime();
		game->timer->UpdateDeltaTime(before, after);

		// Limitador de fps
		if (game->timer->deltaTime < game->framerate / 1000) {
			Timer::Wait(game->framerate / 1000 - game->timer->deltaTime);
		}
	}

	game->Clear();
	*/

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { // No se ha iniciado todo bien
		return 1;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "SDL_mixer error: " << Mix_GetError() << std::endl;
	}

	cout << "Init succesful." << endl;

	std::srand(std::time(0));

	int flags = 0;

	SDL_Window* window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 540, flags);
	if (window)
		cout << "Window created at Game.cpp" << endl;
	else
		cout << "Failed to create a window at Game.cpp" << endl;

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer) {
		cout << "Renderer created at Game.cpp" << endl;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}
	else
		cout << "Renderer failed to create at Game.cpp" << endl;

    //renderer = SDL_CreateRenderer(nullptr, -1, SDL_RENDERER_ACCELERATED);

	SceneManager sceneManager;
	sceneManager.ChangeScene(new GameScene(window), renderer);

	Timer timer;
	SDL_Event event;

	while (sceneManager.IsSceneRunning()) {
		high_resolution_clock::time_point before = timer.GetActualTime();

		while (SDL_PollEvent(&event)) {
			sceneManager.HandleEvents(event);
		}

		sceneManager.Update(timer.deltaTime);
		sceneManager.Render(renderer);

		high_resolution_clock::time_point after = timer.GetActualTime();
		timer.UpdateDeltaTime(before, after);
	}

	return 0;
}