#include "pipe_io.h"

namespace yinyang {
	using namespace std;

	BlockQueue<byte_buffer> _send_queue;
	BlockQueue<byte_buffer> _recv_queue;

	PipeIO::PipeIO(string in, string out):
		_in_file_path(in), _out_file_path(out)
	{
	}

	bool PipeIO::init_io_file()
	{
		throw new exception();
	}

	bool PipeIO::write(byte_buffer buff)
	{
		throw new exception();
	}

	bool PipeIO::write_line(std::string str)
	{
		throw new exception();
	}

	byte_buffer PipeIO::read(long size)
	{
		throw new exception();
	}

	std::string PipeIO::read_line()
	{
		throw new exception();
	}

	PipeIO::~PipeIO(void)
	{
	}
}