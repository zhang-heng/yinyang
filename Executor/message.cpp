#include "message.h"
#include "json/json.h"

#include <mutex>

/*

//头描述
json
{
_n (4 bytes) : json length)
_<n>
_l (4 bytes) : payload length)
_<l>
}

//c# -> c++ (请求执行函数)
json
{
_"type":"invoke", //调用函数
_"invoke_id":123,
_"lib_path":"ExecutorTest.dll",
_"fun_name":"ExecutorTest",
_"return_type":"value"/"ref"/"return_size",
_"return_size":1024,
_"fun_args":["value":1,
_____________"refer":[0,100],
_____________"callback":{"callback_id":1234,
_________________________"block":"true", 
_________________________"return":"value"/"ref",
_________________________"defult_return":0,       //(block = false)
_________________________"fun_args":["value":1,
_____________________________________"refer":100,
_____________________________________"refer":"n_size",
_____________________________________"n_size":32
____________________________________]
_________________________}
_____________]"
}

//c++ -> c# (执行返回值)
json
{
_"type":"invoke",     //响应执行
_"invoke_id":123,
_"return_type":"value"/"ref"/"return_size",
_"return_size":[100,199],
_"fun_args":["value":1,
_____________"refer":[0,99]
_____________]"
}
json
{
_"type":"callback",     //响应回调
_"callback_id":1234,
_"return_type":"value"/"ref"/"return_size",
_"return_size":[100,199],
_"fun_args":["value":1,
_____________"refer":[0,99]
_____________]"
}
*/

namespace yinyang{
	using namespace std;

	Message::Message(string in, string out)
		:_io(in, out)
	{
	}

	Message::~Message()
	{
	}

	bool Message::Init()
	{
		if (_io.init_io_file())
		{
			_reader = new thread([=]()
			{ 
				while (true)
				{
					AsyncHanlde(ReadMessage());
				}
			});
			_writer = new thread([=]()
			{

			});
			return true;
		}		
		return false;
	}

	pair<vector<char>, vector<char>>  Message::ReadMessage()
	{
		pair<vector<char>, vector<char>> packet;
		packet.first = _io.read(GetNextSize());
		packet.second = _io.read(GetNextSize());
		return packet;
	}

	void Message::AsyncHanlde(pair<vector<char>, vector<char>> buff)
	{
		_handlers.push_back(thread([=]()
		{
			auto id = this_thread::get_id();
		}));
	}

	void Message::DelAyncThreadByID(thread::id id )
	{ 
		auto it = find_if(_handlers.begin(),_handlers.end(),
			[id](thread &t){return t.get_id() == id;});
		_handlers.erase(it);
	}

	long Message::GetNextSize()
	{
		long ret = 0; 
		auto chars = _io.read(4);
		auto pchars = chars.data();
		memcpy(&ret, pchars, 4);
		return ret;
	}
}