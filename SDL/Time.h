#pragma once
#include <chrono>

class Timer {
public:
	Timer();
	~Timer();

	static std::chrono::high_resolution_clock::time_point GetActualTime();
	void UpdateDeltaTime(std::chrono::high_resolution_clock::time_point before, std::chrono::high_resolution_clock::time_point after);

	static void Wait(float time);

	float deltaTime;
private:
};