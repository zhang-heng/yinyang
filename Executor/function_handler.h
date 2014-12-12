#pragma once
#include <vector>
#include <thread>
#include "fun_arg.h"

namespace yinyang{


	class FunctionHandler
	{
	public:
		FunctionHandler(int h, std::vector<FunArg> args);
		~FunctionHandler(void);
		void Handle(FunArgs args);




		void handle(void (*finish)(std::vector<FunArg> args, long ret));
	private:
		long call_method();
		int _handle;
		std::thread _thread;
		std::vector<FunArg> _args;
	};
}