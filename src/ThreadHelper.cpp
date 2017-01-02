#include <vector>
#include <thread>
#include "ThreadHelper.hpp"

void ThreadHelper::dispatchWork(std::size_t jobsCount,
	const std::function<void(std::size_t, std::size_t)>& function,
	std::size_t maxArgument)
{
	if(jobsCount > 1)
	{
		const std::size_t step{maxArgument / jobsCount};
		std::vector<std::thread> threads;

		for(std::size_t i{0UL}; i < jobsCount; ++i)
			threads.emplace_back(function, i * step, (i + 1) * step);

		for(auto& thread : threads)
			thread.join();
	}
	else
		function(0UL, maxArgument);
}
