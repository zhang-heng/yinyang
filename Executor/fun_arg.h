#pragma once
#include <string>

namespace yinyang{
	class fun_arg
	{
	public:
		fun_arg();
		~fun_arg(void);
	protected:
	};

	class value_arg :public fun_arg
	{
	public:
		value_arg(std::string d);
	};

	class refer_arg :public fun_arg
	{
	public:
		refer_arg(std::string d);
	};

	class callback_arg :public fun_arg
	{
	public:
		callback_arg(std::string d);
	};
}