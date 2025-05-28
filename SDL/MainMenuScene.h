#pragma once
#include "Scene.h"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include <SDL_ttf.h>

#include "SceneManager.h"

using namespace std;

class MainMenuScene : public Scene {
public:
    MainMenuScene(SDL_Window* window, SDL_Renderer* rend, SceneManager* sm) {
        win = window;
        renderer = rend;
        sceneManager = sm;
    }
    void Init(SDL_Renderer* renderer) override {
        running = true;

        TTF_Init();
        font = TTF_OpenFont("assets/font.ttf", 24);
        if (!font) {
            std::cout << "No se pudo cargar la fuente: " << TTF_GetError() << std::endl;
        }

        int buttonWidth = 200, buttonHeight = 50;
        buttons = {
            {{440, 150, buttonWidth, buttonHeight}, "Play"},
            {{440, 220, buttonWidth, buttonHeight}, "Creditos"},
            {{440, 290, buttonWidth, buttonHeight}, "Salir"}
        };
    }
    void HandleEvents(SDL_Event& event) override {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            int x = event.button.x;
            int y = event.button.y;
            for (size_t i = 0; i < buttons.size(); ++i) {
                if (x > buttons[i].rect.x && x < buttons[i].rect.x + buttons[i].rect.w &&
                    y > buttons[i].rect.y && y < buttons[i].rect.y + buttons[i].rect.h) {
                    if (buttons[i].label == "Play") {
                        
                        sceneManager->ChangeScene(new GameScene(win), renderer);
                    }
                    else if (buttons[i].label == "Créditos") {
                        //sceneManager->ChangeScene(new CreditsScene(), event.button.windowID);
                    }
                    else if (buttons[i].label == "Salir") {
                        running = false;
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
        std::cout << "Menu scene cleared\n";
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
    SDL_Texture* creditTexture = nullptr;
    bool showCredits = false;

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