#include "ImageHelper.h"
#include"SocketEx.h"

vector<SOCKET> ImageHelper::sockets;

LONG currentTime()
{
	SYSTEMTIME time;
	GetSystemTime(&time);
	LONG time_ms = (time.wSecond * 1000) + time.wMilliseconds;
	return time_ms;
}


//  waits for receiving ack 
bool ACK(SOCKET& current_client) {
	char buf[100];
	int stat;
	do { //Read while we get errors that are due to signals.
		stat = recv(current_client, buf, sizeof(buf), 0);
	} while (stat < 0);

	buf[stat] = '/0';

	cout << "Received data in socket\n";
	cout << "Receive Buffer : "  << buf << endl;

	if (strstr(buf, SUCCESS_CODE) == NULL) {
		cout << "Failed to ACK" << endl;
		return false;
	}
	else {
		cout << "Received ACK" << endl << endl;
		return true;
	}
}


string ImageHelper::recvImage(SOCKET& socket) {
	FILE* image;
	int ret, recv_size = 0, read_size, write_size, packet_index=0;
	char RecvdData[1024] = "";
	char buf[100];

	Sleep(50);

	// Get meta data
	cout << "Get meta data" << endl;
	do {
		ret = recv(socket, RecvdData, sizeof(RecvdData), 0);
	} while (ret < 0);
	
	//RecvdData[ret] = '\0';
	cout << "Receive Buffer: " << RecvdData <<" - Time:" << currentTime()<< endl;
	
	vector<string> strs;
	boost::algorithm::split_regex(strs, RecvdData, boost::regex(DELIMITER));
	
//	cout << "Data parsed: " <<  RecvdData << "  " << ret << endl <<endl;

	int imageSize = atoi(strs[0].c_str());
	
	fs::path p(strs[1]);
	string fileName = p.filename().string();

	cout << "Image size: " << imageSize << endl;
	cout << "Image Name: " <<  fileName << endl;

	

	ImageFile imageFile(strs[1], fileName, imageSize);
	if (imageSize > 0 && !fileName.empty()) {
		send(socket, SUCCESS_CODE, sizeof(SUCCESS_CODE), 0);
	}
	else {
		throw SocketEx("Wrong meta data");
	}
	

	// Open file to write
	fopen_s(&image, imageFile.getName().c_str(), "wb");

	if (image == NULL) {
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
			throw SocketEx("error: bad file descriptor set.\n");

		if (buffer_fd == 0)
			throw SocketEx("error: buffer read timeout expired.\n");

		if (buffer_fd > 0)
		{
			do {
				read_size = recv(socket, RecvdData, sizeof(RecvdData), 0);
			} while (read_size <0);

			cout << "Packet number received: " << packet_index << endl;
		//	printf("Packet size: %i\n", read_size);


			//Write the currently read data into our image file
			write_size = fwrite(RecvdData, 1, read_size, image);
		//	printf("Written image size: %i\n", write_size);

			if (read_size != write_size) {
				throw SocketEx("error in read write\n");
			}


			//Increment the total number of bytes read
			recv_size += read_size;
			packet_index++;
		//	printf("Total received image size: %i\n", recv_size);
			
		}

	}


	fclose(image);
	printf("Image successfully Received!\n");

	return fileName;
}


void ImageHelper::sendImage(SOCKET& socket, Image image, FILE* picture)
{
	int read_size, stat, packet_index;
	char send_buffer[1024], read_buffer[256];
	packet_index = 1;
	
	// Format: name - category - description - size - uploader
	string meta = image.getName() + DELIMITER + image.getCategory() + DELIMITER + image.getDescription() + DELIMITER + to_string(image.getSize()) + DELIMITER + image.getUploader();
	//string meta = to_string(image.getSize()) + DELIMITER + image.getName();

	cout << "Sending Picture meta: " << meta << " - Time:" << currentTime() << endl;
	send(socket, meta.c_str(), meta.length(), 0);

	//Send Picture as Byte Array
	printf("Sending Picture as Byte Array\n");

	do { //Read while we get errors that are due to signals.
		stat = recv(socket, read_buffer, sizeof(read_buffer), 0);
	} while (stat < 0);

	cout << "Received data in socket\n";
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

		cout << "Packet Number:" << packet_index << endl;
		//	printf("Packet Size Sent: %i\n", read_size);
		//	printf(" \n");
		//	printf(" \n");


		packet_index++;

		//Zero out our send buffer
		memset(send_buffer, 0, sizeof(send_buffer));
	}

	fclose(picture);
}

void ImageHelper::Init(vector<SOCKET>& _sockets)
{
	ImageHelper::sockets = _sockets;
}

ImageHelper::ImageHelper()
{
}
