#include <SDL.h>
#include <iostream>

#include "SceneManager.h"
#include "Time.h"
#include "Game.h"

using namespace std;
using namespace chrono;

#include "Player.h"

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

	Game* game = new Game();

	game->InitGame("Asteroids", 1080, 540, false, 5);

	while (game->Running()) {
		high_resolution_clock::time_point before = game->timer->GetActualTime();

		game->HandleEvents();
		game->Update();
		game->Render();

		high_resolution_clock::time_point after = game->timer->GetActualTime();
		game->timer->UpdateDeltaTime(before, after);

		// Limitador de fps
		if (game->timer->deltaTime > game->framerate) {
			Timer::Wait(game->timer->deltaTime - game->framerate);
		}
	}

	game->Clear();

	return 0;
}