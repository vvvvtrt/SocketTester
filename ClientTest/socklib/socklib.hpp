#ifndef SOCKLIB_HPP
#define SOCKLIB_HPP

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <inaddr.h>
#include <stdio.h>
#include <vector>
#include <stdexcept>
#include <algorithm>

#pragma comment(lib, "ws2_32.lib")

class SockLib {
public:
	SockLib(const std::string& ip_address, const int& port, const int& packet);
	~SockLib();

	bool connect_server();
	bool send_packet(const std::string& data);

private:
	const char* ip_address_;
	const int port_;
	const int packet_size_;
	SOCKET ClientSock;
};


#endif SOCKLIB_HPP