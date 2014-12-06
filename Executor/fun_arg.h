#pragma once
#include <string>

namespace yinyang{
	class fun_arg
	{
	public:
		fun_arg();
		~fun_arg(void);
		virtual long get_value(){return 0;};
	protected:
	};

	class value_arg :public fun_arg
	{
	public:
		value_arg(std::string d);
		~value_arg(void);
		long get_value();
	};

	class refer_arg :public fun_arg
	{
	public:
		refer_arg(std::string d);
		~refer_arg(void);
		long get_value();
	private:
	};

	class callback_arg :public fun_arg
	{
	public:
		callback_arg(std::string d);
		~callback_arg(void);
		long get_value();
	};
}