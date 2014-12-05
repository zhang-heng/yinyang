#pragma once
#include <string>
#include <vector>
#include "fun_arg.h"

namespace yinyang
{
	class dll_function
	{
	public:
		dll_function(void);
		~dll_function(void);
	private:
		std::string name;
		long handle;
		std::vector <fun_arg> args;
	};
}