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

	ValueArg::ValueArg(long value)
		:_value(value)
	{
		ValueArg();
	}

	ReferArg::ReferArg()
	{
		_type = ArgumentType::Refer;
	}

	ReferArg::ReferArg(pair<long,long> size)
		:_size(size)
	{
		ReferArg();
	}

	CallbackArg::CallbackArg()
	{
		_type = ArgumentType::Callback;
	}

	FunArgs::FunArgs(long count)
		:_count_args(count)
	{

	}

	FunArgs::~FunArgs(void)
	{

	}

	void FunArgs::AddArg(long value, bool feedback, long def)
	{

	}
	void FunArgs::AddArg(std::pair<long,long> refer, bool feedback, long def)
	{

	}
	void FunArgs::AddArg(FunArgs callback_arg)
	{

	}

	void FunArgs::AttachPayload(PipeIO::byte_buffer payload)
	{

	}
}