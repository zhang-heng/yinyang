#pragma once
#include <string>
#include <vector>
#include "fun_arg.h"
#include "function_handler.h"

namespace yinyang
{
	class LibFunction
	{
	public:
		LibFunction(std::string name, long handle, int argc);
		~LibFunction(void);
		FunctionHandler* get_handler(std::vector<FunArg> args);
	private:
		int _argc;
		std::string _name;
		long _handle;
		std::vector <FunArg> _args; 
	};
}