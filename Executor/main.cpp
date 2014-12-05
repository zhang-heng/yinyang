#include <windows.h>
#include "pipeIO.h"

#include <iostream>
#include <thread>

using namespace std;

/*
req_id=123          //请求编号
func_name=do        //函数名
arg_1=0             //参数值类型
arg_2=_100          //参数引用类型
<bytes>             //引用类型的块
arg_3=cb            //参数是回调函数
cb_id=124           //回调函数的编号
cb_1=0              //..
cb_2=_3             //代表n个参数是块长度描述
cb_3=n
cb_retrun=0         //响应返回
func_return=0       //是否有返回值
end


return_id=123
v=0
v=_100
<bytes>

*/

int main(int argc, char *argv[])
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

	});
	thread send_thread([=]()
	{

	});
	recv_thread.join();
	send_thread.join();
	return 0;
}