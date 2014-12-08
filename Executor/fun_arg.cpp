#include "fun_arg.h"
#include <string>

namespace yinyang{
	using namespace std;

	//************************************
	// Class:    fun_arg 
	//************************************
	fun_arg * fun_arg::gen_new_arg(vector<vector<char>> args)
	{
		if (!args.size()) return nullptr;
		string fun_type(args[0].begin(), args[0].end());
		vector<string> s = split(fun_type, '=');
		if (!s.size()) return nullptr;
		const auto last_char = *s[1].rbegin();
		if (last_char == '*') 
			return refer_arg::gen_new_arg(args, s[1]);
		else if (last_char == '$') 
			return callback_arg::gen_new_arg(args);
		else 
			return value_arg::gen_new_arg(s[1]);
		return nullptr;
	}

	vector<string> fun_arg::split(string& str, char pattern)
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
	value_arg::value_arg(long v) : _value(v) { }

	value_arg::~value_arg() { }

	long value_arg::get_value()
	{
		return _value;
	}

	fun_arg * value_arg::gen_new_arg(string arg)
	{
		if(!arg.size()) return nullptr;
		for (auto c : arg) 
			if (c < '0' || c > '9')
				return nullptr; 
		return new value_arg(stol(arg));
	}

	//************************************
	// Class:    refer_arg 
	//************************************
	refer_arg::refer_arg(vector<vector<char>> args)
	{
		auto c = args[1].size();
		_refer_buffer = new char[c];
		memcpy(_refer_buffer, args[1].data(), c);
	}

	refer_arg::~refer_arg()
	{
		delete _refer_buffer;
	}

	long refer_arg::get_value()
	{
		return (long)(void*)_refer_buffer;
	}

	fun_arg * refer_arg::gen_new_arg( std::vector<std::vector<char>> args, string arg)
	{
		if(arg.size()<2) return nullptr;
		for (auto it = arg.rbegin() + 1; it != arg.rend(); it++) 
			if (*it < '0' || *it > '9')
				return nullptr;
		auto len = stol(string (arg.begin(), arg.end() - 1)); 
		if (args[1].size() != len) return nullptr;
		return new refer_arg(args);
	}

	//************************************
	// Class:    callback_arg 
	//************************************
	callback_arg::callback_arg(vector<vector<char>> args)
		: _callback(nullptr)
	{

	}

	callback_arg::~callback_arg()
	{

	}

	long callback_arg::get_value()
	{
		return 0;
	}

	fun_arg * callback_arg::gen_new_arg( std::vector<std::vector<char>> args )
	{
		return nullptr;
	}

	return_arg::~return_arg()
	{

	}

	fun_arg * return_arg::gen_new_arg( vector<vector<char>> args, string arg )
	{
		return nullptr;
	}

	return_arg::return_arg()
		:_block(false)
	{

	}

	bool return_arg::is_block()
	{
		return _block;
	}

}