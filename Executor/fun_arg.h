#pragma once
#include <string>
#include <vector>
#include "callback_function.h"

namespace yinyang{
	class fun_arg
	{
	public:
		fun_arg(){};
		~fun_arg(void){};
		virtual long get_value(){return 0;};
		static fun_arg * gen_new_arg(std::vector<std::vector<char>> args);
		static std::vector<std::string> split(std::string& str, char pattern);
	};

	class value_arg :public fun_arg
	{
	public:
		~value_arg(void);
		long get_value(); 
		static fun_arg * gen_new_arg(std::string arg);
	private:
		value_arg(long v);
		long _value;
	};

	class refer_arg :public fun_arg
	{
	public:
		~refer_arg(void);
		long get_value(); 
		static fun_arg * gen_new_arg(std::vector<std::vector<char>> args, std::string arg);
	private:
		refer_arg(std::vector<std::vector<char>> args);
		char* _refer_buffer;
	};

#include "callback_function.h"
	class callback_arg :public fun_arg
	{
	public:
		~callback_arg(void);
		long get_value(); 
		static fun_arg * gen_new_arg(std::vector<std::vector<char>> args);
	private:
		callback_arg(std::vector<std::vector<char>> args);
		callback_function *_callback;
	};
}