#include "pipe_io.h"

namespace yinyang {
	using namespace std;

	PipeIO::PipeIO(string in, string out):
		_in_file_path(in), _out_file_path(out),
		_reader(nullptr), _writer(nullptr) {}

	bool PipeIO::init_io_file()
	{
		if(_reader || _writer)
			return false;
		try
		{
			_reader =  new ifstream(_in_file_path, ios::binary);
			_writer =  new ofstream(_out_file_path, ios::binary);
		}
		catch (...) { return false;}
		return true;
	}

	bool PipeIO::write(byte_buffer buff)
	{
		_writer->write(buff->data(), buff->size());
		if (_writer->fail()) return false;
		return true ;
	}

	PipeIO::byte_buffer PipeIO::read(long size)
	{
		byte_buffer buffer = make_shared<vector<char>>(size);
		_reader->read(buffer->data(),size);
		if (_reader->fail()) throw exception();
		return buffer;
	}

	PipeIO::~PipeIO(void)
	{
		_writer->close();
		_writer = nullptr;
		_reader->close();
		_reader = nullptr;
	}
}