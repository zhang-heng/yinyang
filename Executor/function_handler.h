#pragma once
#include <vector>
#include <thread>
#include "fun_arg.h"

namespace yinyang{
	class function_handler
	{
	public:
		function_handler(int h, std::vector<fun_arg> args);
		~function_handler(void);
		void handle(void (*finish)(std::vector<fun_arg> args, long ret));
	private:
		long call_method();
		int _handle;
		std::thread _thread;
		std::vector<fun_arg> _args;
	};
}