#include "socklib.hpp"


SockLib::SockLib(const std::string& ip_address, const int& port, const int& packet_size) : 
	ip_address_(ip_address.c_str()),
	port_(port),
	packet_size_(packet_size)
{}

SockLib::~SockLib() {
	closesocket(ClientSock);
	WSACleanup();
}

bool SockLib::connect_server() {
	int erStat;										

	in_addr ip_to_num;
	inet_pton(AF_INET, ip_address_, &ip_to_num);


	WSADATA wsData;
	erStat = WSAStartup(MAKEWORD(2, 2), &wsData);

	if (erStat != 0) {
		std::cerr << "Error WinSock version initializaion #";
		std::cerr << WSAGetLastError();
		throw std::runtime_error("Error WinSock version initializaion");
	}
	else
		std::cout << "WinSock initialization is OK" << std::endl;

	ClientSock = socket(AF_INET, SOCK_STREAM, 0);

	if (ClientSock == INVALID_SOCKET) {
		std::cerr << "Error initialization socket # " << WSAGetLastError() << std::endl;
		closesocket(ClientSock);
		WSACleanup();
	}
	else
		std::cout << "Client socket initialization is OK" << std::endl;


	sockaddr_in servInfo;

	ZeroMemory(&servInfo, sizeof(servInfo));

	servInfo.sin_family = AF_INET;
	servInfo.sin_addr = ip_to_num;
	servInfo.sin_port = htons(port_);

	erStat = connect(ClientSock, (sockaddr*)&servInfo, sizeof(servInfo));

	if (erStat != 0) {
		std::cerr << "Connection to Server is FAILED. Error # " << WSAGetLastError() << std::endl;
		closesocket(ClientSock);
		WSACleanup();
		throw std::runtime_error("Connection FAILED");
	}
	else
		std::cout << "Connection established SUCCESSFULLY. Ready to send a message to Server" << std::endl;
}


bool SockLib::send_packet(const std::string& data) {
	std::vector <char> servBuff(packet_size_), clientBuff(packet_size_);		
	short packet_size = 0;	
	
	std::fill(clientBuff.begin(), clientBuff.end(), 0);

	std::strncpy(clientBuff.data(), data.c_str(), clientBuff.size() - 1); 
	clientBuff[clientBuff.size() - 1] = '\0';

	packet_size = send(ClientSock, clientBuff.data(), clientBuff.size(), 0);

	if (packet_size == SOCKET_ERROR) {
		std::cerr << "Can't send message to Server. Error # " << WSAGetLastError() << std::endl;
		closesocket(ClientSock);
		WSACleanup();
		return 1;
	}

	packet_size = recv(ClientSock, servBuff.data(), servBuff.size(), 0);

	if (packet_size == SOCKET_ERROR) {
		std::cerr << "Can't receive message from Server. Error # " << WSAGetLastError() << std::endl;
		closesocket(ClientSock);
		WSACleanup();
		return 1;
	}
	else
		std::cout << "Server message: " << servBuff.data() << std::endl;
}

