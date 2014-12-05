
extern "C" _declspec(dllexport)int Sum(int a, int b)
{
	return a+b;
}

extern "C" _declspec(dllexport)int Max(int a, int b)
{
	if(a>=b)return a;
	else
		return b;
}

extern "C" _declspec(dllexport)int Min(int a, int b)
{
	if(a>=b)return b;
	else
		return a;
}

extern "C" _declspec(dllexport)bool funbytes(char* a, int len)
{
	for (int i = 0;i<len;i++)
	{
		a[i] = 3;
	}
	return true;
}

typedef void (*callbackfun)(int i); 

extern "C" _declspec(dllexport)bool funbytes2(char* a,int len, callbackfun fun)
{
	for (int i = 0;i<len;i++)
	{
		a[i] = 3;
		fun(i);
	}
	return true;
}