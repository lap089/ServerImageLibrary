#pragma once
#ifndef _SocketEx
#define _SocketEx


#include"ImageHelper.h"
using std::ostringstream;

class SocketEx : public runtime_error {
public:

	SocketEx(string mes)
		: runtime_error(mes)
	{}

	virtual const char* what() const throw();
};





#endif // !_SocketEx
