#pragma once
#ifndef _Constant
#define _Constant

#include<string>
using std::string;

// Delimiter string
const string DELIMITER = "1234567890";

// Serialization file name
const string USER_SERIALIZATION = "UserList";
const string IMAGE_SERIALIZATION = "ImageList";

// Code response
const char* const ERROR_CODE = "ERROR";
const char* const SUCCESS_CODE = "OK";

// Searching types
const int TYPE_USER = 0;
const int TYPE_CATEGORY = 1;
const int TYPE_ALL = 2;
const int TYPE_MINE = 3;

#endif // !_Constant


