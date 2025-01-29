#include "tcp_server.hpp"

TCPServer::TCPServer(const std::string& ip, int port, short bufferSize)
    : ipAddress(ip), portNumber(port), bufferSize(bufferSize), serverSock(INVALID_SOCKET) {
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw std::runtime_error("WinSock initialization failed: " + std::to_string(WSAGetLastError()));
    }
    std::cout << "WinSock initialization is OK" << std::endl;
}

TCPServer::~TCPServer() {
    if (serverSock != INVALID_SOCKET) {
        closesocket(serverSock);
    }
    WSACleanup();
}

void TCPServer::run() {
    createSocket();
    bindSocket();
    startListening();

    while (true) {
        try {
            sockaddr_in clientInfo{};
            SOCKET clientSock = acceptClient(clientInfo);
            handleClient(clientSock);
            closesocket(clientSock);
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

void TCPServer::createSocket() {
    serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock == INVALID_SOCKET) {
        throw std::runtime_error("Socket creation failed: " + std::to_string(WSAGetLastError()));
    }
}

void TCPServer::bindSocket() {
    sockaddr_in servInfo{};
    servInfo.sin_family = AF_INET;
    servInfo.sin_port = htons(portNumber);

    if (inet_pton(AF_INET, ipAddress.c_str(), &servInfo.sin_addr) <= 0) {
        throw std::runtime_error("Invalid IP address format");
    }

    if (bind(serverSock, reinterpret_cast<const sockaddr*>(&servInfo), sizeof(servInfo)) != 0) {
        throw std::runtime_error("Socket binding failed: " + std::to_string(WSAGetLastError()));
    }
    std::cout << "Socket binding is OK" << std::endl;
}

void TCPServer::startListening() {
    if (listen(serverSock, SOMAXCONN) != 0) {
        throw std::runtime_error("Failed to start listening: " + std::to_string(WSAGetLastError()));
    }
    std::cout << "Listening for incoming connections..." << std::endl;
}

SOCKET TCPServer::acceptClient(sockaddr_in& clientInfo) {
    int clientSize = sizeof(clientInfo);
    SOCKET clientSock = accept(serverSock, reinterpret_cast<sockaddr*>(&clientInfo), &clientSize);

    if (clientSock == INVALID_SOCKET) {
        throw std::runtime_error("Failed to accept client: " + std::to_string(WSAGetLastError()));
    }

    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientInfo.sin_addr, clientIP, sizeof(clientIP));
    std::cout << "Client connected with IP: " << clientIP << std::endl;

    return clientSock;
}

void TCPServer::handleClient(SOCKET clientSock) {
    std::vector<char> buffer(bufferSize);
    while (true) {
        int bytesReceived = recv(clientSock, buffer.data(), buffer.size(), 0);
        if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
            std::cout << "Client disconnected or error occurred" << std::endl;
            break;
        }

        std::cout << "Client message: " << std::string(buffer.begin(), buffer.begin() + bytesReceived) << std::endl;

        std::string response = "OK";
        if (send(clientSock, response.c_str(), response.size(), 0) == SOCKET_ERROR) {
            throw std::runtime_error("Failed to send message to client: " + std::to_string(WSAGetLastError()));
        }
    }
}
