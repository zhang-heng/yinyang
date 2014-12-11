#pragma once
#include <string>
#include <vector>
#include "callback_function.h"
#include "types.h"

namespace yinyang{
	class _function_;
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
		ValueArg();
		~ValueArg(void){};
	};

	class ReferArg :public FunArg
	{
	public:
		ReferArg();
		~ReferArg(void){};
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
}