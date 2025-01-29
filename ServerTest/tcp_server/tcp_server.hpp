#ifndef TCPSERVER_HPP
#define TCPSERVER_HPP

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

class TCPServer {
public:
    TCPServer(const std::string& ip, int port, short bufferSize);
    ~TCPServer();

    void run();

private:
    WSADATA wsaData;
    std::string ipAddress;
    int portNumber;
    short bufferSize;
    SOCKET serverSock;

    void createSocket();
    void bindSocket();
    void startListening();
    SOCKET acceptClient(sockaddr_in& clientInfo);
    void handleClient(SOCKET clientSock);
};

#endif // TCPSERVER_HPP
