#pragma once
#include <string>
#include <map>

#include "lib_function.h"

namespace yinyang
{
	class DllLibrary
	{
	public:
		DllLibrary(std::string path);
		~DllLibrary();
		bool init_dll();
		long load_function(std::string name, int args);
		bool handle_func(std::string name, std::vector<FunArg> args);
	private: 
		std::string _dll_path;
		long _dll_handle;
		std::map<std::string, LibFunction> _funcs;
	};
}