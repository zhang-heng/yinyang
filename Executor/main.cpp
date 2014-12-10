#include <windows.h>

#include "pipe_io.h"
#include "callback_function.h"

#include <iostream>
#include <thread>
#include <map>


using namespace std;
using namespace yinyang;

/* c# -> c++ (请求执行函数)
/*json 描述
{
_<json>
_\n
_l (4 bytes) : payload length)
_<l>
}
json
{
_"type"="invoke", //调用函数
_"invoke_id"=123,
_"lib_path"="ExecutorTest.dll",
_"fun_name"="ExecutorTest",
_"return_type"="value"/"ref"/"return_size",
_"return_size"=1024,
_"fun_args"=["value":1,
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

/* c++ -> c# (执行返回值)
json
{
_"type"="invoke",     //响应执行
_"invoke_id"=123,
_"return_type"="value"/"ref"/"return_size",
_"return_size"=[100,199],
_"fun_args"=["value":1,
_____________"refer":[0,99]
_____________]"
}

json
{
_"type"="callback",     //响应回调
_"callback_id"=1234,
_"return_type"="value"/"ref"/"return_size",
_"return_size"=[100,199],
_"fun_args"=["value":1,
_____________"refer":[0,99]
_____________]"
}
*/

int mainx(int argc, char *argv[])
{
	DWORD dwMode = SetErrorMode(SEM_NOGPFAULTERRORBOX);
	SetErrorMode(dwMode | SEM_NOGPFAULTERRORBOX);

	if (argc < 3)
	{
		cout<<"parameters of i/o file name not found!"<<endl; 
	}
	cout<<argv[1]<<endl;
	cout<<argv[2]<<endl;
	PipeIO *io = new PipeIO(argv[1], argv[2]);
	if (!io->init_io_file())
	{
		cout<<"error to init I/O"<<endl;
		return 0;
	}

	thread recv_thread([=]()
	{
		while (true)
		{
			auto line = io->read_line();
			_recv_queue.push(byte_buffer(line.begin(), line.end()));
			auto it = line.rbegin();
			if (*it == '_')
			{
				string n("");
				while (*(++it) != '=') n.insert(n.begin(),*it); 
				auto len = stol(n);
				auto buff = byte_buffer(len);
				io->read(buff);
				_recv_queue.push(buff);
			}
		}
	});

	thread send_thread([=]()
	{
		while (true)
		{
			io->write(_send_queue.pop());
		}
	});
	recv_thread.join();
	send_thread.join();
	return 0;
}

int main()
{
	CallbackFunction::init_callbacks();
	return 0;
}

