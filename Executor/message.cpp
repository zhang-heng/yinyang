#include "message.h"

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
_"type":"lib",
_"id":12,
_"lib_path":"ExecutorTest.dll",
}

json
{
_"type":"fun",
_"id":12,
_"lib_id":12,
_"fun_name":"ExecutorTest",
}

json
{
_"type":"invoke", //调用函数
_"invoke_id":123,
_"lib_id":12,
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
					AsyncHandle(ReadMessage());
				}
			});
			_writer = new thread([=]()
			{

			});
			return true;
		}		
		return false;
	}

	Packet Message::ReadMessage()
	{
		pair<vector<char>, vector<char>> packet;
		packet.first = _io.read(GetNextSize());
		packet.second = _io.read(GetNextSize());
		return packet;
	}

	void Message::AsyncHandle(Packet packet)
	{
		Json::Reader reader;
		Json::Value json;
		if (!reader.parse(&*packet.first.data(), &*packet.first.data(), json))
			return;

		_handlers.push_back(thread([&json, &packet, this]()
		{
			auto id = this_thread::get_id();
			Handle(json, packet.second);
			DelAyncThreadByID(id);
		}));
	}

	void Message::Handle(Json::Value &json, vector<char> &payload)
	{
		auto type = json["type"].asString();

		if (type =="callback")
		{
		}
		else if (type =="invoke")
		{
			auto id = json["invoke_id"].asUInt();
		}
		else if (type =="fun")
		{
			auto id = json["id"].asUInt();
			auto lib_id = json["lib_id"].asUInt();
			auto fun_name = json["fun_name"].asString();
			if(_libs[lib_id])
			{
				auto fun_id = _libs[lib_id]->LoadFunction(fun_name);
				fun_id;//Todo...
			}
			throw exception ("errrrrr");
		}
		else if (type =="lib")
		{
			auto id = json["id"].asUInt();
			auto path = json["lib_path"].asString();
			auto added = find_if(_libs.begin(), _libs.end(),
				[path](pair<long, DllLibrary*> it){return it.second->GetPath() == path;});
			if (added == _libs.end())
			{
				auto lib = new DllLibrary(path);
				auto lib_id = lib->LoadDllLibrary();
				if(lib_id)
				{
					_libs.insert(pair<long, DllLibrary*>(lib_id, lib));
					lib_id;//Todo...
					return;
				}
			}else
			{
				added->first;//Todo...
				return;
			}
			throw exception ("errrrrr");
		}
		throw exception ("unknow error.");
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