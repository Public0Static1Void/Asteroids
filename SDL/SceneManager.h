#pragma once
#include "Scene.h"

class SceneManager {
public:
	~SceneManager();

	void ChangeScene(Scene* newScene, SDL_Renderer* renderer);
	void HandleEvents(SDL_Event& event);
	void Update(float deltaTime);
	void Render(SDL_Renderer* renderer);

	bool IsSceneRunning() const {
		return currentScene && currentScene->IsRunning();
	}

private:
	Scene* currentScene = nullptr;
};