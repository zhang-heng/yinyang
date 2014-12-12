#include "lib_function.h"

namespace yinyang{
	using namespace std;

	LibFunction::LibFunction(string name, long argn, long handle)
		:_argn(argn), _name(name), _handle(handle)
	{
	}

	LibFunction::~LibFunction(void)
	{
	}
}