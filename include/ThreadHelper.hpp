#ifndef THREAD_HELPER_HPP
#define THREAD_HELPER_HPP

#include <cstdint>
#include <functional>
#include <vector>
#include <thread>

class ThreadHelper
{
	public:
		template <typename Function, typename... Args>
		static void dispatchWork(std::size_t jobsCount,
			const Function& function,
			std::size_t maxArgument,
			const Args&... args);
};

template <typename Function, typename... Args>
void ThreadHelper::dispatchWork(std::size_t jobsCount,
	const Function& function,
	std::size_t maxArgument,
	const Args&... args)
{
	if(jobsCount > 1)
	{
		const std::size_t step{maxArgument / jobsCount};
		std::vector<std::thread> threads;

		for(std::size_t i{0UL}; i < jobsCount; ++i)
			threads.emplace_back(function, i * step, (i + 1) * step, args...);

		for(auto& thread : threads)
			thread.join();
	}
	else
		function(0UL, maxArgument, args...);
}

#endif // THREAD_HELPER_HPP
