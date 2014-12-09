#pragma once
#include <string>
#include <vector>
#include "callback_function.h"

namespace yinyang{
	class FunArg
	{
	public:
		FunArg(){};
		~FunArg(void){};
		virtual long get_value(){return 0;};
		virtual void handle(long v){};
		static FunArg * gen_new_arg(std::vector<std::vector<char>> args);
		static std::vector<std::string> split(std::string& str, char pattern);
	};

	class ReturnArg :public FunArg
	{
	public:
		~ReturnArg(void);
		bool is_block();
		static FunArg * gen_new_arg(std::vector<std::vector<char>> args, std::string arg);
	private:
		ReturnArg(void); 
		bool _block;
	};

	class ValueArg :public FunArg
	{
	public:
		~ValueArg(void);
		long get_value(); 
		static FunArg * gen_new_arg(std::string arg);
	private:
		ValueArg(long v);
		long _value;
	};

	class ReferArg :public FunArg
	{
	public:
		~ReferArg(void);
		long get_value(); 
		static FunArg * gen_new_arg(std::vector<std::vector<char>> args, std::string arg);
	private:
		ReferArg(std::vector<std::vector<char>> args);
		char* _refer_buffer;
	};

#include "callback_function.h"
	class CallbackArg :public FunArg
	{
	public:
		~CallbackArg(void);
		long get_value(); 
		static FunArg * gen_new_arg(std::vector<std::vector<char>> args);
	private:
		CallbackArg(std::vector<std::vector<char>> args);
		CallbackFunction *_callback;
	};
}