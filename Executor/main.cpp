#include <windows.h>
#include "pipeIO.h"

#include <iostream>
#include <thread>

using namespace std;
using namespace yinyang;
/*
req_id=123          //请求编号
func_name=do        //函数名
arg_1=0             //参数值类型
arg_2=100_          //参数引用类型
<bytes 100>         //引用类型的块
arg_3=cb            //参数是回调函数
cb_id=124           //回调函数的编号
cb_1=0              //..
cb_2=_a3            //代表第n个参数是块长度描述
cb_3=n
cb_retrun=0         //响应返回
func_return=0       //是否有返回值
end

//执行返回值
req_id=123
arg_1=0
arg_2=100_
<bytes>
arg_3=0
func_return=1
//回调
cb_id=124
cb_1=0
cb_2=100_
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
	pipeIO *io = new pipeIO(argv[1], argv[2]);
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
	return 0;
}