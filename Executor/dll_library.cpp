#include "dll_library.h"
#include <windows.h>

namespace yinyang{
	using namespace std;
	DllLibrary::DllLibrary(string path):_dll_path(path), _dll_handle(0) { }

	DllLibrary::~DllLibrary(void)	{ }

	bool DllLibrary::init_dll()
	{
		return true;
	}

	long DllLibrary::load_function(string name, int args)
	{
		return 0;
	}
}