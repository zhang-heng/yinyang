#include <windows.h>
#include "pipeIO.h"

#include <iostream>
#include <thread>

using namespace std;

/*
req_id=123          //������
func_name=do        //������
arg_1=0             //����ֵ����
arg_2=_100          //������������
<bytes>             //�������͵Ŀ�
arg_3=cb            //�����ǻص�����
cb_id=124           //�ص������ı��
cb_1=0              //..
cb_2=_3             //����n�������ǿ鳤������
cb_3=n
cb_retrun=0         //��Ӧ����
func_return=0       //�Ƿ��з���ֵ
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