#pragma once
#include <string>

typedef long (*__fun0__)();
typedef long (*__fun1__)(long __1);
typedef long (*__fun2__)(long __1, long __2);
typedef long (*__fun3__)(long __1, long __2, long __3);
typedef long (*__fun4__)(long __1, long __2, long __3, long __4); 
typedef long (*__fun5__)(long __1, long __2, long __3, long __4, long __5); 
typedef long (*__fun6__)(long __1, long __2, long __3, long __4, long __5, long __6); 
typedef long (*__fun7__)(long __1, long __2, long __3, long __4, long __5, long __6, long __7); 
typedef long (*__fun8__)(long __1, long __2, long __3, long __4, long __5, long __6, long __7, long __8); 
typedef long (*__fun9__)(long __1, long __2, long __3, long __4, long __5, long __6, long __7, long __8, long __9);  

class dll_library
{
public:
	dll_library(std::string path);
	~dll_library();
private:

};

