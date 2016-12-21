#include"SocketEx.h"

const char * SocketEx::what() const throw()
{
	return runtime_error::what();
}
