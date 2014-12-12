#include "message.h"

#include <algorithm>
#include <mutex>
#include <cassert>

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
_"fun_argn":1
}

json
{
_"type":"invoke", //调用函数
_"req_id":111,
_"lib_id":111,
_"fun_id":111,
_"fun_args":[{"type":"value/refer","refer_size":1024,"feedback,":true},
_____________{"type":"value","value":1,"feedback":true},
_____________{"type":"refer","refer":[0,100],"feedback":true},
_____________{"type":"callback","callback":{"callback_id":1234,
____________________________________________"fun_args":[{"type":"value/refer","refer_size":1024,"default":1,"feedback":false}
________________________________________________________{"type":"value","feedback":true},
________________________________________________________{"type":"refer","size":1024,"feedback":true},
________________________________________________________{"type":"refer","size_arg":[4],"feedback":true},
________________________________________________________{"type":"value","feedback":true}
_______________________________________________________]
____________________________________________},"feedback":true}
____________]
}

json
{
_"type":"callback",     //响应执行
_"callback_id":111, 
_"fun_args":[{"type":"value","value":1},
_____________{"type":"feedbackless"},
_____________{"type":"feedbackless"}
____________]
}

//c++ -> c# (执行返回值)
json
{
_"type":"invoke",     //响应执行
_"req_id":111, 
_"fun_args":[{"type":"value","value":1},
_____________{"type":"refer","refer":[0,99]},
_____________{"type":"feedbackless"}
____________]
}

json
{
_"type":"callback",     //调用回调
_"req_id":111,
_"return_size":[100,199],
_"fun_args":[{"type":"feedbackless"},
_____________{"type":"refer","refer":[0,99]},
_____________{"type":"feedbackless"}
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

	long Message::GetNextSize()
	{
		long ret = 0;
		auto chars = _io.read(4);
		auto pchars = chars->data();
		memcpy(&ret, pchars, 4);
		return ret;
	}

	void Message::AsyncHandle(Packet packet)
	{
		Json::Reader reader;
		Json::Value json;
		assert(reader.parse(&*packet.first->data(), &*packet.first->data(), json));
		_handlers.push_back(thread([json, &packet, this]()
		{
			auto id = this_thread::get_id();
			Handle(json, packet.second);
			DelAyncThreadByID(id);
		}));
	}

	void Message::DelAyncThreadByID(thread::id id )
	{
		auto it = find_if(_handlers.begin(),_handlers.end(),
			[id](thread &t){return t.get_id() == id;});
		_handlers.erase(it);
	}

	void Message::Handle(Json::Value json, PipeIO::byte_buffer payload)
	{
		assert(json.size()>0);
		Json::Value respond;
		auto type = json["type"].asString();
		respond["type"] = type;
		if (type =="callback")
		{
			auto callback_id = json["callback_id"].asUInt();
			auto args = json["fun_args"];
			HandleReturnCallback(respond, callback_id, args, payload);
		}
		else if (type =="invoke")
		{
			auto req_id = json["req_id"].asUInt();
			auto lib_id = json["lib_id"].asUInt();
			auto fun_id = json["fun_id"].asUInt();
			auto args = json["fun_args"];
			HandleInvokeFunction(respond, req_id, lib_id, fun_id, args, payload);
		}
		else if (type =="load_fun")
		{
			auto req_id = json["req_id"].asUInt();
			auto lib_id = json["lib_id"].asUInt();
			auto fun_name = json["fun_name"].asString();
			auto fun_argn = json["fun_argn"].asUInt();
			HandleLoadFunction(respond, req_id, lib_id, fun_name, fun_argn);
		}
		else if (type =="load_lib")
		{
			auto req_id = json["req_id"].asUInt();
			auto path = json["lib_path"].asString();
			HandleLoadLibrary(respond, req_id, path);
		}
		else throw exception ("unknow error.");
	}

	void Message::HandleLoadLibrary(Json::Value &respond, long req_id, std::string path)
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

	void Message::HandleLoadFunction(Json::Value &respond, long req_id, long lib_id, std::string fun_name, long argn)
	{
		if(_libs[lib_id])
		{
			auto fun_id = _libs[lib_id]->LoadFunction(fun_name, argn);
			if(fun_id)
				fun_id;//Todo...
		}
		throw exception ("errrrrr");
	}

	void Message::HandleInvokeFunction(Json::Value &respond, long req_id, long lib_id, long fun_id,
		Json::Value args, PipeIO::byte_buffer payload)
	{
		if(!_libs[lib_id] || !_libs[lib_id]->HasFunction(fun_id))
			throw exception();
		auto handler = _libs[lib_id]->GetFunctionHanlder(fun_id);
		auto fun_args = ExtractArgs(args);
		fun_args.AttachPayload(payload);
		handler.Handle(fun_args);
		//Todo...
		throw exception();
	}

	void Message::HandleReturnCallback(Json::Value &respond, long callback_id, Json::Value args, PipeIO::byte_buffer payload)
	{
	}

	yinyang::FunArgs Message::ExtractArgs(Json::Value args)
	{
		auto args_count = args.size();
		assert(args_count>0);
		FunArgs fun_args(args_count);

		for (auto arg : args)
		{
			auto type = arg["type"].asString();
			auto feedback = arg["feedback"].asBool();
			auto def =  arg["default"].asUInt();

			if(type == "value")
			{
				auto v = arg["value"].asUInt();
				fun_args.AddArg(v, feedback, def);
			}else if(type == "refer")
			{
				auto refer_size = arg["refer_size"];
				pair<long,long> refer(refer_size[0].asUInt(), refer_size[1].asUInt());
				fun_args.AddArg(refer, feedback, def);
			}
			else if(type == "callback")
			{
				auto callback = arg["callback"];
				fun_args.AddArg(ExtractArgs(callback));
			}
		}
		return fun_args;
	}

}