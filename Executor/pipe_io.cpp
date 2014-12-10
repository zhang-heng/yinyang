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
		return true;
	}

	bool PipeIO::write(byte_buffer buff)
	{
		return true;
	}

	bool PipeIO::write_line(std::string str)
	{
		return true;
	}

	bool PipeIO::read(byte_buffer buff)
	{
		return nullptr;
	}

	std::string PipeIO::read_line()
	{
		return nullptr;
	}

	PipeIO::~PipeIO(void)
	{
	}
}