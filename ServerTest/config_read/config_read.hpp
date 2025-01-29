#ifndef CONFIG_READ_HPP
#define CONFIG_READ_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept> 


struct ConfigData {
    std::string ip;
    int port;
    int packetSize;
};


std::pair<std::string, std::string> parseLine(const std::string& line);
ConfigData readConfig(const std::string& filename);


#endif