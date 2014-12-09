#include "lib_function.h"

namespace yinyang{
	using namespace std;

	LibFunction::LibFunction(string name, long handle, int argc)
	{
	}

	LibFunction::~LibFunction(void)
	{
	}

	FunctionHandler* LibFunction::get_handler(vector<FunArg> _args)
	{
		if (_args.size() != _argc) return false;
		return new FunctionHandler(_argc, _args);
	}
}