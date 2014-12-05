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
		bool handle_func();
	private: 
		long load_function(std::string name, int args);
		std::string _dll_path;
		long _dll_handle;
		std::map<std::string, dll_function> _funcs;
	};
}