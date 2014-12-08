#pragma once
#include <vector>
#include <string>
#include <map> 

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

namespace yinyang{
	class fun_arg;

	class callback_function
	{
	public:
		~callback_function(void);
	private:
		const int _argn;
		const std::string _lambda_fun_name;
		const long _fun_address;

		bool _used;
		std::string _call_fun_name;
		std::vector<fun_arg*> _args;
		long _invoker_id;
		callback_function(std::string name, long l_address, int argn);
		long call_fun(long __1 = 0, long __2 = 0, long __3 = 0, long __4 = 0, long __5 = 0,
			long __6 = 0, long __7 = 0, long __8 = 0, long __9 = 0);
		void creat_handler(std::vector<fun_arg*> args);

		/*static*/
	public:
		static void init_callbacks();
		static callback_function* creat_callback_funciton(std::vector<std::vector<char>> args);
	private:  
		static std::map<std::string, callback_function*> _callbacks;
		static bool inited;
	}; 
}