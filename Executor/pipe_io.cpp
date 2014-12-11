#include "pipe_io.h"

namespace yinyang {
	using namespace std;

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

	PipeIO::byte_buffer PipeIO::read(long size)
	{
		throw new exception();
	} 

	PipeIO::~PipeIO(void)
	{
	}
}