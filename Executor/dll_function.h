#pragma once
#include <string>
#include <vector>
#include "fun_arg.h"
#include "function_handler.h"

namespace yinyang
{
	class dll_function
	{
	public:
		dll_function(std::string name, long handle, int argc);
		~dll_function(void);
		function_handler* get_handler(std::vector<fun_arg> args);
	private:
		int _argc;
		std::string _name;
		long _handle;
		std::vector <fun_arg> _args; 
	};
}