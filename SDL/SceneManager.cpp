#include "SceneManager.h"
SceneManager::~SceneManager() {
	if (currentScene) {
		currentScene->CleanUp();
	}
}

void SceneManager::ChangeScene(Scene* newScene, SDL_Renderer* renderer) {
	if (currentScene) {
		currentScene->CleanUp();
		delete currentScene;
	}
	currentScene = newScene;
	currentScene->Init(renderer);
}

void SceneManager::HandleEvents(SDL_Event& event) {
	if (currentScene) {
		currentScene->HandleEvents(event);
	}
}

void SceneManager::Update(float deltaTime) {
	if (currentScene) {
		currentScene->Update(deltaTime);
	}
}

void SceneManager::Render(SDL_Renderer* renderer) {
	if (currentScene) {
		currentScene->Render(renderer);
	}
}