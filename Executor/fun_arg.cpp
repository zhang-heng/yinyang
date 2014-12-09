#include "fun_arg.h"
#include <string>

namespace yinyang{
	using namespace std;

	//************************************
	// Class:    fun_arg 
	//************************************
	FunArg * FunArg::gen_new_arg(vector<vector<char>> args)
	{
		if (!args.size()) return nullptr;
		string fun_type(args[0].begin(), args[0].end());
		vector<string> s = split(fun_type, '=');
		if (!s.size()) return nullptr;
		const auto last_char = *s[1].rbegin();
		if (last_char == '*') 
			return ReferArg::gen_new_arg(args, s[1]);
		else if (last_char == '$') 
			return CallbackArg::gen_new_arg(args);
		else 
			return ValueArg::gen_new_arg(s[1]);
		return nullptr;
	}

	vector<string> FunArg::split(string& str, char pattern)
	{
		auto pos = str.find(pattern);
		vector<string> ret;
		if (pos != string::npos)
		{
			ret.push_back(string(str.begin(), str.begin()+ pos));
			ret.push_back(string(str.begin() + pos + 1, str.end()));
		}
		return ret;
	}


	//************************************
	// Class:    value_arg 
	//************************************
	ValueArg::ValueArg(long v) : _value(v) { }

	ValueArg::~ValueArg() { }

	long ValueArg::get_value()
	{
		return _value;
	}

	FunArg * ValueArg::gen_new_arg(string arg)
	{
		if(!arg.size()) return nullptr;
		for (auto c : arg) 
			if (c < '0' || c > '9')
				return nullptr; 
		return new ValueArg(stol(arg));
	}

	//************************************
	// Class:    refer_arg 
	//************************************
	ReferArg::ReferArg(vector<vector<char>> args)
	{
		auto c = args[1].size();
		_refer_buffer = new char[c];
		memcpy(_refer_buffer, args[1].data(), c);
	}

	ReferArg::~ReferArg()
	{
		delete _refer_buffer;
	}

	long ReferArg::get_value()
	{
		return (long)(void*)_refer_buffer;
	}

	FunArg * ReferArg::gen_new_arg( std::vector<std::vector<char>> args, string arg)
	{
		if(arg.size()<2) return nullptr;
		for (auto it = arg.rbegin() + 1; it != arg.rend(); it++) 
			if (*it < '0' || *it > '9')
				return nullptr;
		auto len = stol(string (arg.begin(), arg.end() - 1)); 
		if (args[1].size() != len) return nullptr;
		return new ReferArg(args);
	}

	//************************************
	// Class:    callback_arg 
	//************************************
	CallbackArg::CallbackArg(vector<vector<char>> args)
		: _callback(nullptr)
	{

	}

	CallbackArg::~CallbackArg()
	{

	}

	long CallbackArg::get_value()
	{
		return 0;
	}

	FunArg * CallbackArg::gen_new_arg( std::vector<std::vector<char>> args )
	{
		return nullptr;
	}

	ReturnArg::~ReturnArg()
	{

	}

	FunArg * ReturnArg::gen_new_arg( vector<vector<char>> args, string arg )
	{
		return nullptr;
	}

	ReturnArg::ReturnArg()
		:_block(false)
	{

	}

	bool ReturnArg::is_block()
	{
		return _block;
	}

}