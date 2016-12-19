#include "ImageHelper.h"
vector<SOCKET> ImageHelper::sockets;

void ImageHelper::sendImage(SOCKET& socket, Image image)
{
	FILE *picture;
	int size, read_size, stat, packet_index;
	char send_buffer[1024], read_buffer[256];
	packet_index = 1;

	if (fopen_s(&picture, image.getPath().c_str(), "rb") != 0) {
		cout << "Cannot read file" << endl;
	}
	printf("Getting Picture Size\n");

	if (picture == NULL) {
		printf("Error Opening Image File");
	}

	fseek(picture, 0, SEEK_END);
	size = ftell(picture);
	fseek(picture, 0, SEEK_SET);
	cout<< "Total Picture size: " << size << endl;
	string meta = to_string(size) + DELIMITER + image.getName();
	//Send Picture Size
	cout << "Sending Picture meta: " << meta << " - Time:" << currentTime() << endl;
	send(socket, meta.c_str(), meta.length() , 0);

	//Send Picture as Byte Array
	printf("Sending Picture as Byte Array\n");

	do { //Read while we get errors that are due to signals.
		stat = recv(socket, read_buffer, sizeof(read_buffer), 0);
	} while (stat < 0);

	cout<< "Received data in socket\n";
	cout << "Socket data: " << read_buffer << endl;

	if (strstr(read_buffer, SUCCESS_CODE) == NULL) {
		cout << "Failed to ACK" << endl;
		return;
	}
	else {
		cout << "Received ACK, start to send data" << endl << endl;
	}

	while (!feof(picture)) {
		//while(packet_index = 1){
		//Read from the file into our send buffer
		read_size = fread(send_buffer, 1, sizeof(send_buffer) - 1, picture);

		//Send data through our socket 
		do {
			stat = send(socket, send_buffer, read_size, 0);
		} while (stat < 0);

		cout<<"Packet Number:" << packet_index << endl;
	//	printf("Packet Size Sent: %i\n", read_size);
	//	printf(" \n");
	//	printf(" \n");


		packet_index++;

		//Zero out our send buffer
		memset(send_buffer, 0, sizeof(send_buffer));
	}
}


Image ImageHelper::recvImage(SOCKET& socket) {
	FILE* picture;
	int ret, recv_size = 0, read_size, write_size, packet_index = 0;
	char RecvdData[1024] = "";
	char buf[100];
	fs::path slash("/");
	fs::path::string_type slashPrefer = slash.make_preferred().native();
	wstring pathSeparator = slashPrefer;

	Sleep(50);

	// Get meta data
	cout << "Get meta data" << endl;
	do {
		ret = recv(socket, RecvdData, sizeof(RecvdData), 0);
	} while (ret < 0);

	if (strstr(RecvdData, ERROR_CODE)) {
		throw SocketEx("Cannot get meta data");
	}

	//RecvdData[ret] = '\0';
	cout << "Receive Buffer: " << RecvdData << " - Time:" << currentTime() << endl;

	vector<string> strs;
	boost::algorithm::split_regex(strs, RecvdData, boost::regex(DELIMITER));

	int size = atoi(strs[3].c_str());
	Image imageFile(strs[0], strs[0], strs[1], strs[2], size, strs[4]);


	cout << "Image size: " <<imageFile.getSize()  << endl;
	cout << "Image Name: " << imageFile.getName() << endl;


	if (imageFile.getSize() > 0 && !imageFile.getName().empty() && !imageFile.getUploader().empty()) {
		send(socket, SUCCESS_CODE, sizeof(SUCCESS_CODE), 0);
	}
	else {
		throw SocketEx("Wrong meta data");
	}

	imageFile.setPath(imageFile.getUploader() + string(pathSeparator.begin(), pathSeparator.end()) + imageFile.getName());

	fs::path rootPath(imageFile.getUploader());
	boost::system::error_code returnedError;

	fs::create_directories(rootPath, returnedError);

	//did not successfully create directories
	if (returnedError) {
		throw SocketEx("Cannot create directory");
	}
		

	// Open file to write
	fopen_s(&picture, imageFile.getPath().c_str(), "wb");

	if (picture == NULL) {
		throw SocketEx("Error has occurred. Image file could not be opened\n");
	}


	int need_exit = 0;
	struct timeval timeout = { 10,0 };

	fd_set fds;
	int buffer_fd, buffer_out;

	while (recv_size < imageFile.getSize()) {
		//while(packet_index < 2){

		FD_ZERO(&fds);
		FD_SET(socket, &fds);

		buffer_fd = select(FD_SETSIZE, &fds, NULL, NULL, &timeout);

		if (buffer_fd < 0)
			printf("error: bad file descriptor set.\n");

		if (buffer_fd == 0)
			printf("error: buffer read timeout expired.\n");

		if (buffer_fd > 0)
		{
			do {
				read_size = recv(socket, RecvdData, sizeof(RecvdData), 0);
			} while (read_size <0);

			cout << "Packet number received: " << packet_index << endl;
			//	printf("Packet size: %i\n", read_size);


			//Write the currently read data into our image file
			write_size = fwrite(RecvdData, 1, read_size, picture);
			//	printf("Written image size: %i\n", write_size);

			if (read_size != write_size) {
				printf("error in read write\n");
			}


			//Increment the total number of bytes read
			recv_size += read_size;
			packet_index++;
			//	printf("Total received image size: %i\n", recv_size);

		}

	}


	fclose(picture);
	printf("Image successfully Received!\n");

	return imageFile;
}


void ImageHelper::Init(vector<SOCKET>& _sockets)
{
	ImageHelper::sockets = _sockets;
}

ImageHelper::ImageHelper()
{
}

LONG currentTime()
{
	SYSTEMTIME time;
	GetSystemTime(&time);
	LONG time_ms = (time.wSecond * 1000) + time.wMilliseconds;
	return time_ms;
}
