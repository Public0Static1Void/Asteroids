#include "SceneManager.h"

SceneManager::SceneManager() {
	scene_num = 0;
	scenes = {};

}
SceneManager::~SceneManager() {

}

Scene SceneManager::CreateScene(int w, int h, std::string* name) {
	Scene scene(name, scene_num, w, h);

	scenes.push_back(scene);
	scene_num++;

	return scene;
}
void SceneManager::LoadScene(int id_scene) {
	current_scene = id_scene;

	renderer = SDL_CreateRenderer(scenes[current_scene].window, id, 0);
}

Scene SceneManager::GetScene(std::string scene_name) {
	for (int i = 0; i < scenes.size() - 1; i++) {
		if (*(scenes[i].name) == scene_name)
			return scenes[i];
	}
	Scene undefinded;
	return undefinded;
}
Scene SceneManager::GetScene(int id_scene) {
	for (int i = 0; i < scenes.size() - 1; i++) {
		if (scenes[i].id = id_scene)
			return scenes[i];
	}
	Scene undefinded;
	return undefinded;
}