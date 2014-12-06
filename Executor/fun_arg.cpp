#include "fun_arg.h"
#include <string>

namespace yinyang{
	using namespace std;
	fun_arg::fun_arg()
	{
	}

	fun_arg::~fun_arg(void)
	{
	}

	value_arg::value_arg(string d)
	{

	}

	value_arg::~value_arg( void )
	{

	}

	long value_arg::get_value()
	{
		return 0;
	}

	refer_arg::refer_arg(string d)
	{

	}

	refer_arg::~refer_arg( void )
	{

	}

	long refer_arg::get_value()
	{
		return 0;
	}

	callback_arg::callback_arg( string d)
	{

	}

	callback_arg::~callback_arg( void )
	{

	}

	long callback_arg::get_value()
	{
		return 0;
	}

}