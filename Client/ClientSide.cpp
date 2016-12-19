#include "ClientSide.h"

inline bool isInteger(const string & s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char * p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}

ImageManager getList(SOCKET & sock, string query)
{
	string sendBuf;
	char recvBuf[10024];
	ImageManager imageManager;
	vector<string> strs;
	string data = "";
	int ret = -1;
	int sum = 0;
	do {
		ret = recv(sock, recvBuf, sizeof(recvBuf), 0);
	} while (ret < 0);

	recvBuf[ret] = '\0';
	//cout <<"recvBuf: "<< recvBuf << endl;

	
	boost::algorithm::split_regex(strs, recvBuf, boost::regex(DELIMITER));
	int dataSize = atoi(strs[1].c_str());
	int size = atoi(strs[0].c_str());

		if (size >= 0 && dataSize >=0) {
		//	cout << "Send ACK" << endl;
			send(sock, SUCCESS_CODE, sizeof(SUCCESS_CODE), 0);
		}
		else {
			send(sock, ERROR_CODE, sizeof(ERROR_CODE), 0);
			throw SocketEx("Received Size error");
		}

		recvBuf[0] = '\0';
		while(sum < dataSize) {
		ret = recv(sock, recvBuf, sizeof(recvBuf), 0);
		if(ret > 0) {
		recvBuf[ret] = '\0';
		//cout << recvBuf << endl;
		data += recvBuf;
		sum += ret;
		}		
		}

		cout << "Start parsing" << endl;
		if (strlen(recvBuf) != 0) {
			boost::algorithm::split_regex(strs, recvBuf, boost::regex(DELIMITER));
			for (int i = 0; i < (strs.size() - 1); i += 6) {
				if (!isInteger(strs[i])) {
					throw SocketEx("Wrong Image List Format: " + strs[i]);
				}
				int id = atoi(strs[i].c_str());
				int size = atoi(strs[i + 4].c_str());
				Image image(id, strs[i + 1], "", strs[i + 2], strs[i + 3], size, strs[i + 5]);

				imageManager.addImage(image);
			}
		}

		return imageManager;
}



void s_handle(int s, SOCKET& client, SOCKET& sock)
{
	if (sock)
		closesocket(sock);
	if (client)
		closesocket(client);
	WSACleanup();
	Sleep(1000);
	cout << "EXIT SIGNAL :" << s;
	exit(0);
}



void s_cl(char *a, int x, SOCKET& client, SOCKET& sock)
{
	cout << a;
	s_handle(x + 1000, client, sock);
}

void socketErrorHandler(int res, SOCKET& client, SOCKET& sock) {

	if (res == 0)
	{
		//0==other side terminated conn
		printf("\nSERVER terminated connection\n");
		Sleep(40);
		closesocket(client);
		client = 0;
		//break;
	}
	else if (res == SOCKET_ERROR)
	{
		//-1 == send error
		printf("Socket error\n");
		Sleep(40);
		s_handle(res, client, sock);
		//break;
	}
}

void setUpServerConnection(SOCKET& client, SOCKET& sock, string& ip, int port)
{
	sockaddr_in ser;
	sockaddr addr;
	WSADATA data;
	int res;

	ser.sin_family = AF_INET;
	ser.sin_port = htons(port);                    //Set the port

	inet_pton(AF_INET, ip.c_str(), &(ser.sin_addr));
	memcpy(&addr, &ser, sizeof(SOCKADDR_IN));

	res = WSAStartup(MAKEWORD(1, 1), &data);      //Start Winsock
	cout << "\n\nWSAStartup"
		<< "\nVersion: " << data.wVersion
		<< "\nDescription: " << data.szDescription
		<< "\nStatus: " << data.szSystemStatus << endl;

	if (res != 0)
		s_cl("WSAStarup failed", WSAGetLastError(), client, sock);

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);       //Create the socket
	if (sock == INVALID_SOCKET)
		s_cl("Invalid Socket ", WSAGetLastError(), client, sock);
	else if (sock == SOCKET_ERROR)
		s_cl("Socket Error)", WSAGetLastError(), client, sock);
	else
		cout << "Socket Established" << endl;



	res = connect(sock, &addr, sizeof(addr));               //Connect to the server
	if (res != 0)
	{
		s_cl("SERVER UNAVAILABLE", res, client, sock);
	}
	else
	{
		cout << "\nConnected to Server: ";
		memcpy(&ser, &addr, sizeof(SOCKADDR));
	}
}

void uploadImage(SOCKET & sock, User user)
{
	string imagePath, catagory, description, imageName;
	int imageSize;
	FILE* picture;
	cout << "Image Path: ";
	getline(cin, imagePath);
	cout << "Image Catagory: ";
	getline(cin, catagory);
	cout << "Image Description: ";
	getline(cin, description);
	fs::path p(imagePath);
	imageName = p.filename().string();

	if (fopen_s(&picture, imagePath.c_str(), "rb") != 0) {
		send(sock, ERROR_CODE, strlen(ERROR_CODE), 0);
		throw SocketEx("Cannot read image");
	}

	printf("Getting Picture Size\n");

	if (picture == NULL) {
		send(sock, ERROR_CODE, strlen(ERROR_CODE), 0);
		throw SocketEx("Error Opening Image File");
	}

	fseek(picture, 0, SEEK_END);
	imageSize = ftell(picture);
	fseek(picture, 0, SEEK_SET);


	Image image(imageName, imagePath, catagory, description, imageSize, user.getUsername());

	ImageHelper::sendImage(sock, image, picture);
}

void showImageDetail(ImageManager & imageManager, int id)
{
	if (imageManager.getSize() == 0) {
		cout << "Image manager is currently empty, please request server (-l --user/--catagory 'object')" << endl;
		return;
	}
	Image image = imageManager.find(id);
	if (image.getId() == -1) {
		cout << "Cannot not find the image" << endl;
		return;
	}
	cout << "Image: " << image.getName() << endl;
	cout << "Catagory: " << image.getCategory() << endl;
	cout << "Description: " << image.getDescription() << endl;
	cout << "Size: " << image.getSize() << endl;
	cout << "Uploader: " << image.getUploader() << endl<<endl;
}

bool logout(SOCKET & sock)
{
	char buf[100];
	int ret = recv(sock, buf, sizeof(buf), 0);
	if (ret > 0) {
		if (strstr(buf, SUCCESS_CODE)) {
			return true;
		}
		else {
			throw SocketEx("Cannot logout");
		}
	}
	return false;
}

User login(SOCKET & sock, string user, string pass)
{
	char recvBuf[100]; 
	int ret;
	ret = recv(sock, recvBuf, sizeof(recvBuf), 0);

	if (ret > 0) {
		recvBuf[ret] = '\0';
		if (strstr(recvBuf, SUCCESS_CODE)) {
			User user(user, pass);
			return user;
		}
		else {
			throw SocketEx(recvBuf);
		}
	}
	else {
		throw SocketEx("Receive ACK error");
	}

}

bool signUp(SOCKET & sock, string user, string pass)
{
	char recvBuf[100];
	int ret;
	ret = recv(sock, recvBuf, sizeof(recvBuf), 0);

	if (ret > 0) {
		recvBuf[ret] = '\0';
		if (strstr(recvBuf, SUCCESS_CODE)) {
			return true;
		}
		else {
			throw SocketEx(recvBuf);
		}
	}
	else {
		throw SocketEx("Receive ACK error");
	}

}


vector<string> commandParser(string buf) {
	
	bool isPath = false;
	
	int index=0;
	std::istringstream iss(buf.c_str());
	vector<string> cmdTokens{ std::istream_iterator<string>{iss}, std::istream_iterator<string>{} };

	//string str(buf);

	//string word;
	//for (const char c : str)
	//{
	//	
	//	if (c != ' ')
	//	{
	//		if (c == '\'' && isPath) {
	//			
	//		}

	//		word += c;
	//	}
	//	else if (isPath) {
	//			
	//		
	//	}
	//	else if (word != "")
	//	{
	//		if (word == "--path" || word == "-p") {
	//			isPath = true;
	//		}
	//		cmdTokens.push_back(word);
	//			word = "";
	//	}

	//}

	
	if (cmdTokens.empty() == false) {
		for (int i = cmdTokens.size() - 1; i >= 0; i--) {
		
			//if (count(cmdTokens[i].begin(), cmdTokens[i].end(), '\'') == 2) {
			//	// remove '
			//}


			//if (count(cmdTokens[i].begin(), cmdTokens[i].end(), '\'') == 1)
			//{
			//	isPath = !isPath;
			//	if (isPath) {
			//		
			//		// concat
			//	}
			//	else {
			//		// concat
			//		isPath = true;
			//	}
			//}
			if (cmdTokens[i].empty()) {
				cmdTokens.erase(cmdTokens.begin() + i);
			}
		}
	}
	return cmdTokens;
}

string downImage(SOCKET& sock, int id)
{
	
	if (ACK(sock))
	{
		string imageName = ImageHelper::recvImage(sock);
		return imageName;
	}
	else {
		throw SocketEx("Cannot find Image");
	}
	
}
