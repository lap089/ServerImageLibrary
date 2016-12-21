
#ifndef _DataEntity
#define _DataEntity


#include<fstream>
#include<string>
#include<vector>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include<iostream>
#include<sstream>
#include <iterator>
#include<boost/archive/text_oarchive.hpp>
#include<boost/archive/text_iarchive.hpp>
#include<boost/serialization/vector.hpp>
#include<boost/serialization/string.hpp>
#include<boost/filesystem.hpp>
#include"Constant.h"

#include <boost/bind.hpp>
#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>

#include <exception>
#include <stdexcept>


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




class Image {
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & id;
		ar & name;
		ar & path;
		ar & category;
		ar & description;
		ar & size;
		ar & uploader;
	}
	int id;
	string name;
	string path;
	string category;
	string description;
	int size;
	string uploader;

public:
	Image(string name, string path, string category, string description, int size, string uploader);
	Image(int id, string name, string path, string category, string description, int size, string uploader);
	Image(int id);
	Image(int id, string name);
	Image() {}
	int getId() { return id; }
	void setId(int id) { this->id = id; }
	string getName() { return name; }
	string getPath() { return path; }
	string getCategory() { return category;}
	string getDescription() { return description; }
	int getSize() { return size; }
	string getUploader() { return uploader; }
    string toString();
};



class User {
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & username;
		ar & password;
		ar & status;
	}
	string username;
	string password;
	bool status;


public:
	User(string username, string password);
	User(string username);
	User() {}
	string getUsername() { return username; }
	bool login(string _username, string _password);
	bool isOnline() { return status; }
	bool equals(User& user);
};



class UserManager {
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & users;
/*
		if (Archive::is_loading::value) {
			ar & size;
			for (int i = 0; i < size; i++) {
				User user;
				ar & user;
				users.push_back(user);
			}
		}
		else {
			size = users.size();
			ar & size;
			for (User user : users) {
				ar & user;
			}
		}*/
	}
	vector<User> users;

public:
	UserManager() {}
	User getUser(int pos);
	int getSize();
	void addUser(User user);
	bool isExisted(User user);
	User find(string username);
	void clear();
};

class ImageManager {
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & images;
	}
	vector<Image> images;
	
public:
	vector<Image> getImages();
	Image getImage(int pos);
	int getSize();
	void addImage(Image image);
	Image find(int id);
	Image find(string name);
	void clear();
};


class SerialHelper {
public:
	static void serializeUser(string fileName, const UserManager& userManager);
	static void deserializeUser(string fileName, UserManager& userManager);

	static void serializeImage(string fileName, const ImageManager& imageManager);
	static void deserializeImage(string fileName, ImageManager& imageManager);
};





#endif // !_DataEntity
