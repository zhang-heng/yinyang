#pragma once
#include <mutex>
#include <atomic>
#include <condition_variable>

namespace yinyang
{
	template<typename T> class BlockQueue
	{
	public:
		T pop(){
			if(!_running) throw exception();
			_working = true;
			unique_lock<mutex> lck(_mtx); 
			_cv.wait(lck,[&]
			{
				if(!_running) 
				{
					_working = false;
					_cv.notify_all();
					throw exception();
				}
				return !_queue.empty();
			});
			auto t =_queue.front();
			_queue.pop();
			_working = false;
			return t;
		}

		void push(T t){
			if (!_running) return;
			std::unique_lock<mutex> lck(_mtx); 
			_queue.push(t); 
			_cv.notify_one();
		}

		void Release()
		{
			std::unique_lock<mutex> lck(_mtx);
			_running = false; 
			_cv.notify_all();
			_cv.wait(lck,[&]{return !_working;});
		}

		BlockQueue()
		{
			_working = false;
			_running = true;
		}

		~BlockQueue()
		{
			if (_running) Release();
		}
	private:

		std::atomic_bool _working;
		std::atomic_bool _running; 
		std::mutex _mtx;
		std::condition_variable _cv; 
		std::queue<T> _queue;
	}; 
}