#include "Time.h"

using namespace std::chrono;

Timer::Timer() {
	deltaTime = 0;
}
Timer::~Timer() {

}

high_resolution_clock::time_point Timer::GetActualTime() {
	return high_resolution_clock::now();

}

void Timer::UpdateDeltaTime(std::chrono::high_resolution_clock::time_point before, std::chrono::high_resolution_clock::time_point after) {
	deltaTime = duration_cast<duration<float>>(after - before).count();
}