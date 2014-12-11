#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include <queue>

#include "block_queue.h"


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

		std::shared_ptr<std::ifstream> _reader;
		std::shared_ptr<std::ofstream> _writer;
	}; 
}