#pragma once
#ifndef _ClientHandler
#define _ClientHandler

#include"ImageHelper.h"
#include"SocketEx.h"
#include"DataEntity.h"


class ClientHandler {
public:
	vector<string> commandParser(char* buf);

	void getListRequest(SOCKET& current_client, ImageManager imageManager, string query, int type);

	void downImageRequest(SOCKET& current_client, ImageManager& imageManager, int imageId);

	void uploadImageRequest(SOCKET& current_client, ImageManager& imageManager);

	bool socketErrorCheck(int res, SOCKET& client);

	User login(SOCKET&, string username, string pass, UserManager userManager);

	bool signUp(SOCKET&, string username, string pass, UserManager& userManager);

};

#endif // !_ClientHandler
