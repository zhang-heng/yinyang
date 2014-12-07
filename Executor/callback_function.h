#pragma once
#include <vector>

namespace yinyang{
	class callback_function
	{
	public:
		callback_function(void);
		~callback_function(void);
		static callback_function* get_callback_funciton(std::vector<std::vector<char>> args);
	};
}