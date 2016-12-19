#pragma once
#ifndef _ImageHelper
#define _ImageHelper



#include<fstream>
#include<string>
#include<vector>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include<iostream>
#include<sstream>
#include <iterator>
#include<boost\archive\text_oarchive.hpp>
#include<boost\archive\text_iarchive.hpp>
#include<boost\serialization\vector.hpp>
#include<boost\serialization\string.hpp>

#include <boost/algorithm/string/regex.hpp>
#include<boost/regex.hpp>

#include<boost\filesystem.hpp>
#include"Constant.h"

#include <boost/bind.hpp>
#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>

#include <exception>
#include <stdexcept>
#include<windows.h>

#include"DataEntity.h"
#include"SocketEx.h"

#pragma comment(lib, "Ws2_32.lib")

namespace fs = boost::filesystem;
namespace po = boost::program_options;
using std::string;
using std::to_string;
using std::cout;
using std::endl;
using std::vector;
using std::ofstream;
using std::ifstream;
using std::istringstream;
using std::runtime_error;
using std::wstring;


class ImageHelper {

public:
	static vector<SOCKET> ImageHelper::sockets;
	static void sendImage(SOCKET& socket, Image image);
	static Image recvImage(SOCKET& socket);
	static void Init(vector<SOCKET>& _sockets);
	ImageHelper();
};

LONG currentTime();


#endif // !_ImageHelper