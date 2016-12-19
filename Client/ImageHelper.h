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
#include<fstream>
#include<sstream>
#include <iterator>
#include <exception>
#include <stdexcept>
#include<algorithm>

#include <boost/algorithm/string/regex.hpp>
#include<boost/regex.hpp>
#include<boost/filesystem.hpp>
#include <boost/bind.hpp>
#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>
#include<boost\archive\text_oarchive.hpp>
#include<boost\archive\text_iarchive.hpp>
#include<boost\serialization\vector.hpp>
#include<boost\serialization\string.hpp>

#include <opencv2\opencv.hpp>


#include<windows.h>
#include"Constant.h"
#include"DataEntity.h"

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
using std::runtime_error;
using std::exception;
using std::count;
using std::cin;
using std::getline;

using cv::Mat;
using cv::namedWindow;
using cv::destroyWindow;
using cv::imread;
using cv::imshow;
using cv::waitKey;

class ImageHelper {

public:
	static vector<SOCKET> ImageHelper::sockets;
	static string recvImage(SOCKET& socket);
	static void sendImage(SOCKET& socket, Image image, FILE*);
	static void Init(vector<SOCKET>& _sockets);
	ImageHelper();
};

class ImageFile {
	string name;
	string absPath;
	int size;

public:
	
	ImageFile(string _path, string _name, int _size) { 
		this->name = _name;
		this->size = _size;
		this->absPath = _path;
	}

	ImageFile() {};
	string getName() { return name; }
	void setName(string _name) { name = name; }
	int getSize() { return size; }
	void setSize(int _size) { size = _size; }
	void setAbsPath(string _path) { this->absPath = _path; }
	

};

bool ACK(SOCKET&);

LONG currentTime();

#endif // !_ImageHelper
