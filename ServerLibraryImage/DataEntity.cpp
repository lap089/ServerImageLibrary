#include "DataEntity.h"

User::User(string username, string password)
{
	this->username = username;
	this->password = password;
	this->status = true;
}

User::User(string username)
{
	this->username = username;
}

bool User::login(string _username, string _password)
{
	return username.compare(_username) == 0 && password.compare(_password) == 0;
}

bool User::equals(User& user)
{
	return (this->username.compare(user.getUsername()) == 0);
}

User UserManager::getUser(int pos)
{
	return pos < users.size() ? users[pos] : User("");
}

int UserManager::getSize()
{
	return users.size();
}

void UserManager::addUser(User user)
{
	users.push_back(user);
	SerialHelper::serializeUser(USER_SERIALIZATION, *this);
}

bool UserManager::isExisted(User user)
{
	for (User u : users) {
		if (user.equals(u)) {
			return true;
		}
	}
	return false;
}

User UserManager::find(string username)
{
	for (User user : users) {
		if (user.getUsername().compare(username) == 0) {
			return user;
		}
	}
	User user("");
	return user;
}

void UserManager::clear()
{
	users.clear();
}

vector<Image> ImageManager::getImages()
{
	return images;
}

Image ImageManager::getImage(int pos)
{
	return images.size() > pos ? images[pos] : Image(-1);
}

int ImageManager::getSize()
{
	return images.size();
}

void ImageManager::addImage(Image image, bool isSaved)
{
	
	if (isSaved) {
		image.setId(images.size());
		images.push_back(image);
		SerialHelper::serializeImage(IMAGE_SERIALIZATION, *this);
	}
	else {
		images.push_back(image);
	}
}

Image ImageManager::find(int id)
{
	for (Image image : images) {
		if (image.getId() == id) {
			return image;
		}
	}
		Image image(-1);
		return image;
}


Image ImageManager::find(string name, string uploader)
{
	for (Image image : images) {
		if (image.getName() == name && image.getUploader() == uploader) {
			return image;
		}
	}
		Image image(-1);
		return image;

}

bool ImageManager::isExisted(Image image)
{
	for (Image i : images) {
		if (i.getName() == image.getName() && i.getUploader() == image.getUploader()) {
			return true;
		}
	}
	return false;
}


void ImageManager::clear()
{
	images.clear();
}

ImageManager ImageManager::findByUser(string query)
{
	ImageManager results;
	for (Image image : images) {
		if (image.getUploader() == query) {
			results.addImage(image, false);
		}
	}
	return results;
}

ImageManager ImageManager::findByCategory(string query)
{
	ImageManager results;
	for (Image image : images) {
		if (image.getCategory() == query) {
			results.addImage(image, false);
		}
	}
	return results;
}

Image::Image(string name, string path, string category, string description, int size, string uploader)
{
	this->name = name;
	this->path = path;
	this->category = category;
	this->description = description;
	this->size = size;
	this->uploader = uploader;
}

Image::Image(int id, string name, string path, string category, string description, int size, string uploader)
{
	this->id = id;
	this->name = name;
	this->path = path;
	this->category = category;
	this->description = description;
	this->size = size;
	this->uploader = uploader;
}

Image::Image(int id)
{
	this->id = id;
}

void SerialHelper::serializeUser(string fileName, const UserManager & userManager)
{
	ofstream ofs(fileName);
	{
		boost::archive::text_oarchive oa(ofs);
		// write class instance to archive
		oa << userManager;
		// archive and stream closed when destructors are called
	}
}

void SerialHelper::deserializeUser(string fileName, UserManager & userManager)
{
	// create and open an archive for input
	std::ifstream ifs(fileName);
	if (!ifs) {
		return;
	}
	else {
		cout << "Start to recovery..." << endl;
	}

	boost::archive::text_iarchive ia(ifs);
	// read class state from archive
	ia & userManager;
	// archive and stream closed when destructors are called
}

void SerialHelper::serializeImage(string fileName, const ImageManager & imageManager)
{
	ofstream ofs(fileName);
	{
		boost::archive::text_oarchive oa(ofs);
		// write class instance to archive
		oa << imageManager;
		// archive and stream closed when destructors are called
	}
}

void SerialHelper::deserializeImage(string fileName, ImageManager & imageManager)
{
	// create and open an archive for input
	std::ifstream ifs(fileName);
	if (!ifs) {
		return;
	}
	else {
		cout << "Start to recovery..." << endl;
	}
	boost::archive::text_iarchive ia(ifs);
	// read class state from archive
	ia >> imageManager;
	// archive and stream closed when destructors are called
}
