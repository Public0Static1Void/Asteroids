#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Scene.h"
#include "SceneManager.h"

using namespace std;

class ResultsScene : public Scene {
public:
	ResultsScene(SDL_Window* win, SceneManager* sm) { window = win; sceneManager = sm; }

	void Init(SDL_Renderer* renderer) override {
        font = TTF_OpenFont("assets/font.ttf", 24);
        GetHighScores();
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

    }

    void Render(SDL_Renderer* renderer) override {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        DrawText(renderer, "Highscores", 440, 50);
        for (int i = 0; i < scores.size() && i < 5; i++) {
            DrawText(renderer, to_string(scores[i]), 460, 75 + (i * 20));
        }

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

	SDL_Window* window;
	SceneManager* sceneManager;

    TTF_Font* font;

    void DrawText(SDL_Renderer* renderer, const std::string& text, int x, int y) {
        SDL_Color color = { 255, 255, 255 };
        SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect dst = { x, y, surface->w, surface->h };
        SDL_RenderCopy(renderer, texture, nullptr, &dst);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    void GetHighScores() {
        std::cout << "Getting highscores..." << std::endl;
        fstream file("score.txt");
        if (!file) {
            cerr << "Could not open score.txt" << endl;
            return;
        }

        // Lee todos los scores guardados
        int score;
        while (file >> score) {
            scores.push_back(score);
        }
        file.close();

        // Ordena de mayor a menor
        sort(scores.begin(), scores.end(), greater<int>());

        // Coge los 10 mejores
        cout << "Top 10 scores:" << endl;
        for (size_t i = 0; i < scores.size() && i < 10; ++i) {
            cout << scores[i] << endl;
        }
    }

private:
    vector<int> scores;
};