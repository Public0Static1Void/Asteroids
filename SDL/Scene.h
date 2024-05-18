#pragma once
#include <SDL.h>
#include <string>
class Scene {
public:
	Scene();
	Scene(int w, int h);
	Scene(int i, int w, int h);
	Scene(std::string* n, int w, int h);
	Scene(std::string* n, int i, int w, int h);
	~Scene();

	void SetBackgroundColor(SDL_Color col);
	void Render(SDL_Renderer* rend);
	void ClearScreen(SDL_Renderer* rend);

	int id;
	std::string* name;

	int width, height;

	bool on_run;

	SDL_Window* window;
	SDL_Renderer* renderer;

	void InitSceneWindow();
};