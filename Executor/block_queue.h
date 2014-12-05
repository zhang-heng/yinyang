#pragma once
#include <mutex>
#include <condition_variable>

namespace yinyang
{
	template<typename T> class block_queue
	{
	public:
		T pop(){
			unique_lock<mutex> lck(_mtx);
			while(!_queue.size()) _cv.wait(lck);
			auto t =_queue.front();
			_queue.pop();
			return t;
		}

		void push(T t){
			std::unique_lock<mutex> lck(_mtx);
			_queue.push(t);
			_cv.notify_one();
		}

	private:
		std::mutex _mtx;
		std::condition_variable _cv; 
		std::queue<T> _queue;
	}; 
}