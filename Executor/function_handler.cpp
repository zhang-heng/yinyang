#include "function_handler.h"

namespace yinyang{
	using namespace std;

	typedef long (*__fun0)();
	typedef long (*__fun1)(long __1);
	typedef long (*__fun2)(long __1, long __2);
	typedef long (*__fun3)(long __1, long __2, long __3);
	typedef long (*__fun4)(long __1, long __2, long __3, long __4); 
	typedef long (*__fun5)(long __1, long __2, long __3, long __4, long __5); 
	typedef long (*__fun6)(long __1, long __2, long __3, long __4, long __5, long __6); 
	typedef long (*__fun7)(long __1, long __2, long __3, long __4, long __5, long __6, long __7); 
	typedef long (*__fun8)(long __1, long __2, long __3, long __4, long __5, long __6, long __7, long __8); 
	typedef long (*__fun9)(long __1, long __2, long __3, long __4, long __5, long __6, long __7, long __8, long __9);  

	function_handler::function_handler(int h, vector<fun_arg> args) 
		:_handle(h), _args(args)
	{
	}

	function_handler::~function_handler(void)
	{
	}

	void function_handler::handle(void (*finish)(std::vector<fun_arg> args, long ret))
	{  
		auto call = [=]()
		{
			auto ret = call_method();
			finish(_args, ret);
		};
		thread _thread(call);
	}

	long function_handler::call_method()
	{
		long ret = 0;
		switch (_args.size())
		{
		case 0:
			ret = ((__fun0)_handle)();
			break;
		case 1:
			ret = ((__fun1)_handle)(_args[0].get_value());
			break;
		case 2:
			ret = ((__fun2)_handle)(_args[0].get_value(), _args[1].get_value());
			break;
		case 3:
			ret = ((__fun3)_handle)(_args[0].get_value(), _args[1].get_value(), _args[2].get_value());
			break;
		case 4:
			ret = ((__fun4)_handle)(_args[0].get_value(), _args[1].get_value(), _args[2].get_value(),
				_args[3].get_value());
			break;
		case 5:
			ret = ((__fun5)_handle)(_args[0].get_value(), _args[1].get_value(), _args[2].get_value(),
				_args[3].get_value(), _args[4].get_value());
			break;
		case 6:
			ret = ((__fun6)_handle)(_args[0].get_value(), _args[1].get_value(), _args[2].get_value(),
				_args[3].get_value(), _args[4].get_value(), _args[5].get_value());
			break;
		case 7:
			ret = ((__fun7)_handle)(_args[0].get_value(), _args[1].get_value(), _args[2].get_value(),
				_args[3].get_value(), _args[4].get_value(), _args[5].get_value(),
				_args[6].get_value());
			break;
		case 8:
			ret = ((__fun8)_handle)(_args[0].get_value(), _args[1].get_value(), _args[2].get_value(),
				_args[3].get_value(), _args[4].get_value(), _args[5].get_value(),
				_args[6].get_value(), _args[7].get_value());
			break;
		case 9:
			ret = ((__fun9)_handle)(_args[0].get_value(), _args[1].get_value(), _args[2].get_value(),
				_args[3].get_value(), _args[4].get_value(), _args[5].get_value(), 
				_args[6].get_value(), _args[7].get_value(), _args[8].get_value());
			break;
		default:
			break;
		}
		return ret;
	}

}