#pragma once
#pragma once
#include <string>
#include "nlohmann/json.hpp"

using nlohmann::json;


struct Config
{
	std::string serverAddress; //!< The server address
	uint16_t port; //!< The server port
	std::string calFilePath;
	std::string sensor;
	int freq;
};


// OUTSTREAMER CONFIG

inline void to_json(json& j, const Config& c) {
	j["serverAddress"] = c.serverAddress;
	j["port"] = c.port;
	j["calFilePath"] = c.calFilePath;
	j["sensor"] = c.sensor;
	j["frequency"] = c.freq;
}

inline void from_json(const json& j, Config& c) {
	c.serverAddress = j["serverAddress"].get<std::string>();
	c.port = j["port"].get<uint16_t>();
	c.calFilePath = j["calFilePath"].get<std::string>();
	c.sensor = j["sensor"].get<std::string>();
	c.freq = j["frequency"].get<int>();
}