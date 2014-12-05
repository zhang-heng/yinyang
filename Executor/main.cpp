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
arg_2=_100          //参数引用类型
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
arg_2=_100
<bytes>
arg_3=0
func_return=1
//回调
cb_id=124
cb_1=0
cb_2=_100
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
			io->read_line();
		}
	});

	thread send_thread([=]()
	{
		while (true)
		{
			io->read_line();
		}
	});
	recv_thread.join();
	send_thread.join();
	return 0;
}






#include <iostream>           // std::cout
#include <thread>             // std::thread, std::this_thread::yield
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable

std::mutex mtx;
std::condition_variable cv;

int cargo = 0;
bool shipment_available() {return cargo!=0;}

void consume (int n) {
	for (int i=0; i<n; ++i) {
		std::unique_lock<std::mutex> lck(mtx);
		cv.wait(lck,shipment_available);
		// consume:
		this_thread::sleep_for(chrono::seconds(1));
		std::cout << cargo << '\n';
		cargo=0;
	}
}

int main ()
{
	std::thread consumer_thread (consume,10);

	// produce 10 items when needed:
	for (int i=0; i<10; ++i) {
		while (shipment_available())
		{
			cout<<"a------------b" + i<<endl;
			std::this_thread::yield();
		}
		std::unique_lock<std::mutex> lck(mtx);
		cargo = i+1;
		cv.notify_one();
	}
	consumer_thread.join();
	return 0;
}
