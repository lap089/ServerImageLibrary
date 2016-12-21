
#include"ClientHandler.h"


ImageManager imageManager;
UserManager userManager;

void initData() {
	cout << "Init image data" << endl;
	userManager.clear();
	imageManager.clear();
	FILE* picture;
	User user("admin", "123456");
	userManager.addUser(user);

	fs::path p("admin");
	fs::directory_iterator end_itr;

	// cycle through the directory
	for (fs::directory_iterator itr(p); itr != end_itr; ++itr)
	{
		if (is_regular_file(itr->path())) {

			if (fopen_s(&picture, itr->path().string().c_str(), "rb") != 0) {
				throw SocketEx("Cannot read image");
			}

			if (picture == NULL) {
				throw SocketEx("Error Opening Image File");
			}

			fseek(picture, 0, SEEK_END);
			int imageSize = ftell(picture);
			fseek(picture, 0, SEEK_SET);

			string current_file = itr->path().string();
			Image image(itr->path().filename().string(), itr->path().string(), "Image", "Init Data", imageSize , "admin");
			imageManager.addImage(image, true);
			fclose(picture);
		}
	}
}



// our thread for recving commands
DWORD WINAPI receive_cmds(LPVOID lpParam)
{
	printf("thread created\r\n");


	// set our socket to the socket passed in as a parameter   
	SOCKET current_client = (SOCKET)lpParam;
	ClientHandler clientHandler;
	User currentUser;
	// buffer to hold our recived data
	char buf[200];
	// buffer to hold our sent data
	string sendData;
	// for error checking 
	int res;
	// user login status
	bool loginStatus = false;
	// our recv loop

	string user, category, imagePath, pass;
	int imageId;
	po::options_description desc("Options");
	desc.add_options()
		("help,h", "Print help messages")
		("download,d", "Download image")
		("login", "Login command (followed by --user and --pass)")
		("pass", po::value<string>(&pass), "Password")
		("user", po::value<string>(&user), "Username")
		("register,r", "Register new user command")
		("category,c", po::value<string>(&category), "category")
		("upload,u", "Upload image")
		("id", po::value<int>(&imageId), "Image ID")
		("logout", "Logout command")
		("delete", "Delete Image")
		("all,a", "Type all")
		("list,l", "Get list of images");
	po::variables_map vm;

	while (true)
	{
		res = recv(current_client, buf, sizeof(buf), 0); // recv cmds

		if (!clientHandler.socketErrorCheck(res, current_client)) {
			cout << "End client " << current_client << endl;
			return 0;
		}

		buf[res] = '\0';
		
		Sleep(10);

		try
		{
			po::store(po::command_line_parser(clientHandler.commandParser(buf)).options(desc).run(), vm);
			po::notify(vm);

			if (!loginStatus && !vm.count("login") && !vm.count("register")) {
				cout << "Please login first or register new account (--help (-h) for more info)" << endl;
			}
			else if (vm.count("login") && vm.size() == 3) {
				if (loginStatus) {
					cout << "Please logout first!" << endl;
				}
				else if (vm.count("user") && vm.count("pass")) {
					currentUser = clientHandler.login(current_client, user, pass, userManager);
					loginStatus = true;
						
				}
				else {
					throw po::error("Please specify username and pass with command --user and --pass");
				}
				
			}
			else if (vm.count("register")) {
				if (vm.count("user") && vm.count("pass")) {
				clientHandler.signUp(current_client, user, pass, userManager);
				}
				else {
					throw po::error("Please specify username and pass with command --user and --pass");
				}
			}
			else if (vm.count("logout")) {
				loginStatus = false;
				cout << "Logout successful" << endl;
			}
			else if (vm.count("list")) {
				if (vm.count("user")) {
				clientHandler.getListRequest(current_client, imageManager, user, TYPE_USER);
				}
				else if (vm.count("category")) {
				clientHandler.getListRequest(current_client, imageManager, category, TYPE_CATEGORY);
				}
				else if (vm.count("all")) {
					clientHandler.getListRequest(current_client, imageManager, "", TYPE_ALL);
				}
				else {
					clientHandler.getListRequest(current_client, imageManager, currentUser.getUsername(), TYPE_MINE);
				}

			}
			else if (vm.count("download")) {
				if (vm.count("id")) {
				clientHandler.downImageRequest(current_client, imageManager, imageId);
				}
				else {
					throw po::error("Please provide id of image");
				}
			}
			else if (vm.count("upload")) {
				clientHandler.uploadImageRequest(current_client, imageManager);
			}
			else if (vm.count("quit")) {
				cout << "\nrecived bye cmd\n";

				sendData = "cya\n";
				Sleep(10);
				send(current_client, sendData.c_str(), sizeof(sendData), 0);

				// close the socket associted with this client and end this thread
				closesocket(current_client);
				ExitThread(0);
			}
			else {
				throw po::error("Invalid command");
			}



		}
		catch (boost::program_options::required_option& e)
		{
			cout << e.what() << endl;
		}
		catch (boost::program_options::error& e)
		{
			cout << "ERROR: " << e.what() << std::endl << std::endl;
		}
		catch (SocketEx& e) {
			cout << "SOCKET ERROR: " << e.what() << endl << endl;
		}


		vm.clear();

		// clear buffers
		sendData = "";
		memset(buf, ' ', sizeof(buf));
	}
}


int main()
{
	printf("Starting up Multi-threaded ImageLibrary Server\r\n");

	SerialHelper::deserializeImage(IMAGE_SERIALIZATION, imageManager);
	SerialHelper::deserializeUser(USER_SERIALIZATION, userManager);

	if (imageManager.getSize() == 0 && userManager.getSize() ==0) {
		initData();
	}

	// our masterSocket(socket that listens for connections)
	SOCKET sock;
	vector<SOCKET> socks;
	// for our thread
	DWORD thread;
	ImageHelper::Init(socks);

	WSADATA wsaData;
	sockaddr_in server;

	// start winsock
	int ret = WSAStartup(0x101, &wsaData); // use highest version of winsock avalible

	if (ret != 0)
	{
		return 0;
	}

	// fill in winsock struct ... 
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(123); // listen on telnet port 23

								  // create our socket
	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == INVALID_SOCKET)
	{
		return 0;
	}

	// bind our socket to a port(port 123) 
	if (bind(sock, (sockaddr*)&server, sizeof(server)) != 0)
	{
		return 0;
	}

	// listen for a connection  
	if (listen(sock, SOMAXCONN) != 0)
	{
		return 0;
	}

	// socket that we snedzrecv data on
	SOCKET client;

	sockaddr_in from;
	int fromlen = sizeof(from);



	// loop forever 
	while (true)
	{
		client = SOCKET_ERROR;
		// accept connections
		while (client == SOCKET_ERROR) {
			client = accept(sock, (struct sockaddr*)&from, &fromlen);
		}

		printf("Client connected\r\n");
		socks.push_back(client);
		// create our recv_cmds thread and parse client socket as a parameter
		CreateThread(NULL, 0, receive_cmds, (LPVOID)client, 0, &thread);

	}

	// shutdown winsock
	closesocket(sock);
	WSACleanup();

	// exit
	return 0;
}