#include "pipe_io.h"
#include <string>
#include <thread>
#include <vector>

namespace yinyang{
	class Message
	{
	public:
		Message(std::string in, std::string out);
		bool Init();
		~Message();
	private:
		std::pair<std::vector<char>, std::vector<char>>  ReadMessage();
		long GetNextSize();
		void AsyncHanlde(std::pair<std::vector<char>, std::vector<char>> buff);
		void DelAyncThreadByID(std::thread::id id);
		PipeIO _io;
		std::thread *_reader;
		std::thread *_writer;
		std::vector<std::thread> _handlers;
	};
}