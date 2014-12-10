#include <windows.h>

#include "pipe_io.h"
#include "callback_function.h"

#include <iostream>
#include <thread>
#include <map>


using namespace std;
using namespace yinyang;

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
	return 0;
}

int main()
{  
	CallbackFunction::init_callbacks();
	return 0;
}

