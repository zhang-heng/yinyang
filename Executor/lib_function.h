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
		LibFunction(std::string name, long argn, long handle);
		~LibFunction(void);
	private:
		const long _argn;
		const std::string _name;
		const long _handle;
	};
}