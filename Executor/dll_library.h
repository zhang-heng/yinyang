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
		long LoadDllLibrary();
		long GetLibraryId();
		std::string GetPath();
		long LoadFunction(std::string name);
		bool handle_func(std::string name, std::vector<FunArg> args);
	private:
		long _dll_handle;
		std::string _dll_path;
		std::map<std::string, LibFunction> _funcs;
	};
}