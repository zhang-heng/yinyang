#pragma once
#include <string>
#include <vector>
#include "callback_function.h"
#include "types.h"
#include "pipe_io.h"

namespace yinyang{
	class FunArg
	{
	public:
		FunArg(){};
		~FunArg(void){};
		ArgumentType  GetType() {return _type;};
	protected:
		ArgumentType _type;
	};

	class ValueArg :public FunArg
	{
	public:
		ValueArg(long value);
		~ValueArg(void){};
	private:
		long _value;
		ValueArg();
	};

	class ReferArg :public FunArg
	{
	public:
		ReferArg::ReferArg(std::pair<long,long> size);
		~ReferArg(void){};
	private:
		std::pair<long,long> _size;
		ReferArg();
	};

	class ReturnArg :public FunArg
	{
	public:
		ReturnArg();
		~ReturnArg(void){};

	private:
		bool _block;
		FunArg _arg_type;
	};

#include "callback_function.h"
	class CallbackArg :public FunArg
	{
	public:
		CallbackArg();
		~CallbackArg(){};
	};

	class FunArgs
	{
	public:
		FunArgs(long count);
		~FunArgs(void);
		void AddArg(long value, bool feedback, long def);
		void AddArg(std::pair<long,long> refer, bool feedback, long def);
		void AddArg(FunArgs callback_arg);
		void AttachPayload(PipeIO::byte_buffer payload);
	private:
		const long _count_args;
	};
}