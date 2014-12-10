#include "pipe_io.h"
#include "dll_library.h"

#include "json/json.h"

#include <string>
#include <thread>
#include <vector>
#include <map>


namespace yinyang{
	typedef std::pair<std::vector<char>, std::vector<char>> Packet;

	class Message
	{
	public:
		Message(std::string in, std::string out);
		bool Init();
		~Message();
	private:
		Packet ReadMessage();
		long GetNextSize();
		void Handle(Json::Value &json, std::vector<char> &payload);
		void AsyncHandle(Packet packet);
		void DelAyncThreadByID(std::thread::id id);
		PipeIO _io;
		std::thread *_reader;
		std::thread *_writer;
		std::vector<std::thread> _handlers;

		std::map<long, DllLibrary*> _libs;
	};
}