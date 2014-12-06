#pragma once
#include <string>
#include <map>

#include "dll_function.h"

namespace yinyang
{
	class dll_library
	{
	public:
		dll_library(std::string path);
		~dll_library();
		bool init_dll();
		long load_function(std::string name, int args);
		bool handle_func(std::string name, std::vector<fun_arg> args);
	private: 
		std::string _dll_path;
		long _dll_handle;
		std::map<std::string, dll_function> _funcs;
	};
}