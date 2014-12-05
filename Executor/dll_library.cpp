#include "dll_library.h"
#include <windows.h>

namespace yinyang{
	using namespace std;
	dll_library::dll_library(string path):_dll_path(path), _dll_handle(0) { }

	dll_library::~dll_library(void)	{ }

	bool dll_library::init_dll()
	{
		return true;
	}

	long dll_library::load_function(string name, int args)
	{
		return 0;
	}
}