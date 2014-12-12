#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <memory>

namespace yinyang
{
	class PipeIO
	{
	public:
		typedef std::shared_ptr<std::vector<char>> byte_buffer;
		PipeIO(std::string in, std::string out);
		~PipeIO(void);
		bool init_io_file();
		bool write(byte_buffer buff);
		byte_buffer read(long size);
	private:
		std::string _in_file_path;
		std::string _out_file_path;

		std::ifstream* _reader;
		std::ofstream* _writer;
	}; 
}