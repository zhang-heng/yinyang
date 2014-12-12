#include "dll_library.h"
#include <windows.h>

namespace yinyang{
	using namespace std;
	DllLibrary::DllLibrary(string path)
		:_dll_path(path), _dll_handle(0) { }

	DllLibrary::~DllLibrary(void)	{ }

	long DllLibrary::LoadDllLibrary()
	{
		_dll_handle = (long) LoadLibrary(_dll_path.c_str());
		return _dll_handle;
	}

	long DllLibrary::GetLibraryId()
	{
		return _dll_handle;
	}

	long DllLibrary::LoadFunction(string name, long argn)
	{
		auto ret = (long)GetProcAddress((HMODULE)_dll_handle, name.c_str());
		if(ret)
		{
			_funcs.insert(pair<string, LibFunction>(name, LibFunction(name, argn, ret)));
			return ret;
		}
		return 0;
	}

	string DllLibrary::GetPath()
	{
		return _dll_path;
	}

	bool DllLibrary::HasFunction( long fun_id )
	{
		return false;
	}

	FunctionHandler DllLibrary::GetFunctionHanlder(long fun_id)
	{
		throw exception();
	}
}