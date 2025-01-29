#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <socklib/socklib.hpp>
#include <text_chunker/text_chunker.hpp>
#include <config_read/config_read.hpp>

#pragma comment(lib, "ws2_32.lib")


int main()
{	
	std::string server_ip;
	int port;
	int packetSize;
	int frequency;

	try {
		ConfigData config = readConfig("config.txt");
		server_ip = config.ip;
		port = config.port;
		packetSize = config.packetSize;
		frequency = config.frequency;
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	

	SockLib sock = SockLib::SockLib(server_ip, port, packetSize);
	try {
		sock.connect_server();
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
		return 1;
	}

	std::ofstream file; 
	file.open("output.txt", std::ios::app);

	if (!file.is_open()) {
		std::cerr << "Ошибка открытия файла!" << std::endl;
		return 1;
	}
	
	file << "<###########################################>" << std::endl;
	file << std::endl;

	auto now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	file << "Measurement time: " << std::put_time(std::localtime(&now_c), "%d.%m.%Y  %H:%M:%S") << std::endl;
	file << std::endl;

	file << "Configuration: " << std::endl;
	file << "IP server: " << server_ip << std::endl;
	file << "PORT: " << port << std::endl;
	file << "Packet size: " << packetSize << " byte" << std::endl;
	file << "Frequency packet: " << frequency << " microseconds" << std::endl;

	TextChunker read_file = TextChunker("input.txt", packetSize);
	file << "Number of packages: " << read_file.getChunkCount() << std::endl << std::endl;

	auto run_time = std::chrono::high_resolution_clock::now();
	auto last_packet = std::chrono::high_resolution_clock::now();

	double sum_measurements = 0;

	for (size_t i = 0; i < read_file.getChunkCount(); i++){
		auto now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - last_packet);

		while (now.count() < frequency) {
			now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - last_packet);
		}

		try {
			auto start = std::chrono::high_resolution_clock::now();

			sock.send_packet(read_file[i]);

			auto end = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
			last_packet = std::chrono::high_resolution_clock::now();

			sum_measurements += duration.count();
			file << "packet №" << i + 1 << " time taken: " << duration.count() << " microseconds" << "\n";
		}
		catch (const std::runtime_error& e) {
			file << "packet №" << i + 1 << " caught exception: " << e.what() << "\n";
		}
		
	}

	auto now_ = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now_ - run_time);

	file << std::endl;
	file << "Average speed: " << sum_measurements / read_file.getChunkCount() << " microseconds" << std::endl;
	file << "Run time: " << duration.count() << " microseconds"  << std::endl;

	file << std::endl;
	file << "<------------------------------------------->" << std::endl;
	file << std::endl;
	file.close();

	return 0;
}