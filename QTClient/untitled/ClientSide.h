#pragma once
#ifndef _ClientSide
#define _ClientSide

#include"DataEntity.h"
#include"SocketEx.h"
#include"ImageHelper.h"


ImageManager getList(SOCKET& sock);
vector<string> commandParser(string buf);

string downImage(SOCKET&, int);

void s_cl(const char *a, int x, SOCKET& client, SOCKET& sock);
void socketErrorHandler(int res, SOCKET& client, SOCKET& sock);

void setUpServerConnection(SOCKET& client, SOCKET& sock, string& ip, int port);

void uploadImage(SOCKET&, User);
void showImageDetail(ImageManager& imageManager, int id);

bool logout(SOCKET& sock);
User login(SOCKET& sock, string user, string pass);
bool signUp(SOCKET& sock, string user, string pass);

#endif // !_ClientSide
