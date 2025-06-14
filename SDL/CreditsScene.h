#pragma once
#include "Scene.h"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include <SDL_ttf.h>
#include <iostream>

#include "SceneManager.h"

class CreditsScene : public Scene {
public:
	CreditsScene(SDL_Window* window, SDL_Renderer* rend, SceneManager* sm) {
        win = window;
        renderer = rend;
        sceneManager = sm;
        running = false;
	}
    void Init(SDL_Renderer* renderer) override {
        running = true;

        TTF_Init();
        font = TTF_OpenFont("assets/font.ttf", 24);
        if (!font) {
            std::cout << "No se pudo cargar la fuente: " << TTF_GetError() << std::endl;
        }

        int buttonWidth = 100, buttonHeight = 100;
        buttons = {
            {{0, 0, buttonWidth, buttonHeight}, "Volver"},
        };
    }
    void HandleEvents(SDL_Event& event) override {
        if (!running) return;

        if (event.type == SDL_QUIT) {
            running = false;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            int x = event.button.x;
            int y = event.button.y;
            for (size_t i = 0; i < buttons.size(); ++i) {
                if (x > buttons[i].rect.x && x < buttons[i].rect.x + buttons[i].rect.w &&
                    y > buttons[i].rect.y && y < buttons[i].rect.y + buttons[i].rect.h) {
                    if (buttons[i].label == "Volver") {
                        //sceneManager->ChangeScene(new typename MainMenuScene(win, renderer, sceneManager), renderer);
                    }
                }
            }
        }
    }
    void Update(float deltaTime) override {

    }
    void Render(SDL_Renderer* renderer) override {
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        for (const auto& button : buttons) {
            SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);
            SDL_RenderFillRect(renderer, &button.rect);
            
            DrawText(renderer, "Programación", 480, 50);
            DrawText(renderer, "Daniel Gonzalez Peralta", 500, 75);
            DrawText(renderer, "Hugo Ahmed Peralta", 500, 85);
            DrawText(renderer, button.label, button.rect.x + 20, button.rect.y + 10);
        }

        SDL_RenderPresent(renderer);
    }
    void CleanUp() override {
        if (font) {
            TTF_CloseFont(font);
            font = nullptr;
        }
        TTF_Quit();
        std::cout << "Credits scene cleared\n";
    }

    bool IsRunning() const override {
        return running;
    }
private:
    struct Button {
        SDL_Rect rect;
        std::string label;
    };

    std::vector<Button> buttons;
    TTF_Font* font = nullptr;

    void DrawText(SDL_Renderer* renderer, const std::string& text, int x, int y) {
        SDL_Color color = { 255, 255, 255 };
        SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect dst = { x, y, surface->w, surface->h };
        SDL_RenderCopy(renderer, texture, nullptr, &dst);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    bool running;

    SceneManager* sceneManager;
    SDL_Window* win;
    SDL_Renderer* renderer;
};