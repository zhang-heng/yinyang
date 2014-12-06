#include "dll_function.h"

namespace yinyang{
	using namespace std;

	dll_function::dll_function(string name, long handle, int argc)
	{
	}

	dll_function::~dll_function(void)
	{
	}

	function_handler* dll_function::get_handler(vector<fun_arg> _args)
	{
		if (_args.size() != _argc) return false;
		return new function_handler(_argc, _args);
	}
}