#pragma once
#include <iostream>
#include <fstream>
#include <sys/timeb.h>
#include <time.h>
#include <string>
#include "igtlServerSocket.h"
#include "igtlSensorMessage.h"
#include "nlohmann/json.hpp"
#include "Config.hpp"
#include "SensorHandler.hpp"
#include "AtiForceSensor.hpp"

int parse_config(Config& config)
{
	std::string configDir = std::string("config.json");

	try
	{
		std::ifstream fid(configDir);

		json j;
		fid >> j;

		config = j;
	}
	catch(std::exception& e)
	{
		std::cout << "Failed to load config file: " << e.what() << std::endl;
		return -1;
	}
	return 0;
};

void get_time(igtl::TimeStamp::Pointer ts)
{
	struct _timeb timebuffer;
	time_t sec;
	unsigned short frac;

	_ftime(&timebuffer); // C4996
	// Note: _ftime is deprecated; consider using _ftime_s instead

	sec = timebuffer.time;
	frac = timebuffer.millitm;

	ts->SetTime(sec, frac);
}

int main()
{
	Config config;
	if (parse_config(config) < 0)
	{
		return -1;
	}

	std::shared_ptr<SensorHandler> sensor;

	if ((config.sensor.compare("FT_ATI")) == 0)
	{
		sensor.reset(new AtiForceSensor(config.calFilePath));
	}
	else
	{
		std::cout << "Unknown sensor" << std::endl;
		return -1;
	}

	std::cout << "setting frequency: " << config.freq << std::endl;
	sensor->setFrequency(config.freq * 2);
	if (sensor->initSensor() < 0)
	{
		std::cout << "Unable to initialize sensor" << std::endl;
		return -1;
	}
	sensor->printCalInfo();
	
	igtl::ServerSocket::Pointer serverSocket;
	serverSocket = igtl::ServerSocket::New();
	serverSocket->CreateServer(config.port);

	igtl::ClientSocket::Pointer socket;
	bool client_connected = false;

	while (true)
	{
		if (!client_connected)
		{
			std::cout << "Waiting for connection" << std::endl;
			socket = serverSocket->WaitForConnection(30000);
			if (socket.IsNull())
			{
				continue;
			}
			client_connected = true;
			std::cout << "Client connected" << std::endl;
		}

		double data[6];
		sensor->getData(data);

		igtl::SensorMessage::Pointer sensorMsg;
		igtl::TimeStamp::Pointer ts;
		ts = igtl::TimeStamp::New();

		get_time(ts);

		sensorMsg = igtl::SensorMessage::New();
		sensorMsg->SetDeviceName("ForceServer");
		sensorMsg->SetLength(6);
		sensorMsg->SetValue(data);
		sensorMsg->SetTimeStamp(ts);

		sensorMsg->Pack();
		int res = socket->Send(sensorMsg->GetPackPointer(), sensorMsg->GetPackSize());
		
		if (res < 1)
		{
			std::cout << "Client disconnected" << std::endl;
			client_connected = false;
		}
				
		Sleep(1000/(config.freq));
	}
	return 0;

}