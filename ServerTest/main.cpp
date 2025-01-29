#include <iostream>
#include <tcp_server/tcp_server.hpp>
#include <config_read/config_read.hpp>

#pragma comment(lib, "Ws2_32.lib")

int main() {
	std::string server_ip;
	int port;
	int packetSize;

	try {
		ConfigData config = readConfig("config.txt");
		server_ip = config.ip;
		port = config.port;
		packetSize = config.packetSize;
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

    try {
        TCPServer server(server_ip, port, packetSize);
        server.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
