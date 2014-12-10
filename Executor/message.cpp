#include "message.h"
#include "json/json.h"

#include <mutex>

/*

//ͷ����
json
{
_n (4 bytes) : json length)
_<n>
_l (4 bytes) : payload length)
_<l>
}

//c# -> c++ (����ִ�к���)
json
{
_"type":"invoke", //���ú���
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

//c++ -> c# (ִ�з���ֵ)
json
{
_"type":"invoke",     //��Ӧִ��
_"invoke_id":123,
_"return_type":"value"/"ref"/"return_size",
_"return_size":[100,199],
_"fun_args":["value":1,
_____________"refer":[0,99]
_____________]"
}
json
{
_"type":"callback",     //��Ӧ�ص�
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