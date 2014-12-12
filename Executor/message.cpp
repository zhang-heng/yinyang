#include "message.h"

#include <algorithm>
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
_"type":"load_lib",
_"req_id":111,
_"lib_path":"ExecutorTest.dll",
}

json
{
_"type":"load_fun",
_"req_id":111,
_"lib_id":111,
_"fun_name":"ExecutorTest",
}

json
{
_"type":"invoke", //���ú���
_"req_id":111,
_"lib_id":111,
_"fun_id":111,
_"fun_args":[{"type":"value/refer","refer_size":1024,"need":true},
_____________{"type":"value","value":1,"need":true},
_____________{"type":"refer","refer":[0,100],"need":true},
_____________{"type":"callback","callback":{"callback_id":1234,
____________________________________________"fun_args":[{"type":"value/refer","refer_size":1024,"default":1,"need":false}
________________________________________________________{"type":"value","need":true},
________________________________________________________{"type":"refer","size":1024,"need":true},
________________________________________________________{"type":"refer","size_arg":[4],"need":true},
________________________________________________________{"type":"value","need":true}
_______________________________________________________]
____________________________________________},"need":true}
____________]
}

json
{
_"type":"callback",     //��Ӧִ��
_"callback_id":111, 
_"fun_args":[{"type":"value","value":1},
_____________{"type":"needless"},
_____________{"type":"needless"}
____________]
}

//c++ -> c# (ִ�з���ֵ)
json
{
_"type":"invoke",     //��Ӧִ��
_"req_id":111, 
_"fun_args":[{"type":"value","value":1},
_____________{"type":"refer","refer":[0,99]},
_____________{"type":"needless"}
____________]
}

json
{
_"type":"callback",     //���ûص�
_"req_id":111,
_"return_size":[100,199],
_"fun_args":[{"type":"needless"},
_____________{"type":"refer","refer":[0,99]},
_____________{"type":"needless"}
____________]
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
			_reading = new thread([=]()
			{
				while (true)
				{
					AsyncHandle(ReadMessage());
				}
			});
			_writting = new thread([=]()
			{

			});
			return true;
		}
		return false;
	}

	void Message::WaitExit()
	{
		_reading->join();
		_writting->join();
	}

	Message::Packet Message::ReadMessage()
	{
		pair<PipeIO::byte_buffer, PipeIO::byte_buffer> packet;
		packet.first = _io.read(GetNextSize());
		packet.second = _io.read(GetNextSize());
		return packet;
	}

	void Message::DelAyncThreadByID(thread::id id )
	{ 
		auto it = find_if(_handlers.begin(),_handlers.end(),
			[id](thread &t){return t.get_id() == id;});
		_handlers.erase(it);
	}

	void Message::AsyncHandle(Packet packet)
	{
		Json::Reader reader;
		Json::Value json;
		if (!reader.parse(&*packet.first->data(), &*packet.first->data(), json))
			return;

		_handlers.push_back(thread([json, &packet, this]()
		{
			auto id = this_thread::get_id();
			Handle(json, packet.second);
			DelAyncThreadByID(id);
		}));
	}

	void Message::Handle(Json::Value json, PipeIO::byte_buffer payload)
	{
		auto type = json["type"].asString();
		if (type =="callback")
		{
			auto callback_id = json["callback_id"].asUInt();
			auto args = json["fun_args"];
			HandleReturnCallback(callback_id, args, payload);
		}
		else if (type =="invoke")
		{
			auto req_id = json["req_id"].asUInt();
			auto lib_id = json["lib_id"].asUInt();
			auto fun_id = json["fun_id"].asUInt();
			auto args = json["fun_args"];
			HandleInvokeFunction(req_id, lib_id, fun_id, args, payload);
		}
		else if (type =="load_fun")
		{
			auto req_id = json["req_id"].asUInt();
			auto lib_id = json["lib_id"].asUInt();
			auto fun_name = json["fun_name"].asString();
			HandleLoadFunction(req_id, lib_id, fun_name);
		}
		else if (type =="load_lib")
		{
			auto req_id = json["req_id"].asUInt();
			auto path = json["lib_path"].asString();
			HandleLoadLibrary(req_id, path);
		}
		else throw exception ("unknow error.");
	}

	long Message::GetNextSize()
	{
		long ret = 0; 
		auto chars = _io.read(4);
		auto pchars = chars->data();
		memcpy(&ret, pchars, 4);
		return ret;
	}

	void Message::HandleLoadLibrary(long req_id, std::string path)
	{
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

	void Message::HandleLoadFunction( long req_id, long lib_id, std::string fun_name )
	{
		if(_libs[lib_id])
		{
			auto fun_id = _libs[lib_id]->LoadFunction(fun_name);
			fun_id;//Todo...
		}
		throw exception ("errrrrr");
	}

	void Message::HandleInvokeFunction(long req_id, long lib_id, long fun_id,
		Json::Value args, PipeIO::byte_buffer payload)
	{
	}

	void Message::HandleReturnCallback(long callback_id, Json::Value args, PipeIO::byte_buffer payload)
	{
	}
}