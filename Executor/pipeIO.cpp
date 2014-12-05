#include "pipeIO.h"

namespace yinyang {
	using namespace std;

	block_queue<byte_buffer> _send_queue;
	block_queue<byte_buffer> _recv_queue;

	pipeIO::pipeIO(string in, string out):
		_in_file_path(in), _out_file_path(out)
	{
	}

	bool pipeIO::init_io_file()
	{
		return true;
	}

	bool pipeIO::write(byte_buffer buff)
	{
		return true;
	}

	bool pipeIO::write_line(std::string str)
	{
		return true;
	}

	bool pipeIO::read(byte_buffer buff)
	{
		return nullptr;
	}

	std::string pipeIO::read_line()
	{
		return nullptr;
	}

	pipeIO::~pipeIO(void)
	{
	}
}