#ifndef THREAD_HELPER_HPP
#define THREAD_HELPER_HPP

#include <cstdint>
#include <functional>

class ThreadHelper
{
	public:
		static void dispatchWork(std::size_t jobsCount,
			const std::function<void(std::size_t, std::size_t)>& function,
			std::size_t maxArgument);
};


#endif // THREAD_HELPER_HPP
