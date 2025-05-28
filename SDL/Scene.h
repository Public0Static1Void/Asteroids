#pragma once
#include <SDL.h>

class Scene {
public:
	virtual ~Scene();

	virtual void Init(SDL_Renderer* renderer) = 0;
	virtual void HandleEvents(SDL_Event& event) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;
	virtual void CleanUp() = 0;

	virtual bool IsRunning() const = 0;
};