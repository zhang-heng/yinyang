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
		std::vector<char> ReadMessage();
		void AsyncHanlde(std::vector<char> buff);
		void DelAyncThreadByID(std::thread::id id);
		PipeIO _io;
		std::thread *_reader;
		std::thread *_writer;
		std::vector<std::thread> _handlers;
	};
}