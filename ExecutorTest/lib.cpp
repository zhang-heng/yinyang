#include <thread>

//����ֵ���ʹ��� ֵ���ͷ���ֵ
extern "C" _declspec(dllexport)int sum(int a, int b)
{
	return a+b;
}

//�����������Ͳ���
extern "C" _declspec(dllexport)void bytes_set(char* a, int len)
{
	for (int i = 0;i<len;i++)
	{
		a[i] = 3;
	} 
}

//��������
extern "C" _declspec(dllexport)bool test_block()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	return true;
}

//�ص����� ֵ����
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

//�ص����� ���ô���
typedef void (*cbfun2)(char* p, int l); 
extern "C" _declspec(dllexport)bool test_callback2(int a, cbfun2 fun)
{
	a *= 100;
	auto bs = new char[a];
	fun(bs, a);
	delete [] bs;
	return true;
}

//�첽���ûص�����
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


//�ص����� ��������ص�����ֵ 
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