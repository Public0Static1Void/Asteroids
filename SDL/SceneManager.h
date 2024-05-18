#pragma once
#include "Scene.h"
#include <vector>

class SceneManager : Scene {
public:
	SceneManager();
	~SceneManager();

	int scene_num;
	int current_scene;

	std::vector<Scene> scenes;

	Scene CreateScene(int w, int h, std::string* name);
	void LoadScene(int id_scene);

	Scene GetScene(std::string scene_name);
	Scene GetScene(int id);

	SDL_Renderer* sm_renderer;

	
};