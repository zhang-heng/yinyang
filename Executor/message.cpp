#include "message.h"
#include <mutex>

namespace yinyang{
	using namespace std;

	Message::Message(string in, string out)
		:_io(in, out)
	{
	}

	Message::~Message()
	{
	}

	bool Message::Init()
	{
		if (_io.init_io_file())
		{
			_reader = new thread([=]()
			{ 
				AsyncHanlde(ReadMessage());
			});
			_writer = new thread([=]()
			{

			});
			return true;
		}		
		return false;
	}

	vector<char> Message::ReadMessage()
	{
		throw new exception();
	}

	void Message::AsyncHanlde(vector<char> buff)
	{
		_handlers.push_back(thread([=]()
		{
			auto id = this_thread::get_id();
		}));
	}

	void Message::DelAyncThreadByID(thread::id id )
	{ 

		auto it = find_if(_handlers.begin(),_handlers.end(),
			[id](thread &t){return t.get_id() == id;});
		_handlers.erase(it);
	}
}