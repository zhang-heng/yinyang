#include "pipe_io.h"
#include "dll_library.h"
#include "types.h"
#include "fun_arg.h"

#include "json/json.h"

#include <string>
#include <thread>
#include <vector>
#include <map>


namespace yinyang{

	class Message
	{
	public:
		Message(std::string in, std::string out);
		bool Init();
		void WaitExit();
		~Message();
	private:
		typedef std::pair<PipeIO::byte_buffer, PipeIO::byte_buffer> Packet;
		Packet ReadMessage();
		long GetNextSize();
		void AsyncHandle(Packet packet);
		void Handle(Json::Value json, PipeIO::byte_buffer payload);
		void HandleLoadLibrary(long req_id, std::string path);
		void HandleLoadFunction(long req_id, long lib_id, std::string fun_name);
		void HandleInvokeFunction(long req_id, long lib_id, long fun_id, Json::Value args, PipeIO::byte_buffer payload);
		void HandleReturnCallback(long callback_id, Json::Value args, PipeIO::byte_buffer payload);
		void DelAyncThreadByID(std::thread::id id);
		PipeIO _io;
		std::thread *_reader;
		std::thread *_writer;
		std::vector<std::thread> _handlers;

		std::map<long, DllLibrary*> _libs;
	};
}