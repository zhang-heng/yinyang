#include <windows.h>
#include "pipeIO.h"

#include <iostream>
#include <thread>
#include <map>

using namespace std;
using namespace yinyang;
/*
req_id=123          //������
func_name=do        //������
arg_1=0             //����ֵ����
arg_2=100*          //������������
<bytes 100>         //�������͵Ŀ�
arg_3=cb$           //�����ǻص�����
cb_id=124           //�ص������ı��
cb_1=0              //..
cb_2=3^             //�����n�������ǿ鳤������
cb_3=n              //��ֵ���� �����ڶ����������ͳ���
cb_4=100&           //�������� ����
cb_retrun=0         //��Ӧ����
func_return=0       //�Ƿ��з���ֵ
end

//ִ�з���ֵ
req_id=123
arg_1=0
arg_2=100*
<bytes>
arg_3=0
func_return=1

//�ص�
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

typedef string (*cb0)();
#define FUN0 []()->string{ return __FUNCTION__;}
int main()
{
	std::map<string, cb0> _cb_0;
	cb0 _cb0[] = {FUN0,FUN0,FUN0,FUN0};
	for(auto i = begin(_cb0); i != end(_cb0); i++)
	{
		_cb_0.insert(pair<string, cb0>((*i)(),*i));
	}
	return 0;
}

