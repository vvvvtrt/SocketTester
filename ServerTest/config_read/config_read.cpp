#include "config_read.hpp"

std::pair<std::string, std::string> parseLine(const std::string& line) {
    size_t pos = line.find('=');
    if (pos == std::string::npos) {
        throw std::runtime_error("Invalid config line: missing '=': " + line);
    }
    std::string key = line.substr(0, pos);
    std::string value = line.substr(pos + 1);

    // Удаление пробелов с начала и конца ключа и значения
    size_t first = key.find_first_not_of(" ");
    size_t last = key.find_last_not_of(" ");
    key = key.substr(first, (last == std::string::npos) ? std::string::npos : last - first + 1);

    first = value.find_first_not_of(" ");
    last = value.find_last_not_of(" ");
    value = value.substr(first, (last == std::string::npos) ? std::string::npos : last - first + 1);

    return std::make_pair(key, value);
}



ConfigData readConfig(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open config file: " + filename);
    }

    ConfigData config;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; 
        try {
            std::pair<std::string, std::string> keyValue = parseLine(line);
            std::string key = keyValue.first;
            std::string value = keyValue.second;

            if (key == "ip") {
                config.ip = value;
            }
            else if (key == "port") {
                config.port = std::stoi(value);
            }
            else if (key == "packet_size") {
                config.packetSize = std::stoi(value);
            }
            else {
                std::cerr << "Warning: Unknown config key: " << key << std::endl;
            }
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error parsing line: " << e.what() << std::endl;
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Error parsing integer: " << e.what() << " from " << line << std::endl;
        }
    }

    file.close();

    if (config.ip.empty() || config.port == 0 || config.packetSize == 0) {
        throw std::runtime_error("Missing required config data in " + filename);
    }


    return config;
}