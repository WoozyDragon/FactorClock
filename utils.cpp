#include <chrono>
#include <thread>

typedef unsigned int u32;

inline int clamp(int min, int val, int max)
{
	if (val < min) return min;
	if (val > max) return max;
	return val;
}

static void frameDelay(std::chrono::system_clock::time_point startTime, double framerate)
{
	std::this_thread::sleep_until(startTime + std::chrono::milliseconds(static_cast<int>((1. / framerate) * 1000)));
}