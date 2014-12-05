#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include <queue>

#include "block_queue.h"

#define byte_buffer std::vector<char>

namespace yinyang
{
	class pipeIO
	{
	public:
		pipeIO(std::string in, std::string out);
		~pipeIO(void);
		bool init_io_file();
		bool write(byte_buffer buff); 
		bool write_line(std::string str);
		bool read(byte_buffer buff);
		std::string read_line();
	private:
		std::string _in_file_path;
		std::string _out_file_path;

		std::shared_ptr<std::ifstream> _reader;
		std::shared_ptr<std::ofstream> _writer;
	};

	extern block_queue<byte_buffer> _send_queue;
	extern block_queue<byte_buffer> _recv_queue;
}