#include <windows.h>

#include "pipe_io.h"
#include "message.h"

#include <iostream>
#include <thread>
#include <map>

using namespace std;
using namespace yinyang;

int main(int argc, char *argv[])
{
	DWORD dwMode = SetErrorMode(SEM_NOGPFAULTERRORBOX);
	SetErrorMode(dwMode | SEM_NOGPFAULTERRORBOX);

	if (argc!=3) return -1;
	Message msg(argv[1], argv[2]);
	if (msg.Init())
	{
		msg.WaitExit();
		return 0;
	} 
	cout<<"error init."<<endl;
	return -1;
}