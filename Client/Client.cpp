
#include <signal.h>
#include"ClientSide.h"

//error trapping signals

// SOCKETS
SOCKET sock, client;

int main()
{


	//Declarations
	DWORD poll;
	char* window = "Image";
	int res, port = 123;
	string buf;
	string ip = "127.0.0.1";
	char RecvdData[1024] = "";
	int imageId;
	User authenticatedUser;
	string user, catagory, imagePath, description, pass;
	ImageManager imageManager;
	bool loginStatus = false;

	cout << "\t\tEcho Client" << endl;
	
	setUpServerConnection(client, sock, ip, port);


	po::options_description desc("Options");
	desc.add_options()
		("help,h", "Print help messages")
		("download,d", "Download image")
		("login", "Login command (followed by --user and --pass)")
		("pass", po::value<string>(&pass), "Password")
		("user", po::value<string>(&user), "Username")
		("register,r", "Register new user command")
		("catagory,c", po::value<string>(&catagory), "Catagory")
		("upload,u", "Upload image")
		("image,i", "Image selection")
		("id", po::value<int>(&imageId), "Image ID")
		("all,a", "Type all")
		("logout", "Logout command")
		("list,l", "Get list of images");
		
	po::variables_map vm;

	while (true)
	{
		//(buf, 0, sizeof(buf));
		//buf[0] = '\0';
		//cout << "\nEnter message to send ->\n";
		//fgets(buf, sizeof(buf), stdin);
		cout << "\nCmd>";
		getline(cin, buf);
			
		res = send(sock, buf.c_str(), sizeof(buf), 0);

		socketErrorHandler(res, client, sock);

		try
		{
		po::store(po::command_line_parser(commandParser(buf)).options(desc).run(),vm); 
		po::notify(vm);

		if (!loginStatus && !vm.count("login") && !vm.count("register") && !vm.count("help")) {
			cout << "Please login first or register new account (--help (-h) for more info)" << endl;
		}
		else if (vm.count("login") && vm.size() == 3) {
			if (loginStatus) {
				cout << "Please logout first!" << endl;
			}
			else if (vm.count("user") && vm.count("pass")) {
				authenticatedUser = login(sock, user, pass);
				loginStatus = true;
				cout << "Login successful!" << endl;
			}
			else {
				throw po::error("Please specify username and pass with command --user and --pass");
			}
		}
		else if (vm.count("register")) {
			if (vm.count("user") && vm.count("pass")) {
			signUp(sock, user, pass);
			cout << "Sign up successful" << endl;
			}
			else {
				throw po::error("Please specify username and pass with command --user and --pass");
			}
		}
		else if (vm.count("logout")) {
			loginStatus = false;
		}
		else if (vm.count("list")) {
			if (vm.count("user")) {
				imageManager = getList(sock, user);
			}
			else if (vm.count("catagory")) {
				imageManager = getList(sock, catagory);
			}
			else {
				throw po::error("Please provide subject to search for!");
			}
			
			cout << "Recived! Size: " << imageManager.getSize() << endl;

			for (int i = 0; i < imageManager.getSize(); ++i) {
				cout << i << ". \t" << imageManager.getImage(i).getId() << " - " << imageManager.getImage(i).getName() << endl;
			}

		}
		else if (vm.count("image")) {
			if (vm.count("id")) {
				showImageDetail(imageManager, imageId);
			}
			else {
				throw po::error("Please provide id of image");
			}
		}
		else if (vm.count("download")) {
			if (vm.count("id")) {
				string imageName = downImage(sock, imageId);
				Mat image = imread(imageName, CV_LOAD_IMAGE_COLOR);   // Read the file
				namedWindow(window, CV_WINDOW_NORMAL);
				imshow(window, image);
				waitKey(0);
				destroyWindow(window);
			}	
			else {
				throw po::error("Please provide id of image");
			}
		}
		else if (vm.count("upload")) {
			uploadImage(sock, authenticatedUser);
		}
		else if (vm.count("help")) {
			cout << desc << endl;
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

	}

	closesocket(client);
	WSACleanup();
}