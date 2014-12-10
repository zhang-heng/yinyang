#include <thread>

//测试值类型处理 值类型返回值
extern "C" _declspec(dllexport)int sum(int a, int b)
{
	return a+b;
}

//处理引用类型参数
extern "C" _declspec(dllexport)void bytes_set(char* a, int len)
{
	for (int i = 0;i<len;i++)
	{
		a[i] = 3;
	} 
}

//阻塞调用
extern "C" _declspec(dllexport)bool test_block()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	return true;
}

//回调处理 值传递
typedef void (*cbfun1)(int i); 
extern "C" _declspec(dllexport)bool test_callback1(char* a, int len, cbfun1 fun)
{
	for (int i = 0;i<len;i++)
	{
		a[i] = 3;
		fun(i);
	}
	return true;
}

//回调处理 引用传递
typedef void (*cbfun2)(char* p, int l); 
extern "C" _declspec(dllexport)bool test_callback2(int a, cbfun2 fun)
{
	a *= 100;
	auto bs = new char[a];
	fun(bs, a);
	delete [] bs;
	return true;
}

//异步调用回调测试
typedef void (*cbfun3)(char* p, int l, char* p100); 
extern "C" _declspec(dllexport)bool test_callback3(int a, cbfun3 fun)
{
	std::thread th([&]()
	{
		a *= 100;
		auto bs = new char[a];
		auto bs2 = new char[100];
		for (int i =0;i<3;i++)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			fun(bs, a, bs2);
		}
		delete [] bs;
		delete [] bs2;
	});
	return true;
}


//回调处理 阻塞处理回调返回值 
typedef int (*cbfun4)(int i);
extern "C" _declspec(dllexport)bool test_callback4(cbfun4 fun)
{
	int n = 0;
	for (int i = 0; i<100; i++)
	{
		n = fun(n);
	}
	return true;
}