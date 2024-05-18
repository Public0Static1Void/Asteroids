#include "Scene.h"

Scene::Scene() {
	id = 0;
	*(name) = "";

	width = 0;
	height = 0;

	InitSceneWindow();
}
Scene::Scene(int w, int h) {
	id = 0;
	*(name) = "";

	width = w;
	height = h;

	InitSceneWindow();
}
Scene::Scene(int i, int w, int h) {
	id = i;
	*(name) = "";

	width = w;
	height = h;

	InitSceneWindow();
}
Scene::Scene(std::string* n, int w, int h) {
	id = 0;
	name = n;

	width = w;
	height = h;

	InitSceneWindow();
}
Scene::Scene(std::string* n, int i, int w, int h) {
	id = i;
	name = n;

	width = w;
	height = h;

	InitSceneWindow();
}

Scene::~Scene() {

}

void Scene::InitSceneWindow() {
	window = SDL_CreateWindow(name->c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, id, 0);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	on_run = true;
}

void Scene::Render(SDL_Renderer* rend) {
	SDL_RenderPresent(rend);
}

void Scene::ClearScreen(SDL_Renderer* rend) {
	SDL_RenderClear(rend);
}

void Scene::SetBackgroundColor(SDL_Color col) {
	SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
}