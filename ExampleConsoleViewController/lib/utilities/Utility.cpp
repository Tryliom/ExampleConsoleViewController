#include "Utility.h"

#include <chrono>
#include <thread>

namespace Utility
{
	void sleep(const int milliseconds)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}
}
