#include <windows.h>

#include "pipe_io.h"
#include "callback_function.h"

#include <iostream>
#include <thread>
#include <map>


using namespace std;
using namespace yinyang;

/* c# -> c++ (请求执行函数)
req_id=123      //请求编号
func_name=do    //函数名
func_return=0   //是否有返回值

arg_1=0         //参数值类型

arg_2=100*      //参数引用类型
<bytes 100>     //引用类型的块

arg_3=124$      //参数是回调函数 回调函数的请求编号 
cb_retrun=0     //返回值
cb_1=0          //..
cb_2=3^         //代表第n个参数是块长度描述
cb_3=#          //数值类型 决定第二个引用类型长度
cb_4=100&       //引用类型 长度
cb_end		    

req_end         //请求结束
*/

/* c++ -> c# (执行返回值)
req_id=123
func_return=1
arg_1=0
arg_2=100*
<bytes>
arg_3=0
req_end         //请求结束

//回调
cb_id=124
cb_1=0
cb_2=100*
<bytes 100>
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

