#include "fun_arg.h"
#include <string>

namespace yinyang{
	using namespace std;
	ReturnArg::ReturnArg()
	{
		//_type = ArgumentType::Return;
	}

	ValueArg::ValueArg()
	{
		_type = ArgumentType::Value;
	}

	ReferArg::ReferArg()
	{
		_type = ArgumentType::Refer;
	}

	CallbackArg::CallbackArg()
	{
		_type = ArgumentType::Callback;
	}
}