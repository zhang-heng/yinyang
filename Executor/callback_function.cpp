#include "callback_function.h"
#include "fun_arg.h"

#define FUN0 []()->long{\
	if (!inited) return (long)__FUNCTION__;else return _callbacks[__FUNCTION__]->call_fun();} 
#define FUN1 [](long __1)->long{\
	if (!inited) return (long)__FUNCTION__;else return _callbacks[__FUNCTION__]->call_fun(__1);} 
#define FUN2 [](long __1, long __2)->long{\
	if (!inited) return (long)__FUNCTION__;else return _callbacks[__FUNCTION__]->call_fun(__1,__2);} 
#define FUN3 [](long __1, long __2, long __3)->long{\
	if (!inited) return (long)__FUNCTION__;else return _callbacks[__FUNCTION__]->call_fun(__1,__2,__3);} 
#define FUN4 [](long __1, long __2, long __3, long __4) ->long{\
	if (!inited) return (long)__FUNCTION__;else return _callbacks[__FUNCTION__]->call_fun(__1,__2,__3,__4);} 
#define FUN5 [](long __1, long __2, long __3, long __4, long __5) ->long{\
	if (!inited) return (long)__FUNCTION__;else return _callbacks[__FUNCTION__]->call_fun(__1,__2,__3,__4,__5);} 
#define FUN6 [](long __1, long __2, long __3, long __4, long __5, long __6) ->long{\
	if (!inited) return (long)__FUNCTION__;else return _callbacks[__FUNCTION__]->call_fun(__1,__2,__3,__4,__5,__6);} 
#define FUN7 [](long __1, long __2, long __3, long __4, long __5, long __6, long __7) ->long{\
	if (!inited) return (long)__FUNCTION__;else return _callbacks[__FUNCTION__]->call_fun(__1,__2,__3,__4,__5,__6,__7);} 
#define FUN8 [](long __1, long __2, long __3, long __4, long __5, long __6, long __7, long __8) ->long{\
	if (!inited) return (long)__FUNCTION__;else return _callbacks[__FUNCTION__]->call_fun(__1,__2,__3,__4,__5,__6,__7,__8);} 
#define FUN9 [](long __1, long __2, long __3, long __4, long __5, long __6, long __7, long __8, long __9)->long{\
	if (!inited) return (long)__FUNCTION__;else return _callbacks[__FUNCTION__]->call_fun(__1,__2,__3,__4,__5,__6,__7,__8,__9);}  

namespace yinyang{
	using namespace std;

	/*static*/
	void CallbackFunction::init_callbacks()
	{
		if (!inited)
		{
			__fun0 cb0[] = {FUN0,FUN0,FUN0,FUN0,FUN0,FUN0,FUN0,FUN0,FUN0,FUN0,FUN0,FUN0,FUN0,FUN0,FUN0,FUN0,FUN0,FUN0,FUN0,FUN0};
			__fun1 cb1[] = {FUN1,FUN1,FUN1,FUN1,FUN1,FUN1,FUN1,FUN1,FUN1,FUN1,FUN1,FUN1,FUN1,FUN1,FUN1,FUN1,FUN1,FUN1,FUN1,FUN1};
			__fun2 cb2[] = {FUN2,FUN2,FUN2,FUN2,FUN2,FUN2,FUN2,FUN2,FUN2,FUN2,FUN2,FUN2,FUN2,FUN2,FUN2,FUN2,FUN2,FUN2,FUN2,FUN2};
			__fun3 cb3[] = {FUN3,FUN3,FUN3,FUN3,FUN3,FUN3,FUN3,FUN3,FUN3,FUN3,FUN3,FUN3,FUN3,FUN3,FUN3,FUN3,FUN3,FUN3,FUN3,FUN3};
			__fun4 cb4[] = {FUN4,FUN4,FUN4,FUN4,FUN4,FUN4,FUN4,FUN4,FUN4,FUN4,FUN4,FUN4,FUN4,FUN4,FUN4,FUN4,FUN4,FUN4,FUN4,FUN4};
			__fun5 cb5[] = {FUN5,FUN5,FUN5,FUN5,FUN5,FUN5,FUN5,FUN5,FUN5,FUN5,FUN5,FUN5,FUN5,FUN5,FUN5,FUN5,FUN5,FUN5,FUN5,FUN5};
			__fun6 cb6[] = {FUN6,FUN6,FUN6,FUN6,FUN6,FUN6,FUN6,FUN6,FUN6,FUN6,FUN6,FUN6,FUN6,FUN6,FUN6,FUN6,FUN6,FUN6,FUN6,FUN6};
			__fun7 cb7[] = {FUN7,FUN7,FUN7,FUN7,FUN7,FUN7,FUN7,FUN7,FUN7,FUN7,FUN7,FUN7,FUN7,FUN7,FUN7,FUN7,FUN7,FUN7,FUN7,FUN7};
			__fun8 cb8[] = {FUN8,FUN8,FUN8,FUN8,FUN8,FUN8,FUN8,FUN8,FUN8,FUN8,FUN8,FUN8,FUN8,FUN8,FUN8,FUN8,FUN8,FUN8,FUN8,FUN8};
			__fun9 cb9[] = {FUN9,FUN9,FUN9,FUN9,FUN9,FUN9,FUN9,FUN9,FUN9,FUN9,FUN9,FUN9,FUN9,FUN9,FUN9,FUN9,FUN9,FUN9,FUN9,FUN9};
			for(auto i = begin(cb0); i != end(cb0); i++) new CallbackFunction((char*)(*i)(),(long)i,0);
			for(auto i = begin(cb1); i != end(cb1); i++) new CallbackFunction((char*)(*i)(0),(long)i,1);
			for(auto i = begin(cb2); i != end(cb2); i++) new CallbackFunction((char*)(*i)(0,0),(long)i,2);
			for(auto i = begin(cb3); i != end(cb3); i++) new CallbackFunction((char*)(*i)(0,0,0),(long)i,3);
			for(auto i = begin(cb4); i != end(cb4); i++) new CallbackFunction((char*)(*i)(0,0,0,0),(long)i,4);
			for(auto i = begin(cb5); i != end(cb5); i++) new CallbackFunction((char*)(*i)(0,0,0,0,0),(long)i,5);
			for(auto i = begin(cb6); i != end(cb6); i++) new CallbackFunction((char*)(*i)(0,0,0,0,0,0),(long)i,6);
			for(auto i = begin(cb7); i != end(cb7); i++) new CallbackFunction((char*)(*i)(0,0,0,0,0,0,0),(long)i,7);
			for(auto i = begin(cb8); i != end(cb8); i++) new CallbackFunction((char*)(*i)(0,0,0,0,0,0,0,0),(long)i,8);
			for(auto i = begin(cb9); i != end(cb9); i++) new CallbackFunction((char*)(*i)(0,0,0,0,0,0,0,0,0),(long)i,9);
			inited = true;
		}
	}
	/*static*/
	CallbackFunction* CallbackFunction::creat_callback_funciton(vector<vector<char>> args)
	{
		return nullptr;
	}
	/*static*/
	map<string, CallbackFunction*> CallbackFunction::_callbacks;
	/*static*/
	bool CallbackFunction::inited = false;

	CallbackFunction::CallbackFunction(string name, long l_address, int argn)
		:_used(false), _lambda_fun_name(name), _fun_address(l_address), _argn(argn)
	{
		_callbacks.insert(pair<string, CallbackFunction*>(_lambda_fun_name, this));
	}

	void CallbackFunction::creat_handler(vector<FunArg*> args) 
	{
		auto argn = _args.size() - 1;
		_used = true;
		string fun_name = "";
	}

	CallbackFunction::~CallbackFunction(void)
	{

	}

	long CallbackFunction::call_fun(long __1, long __2, long __3, long __4, long __5, long __6, long __7, long __8, long __9)
	{ 
		bool block_wait_result = false; 
		long ret = 0;
		for (auto i = _args.begin(); i!= _args.end(); i++)
		{  
			//return value(block or no block handle)
			//if (i == _args.begin() + 0) block_wait_result = ((ReturnArg*)(*i))->is_block();
			//if (i == _args.begin() + 1) (*i)->handle(__1);
			//if (i == _args.begin() + 2) (*i)->handle(__2);
			//if (i == _args.begin() + 3) (*i)->handle(__3);
			//if (i == _args.begin() + 4) (*i)->handle(__4);
			//if (i == _args.begin() + 5) (*i)->handle(__5);
			//if (i == _args.begin() + 6) (*i)->handle(__6);
			//if (i == _args.begin() + 7) (*i)->handle(__7);
			//if (i == _args.begin() + 8) (*i)->handle(__8);
			//if (i == _args.begin() + 9) (*i)->handle(__9);
		}
		return 0;//_args[0]->get_value();
	}
}