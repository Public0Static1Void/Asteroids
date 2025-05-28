#pragma once
#include "Scene.h"
#include <SDL.h>
#include <iostream>

#include "SceneManager.h"
#include "Time.h"
#include "Game.h"

using namespace std;
using namespace chrono;

#include "Player.h"

class GameScene : public Scene
{
public:
    GameScene(SDL_Window* win) { window = win; }
    void Init(SDL_Renderer* renderer) override {
        game = new Game(window, renderer);
        game->InitGame("Asteroids", 1080, 540, false, 120);

        running = true;
    }

    void HandleEvents(SDL_Event& event) override {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_RETURN) {
                // Avanzar a otra escena
                running = false;
            }
        }
    }

    void Update(float deltaTime) override {
        while (running && game->Running()) {
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
    }

    void Render(SDL_Renderer* renderer) override {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
    }

    void CleanUp() override {
        std::cout << "Game scene cleared\n";
    }

    bool IsRunning() const override {
        return running;
    }

private:
	bool running;

	Game* game;
    SDL_Window* window;
};