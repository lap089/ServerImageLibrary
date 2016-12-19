#include "ClientHandler.h"
#include"DataEntity.h"
#include"Constant.h"



vector<string>  ClientHandler::commandParser(char* buf) {

	std::istringstream iss(buf);
	vector<string> cmdTokens{ std::istream_iterator<string>{iss}, std::istream_iterator<string>{} };
	if (cmdTokens.empty() == false) {
		for (int i = cmdTokens.size() - 1; i >= 0; i--) {
			if (cmdTokens[i].empty()) {
				cmdTokens.erase(cmdTokens.begin() + i);
			}
		}
	}
	return cmdTokens;
}


void ClientHandler::downImageRequest(SOCKET& current_client, ImageManager& imageManager, int imageId)
{
		
	Image imageFile = imageManager.find(imageId);
		
	if (imageFile.getId() != -1) {			
		cout << "Down image " << imageFile.getName() << endl;
		send(current_client, SUCCESS_CODE, sizeof(SUCCESS_CODE), 0);
		ImageHelper::sendImage(current_client, imageFile);
	}
	else {
		send(current_client, ERROR_CODE, sizeof(ERROR_CODE), 0);
		throw SocketEx("Receive invalid Id");
	}
	cout << "Sending done" << endl;
}

// server waits for receiving ack from client
bool ACK(SOCKET& current_client) {
	char buf[1024];
	int stat;
	do { //Read while we get errors that are due to signals.
		stat = recv(current_client, buf, sizeof(buf), 0);
	} while (stat < 0 && strlen(buf));

	cout << "Received data in socket\n";
	cout << "Socket data: " << buf << endl;

	if (strstr(buf, SUCCESS_CODE) == NULL) {
		cout << "Failed to ACK" << endl;
		return false;
	}
	else {
		cout << "Received ACK, start to send data" << endl << endl;
		return true;
	}
}

void ClientHandler::getListRequest(SOCKET& current_client, ImageManager imageManager, string query, bool isUserType) {
	string data = "";
	char buf[100];
	int ret;
	ImageManager resultImages;
	if (isUserType) {
		resultImages = imageManager.findByUser(query);
	}
	else {
		resultImages = imageManager.findByCatagory(query);
	}	

	int size = resultImages.getSize();


	// Format : id - name - catagory - description - size - uploader
	if (size > 0) {
		Image image = resultImages.getImage(0);
		data = to_string(image.getId()) + DELIMITER + image.getName() + DELIMITER + image.getCategory() + DELIMITER + image.getDescription() + DELIMITER + to_string(image.getSize()) + DELIMITER + image.getUploader();
	}
	for (int i = 1; i < size; ++i) {
		Image image = resultImages.getImage(i);
		data += DELIMITER + to_string(image.getId()) + DELIMITER + image.getName() + DELIMITER + image.getCategory() + DELIMITER + image.getDescription() + DELIMITER + to_string(image.getSize()) + DELIMITER + image.getUploader();
	}

	// If image list is empty, return data size zero
	string dataSize = to_string(size) + DELIMITER + to_string(data.size());

	send(current_client, dataSize.c_str(), dataSize.length(), 0);

	//Sleep(500);

	//cout << currentTime() << endl;

	if (ACK(current_client)) {
		
			send(current_client, data.c_str(), data.length(), 0);			
			/*do {
				ret = recv(current_client, buf, sizeof(buf), 0);
			} while (ret > 0);
			cout << "Received ACK" << endl;*/
	}
	else {
		throw SocketEx("Does not receive ACK");
	}
	
	cout << "Finish!" << endl;
}



void ClientHandler::uploadImageRequest(SOCKET & current_client, ImageManager& imageManager)
{
	Image image = ImageHelper::recvImage(current_client);
	if (imageManager.find(image.getName(), image.getUploader()).getId() == -1) {
		imageManager.addImage(image, true);
	}
}



void s_handle(int s, SOCKET& client)
{
	if (client)
		closesocket(client);
	//WSACleanup();
//	Sleep(1000);
	//cout << "EXIT SIGNAL :" << s;
	//exit(0);
}


bool ClientHandler::socketErrorCheck(int res, SOCKET& client) {

	if (res == 0)
	{
		//0==other side terminated conn
		printf("\t Terminated connection\n");
		Sleep(40);
		closesocket(client);
		client = 0;
		return false;
	}
	else if (res == SOCKET_ERROR)
	{
		//-1 == send error
		printf("Socket error\n");
		Sleep(40);
		s_handle(res, client);
		return false;
	}
	return true;
}

User ClientHandler::login(SOCKET& current_client, string username, string pass, UserManager userManager)
{
	string mess;
	User user = userManager.find(username);
	if (user.getUsername().empty()) {
		mess = "Username does not exists";
		send(current_client, mess.c_str(), mess.length(), 0);
		throw SocketEx(mess);
	}
	else if (user.login(username, pass)) {
		send(current_client, SUCCESS_CODE, strlen(SUCCESS_CODE), 0);
		return user;
	}
	else {
		mess = "Wrong password";
		send(current_client, mess.c_str(), mess.length(), 0);
		throw SocketEx(mess);
	}
}

bool ClientHandler::signUp(SOCKET& sock, string username, string pass, UserManager& userManager)
{
	string mess;
	User user = userManager.find(username);
	if (!user.getUsername().empty()) {
		mess = "User exists";
		send(sock, mess.c_str(), mess.length(), 0);
		throw SocketEx(mess);
	}
	else {
		User newUser(username, pass);
		userManager.addUser(newUser);
		send(sock, SUCCESS_CODE, strlen(SUCCESS_CODE), 0);
		return true;
	}
}

