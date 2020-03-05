# SensorStreamer
Streamer for ATI DAQ F/T Force Sensor

This is a simple implementation of a program reading data from an ATI DAQ Force Sensor device and streaming them over the network using OpenIGTLink protocol (http://openigtlink.org/). 

The program was compiled and tested on a Windows machine with the NI-DAQmx drivers installed (https://www.ni.com/de-de/support/downloads/drivers/download.ni-daqmx.html#333268). The ATIDAQ C Library (https://www.ati-ia.com/Products/ft/software/daq_software.aspx) is used to manage the force sensor control and data read. 

## SimpleIGTLinkStreamer
### Usage - Windows machine + Visual Studio

git clone https://github.com/mariatirindelli/SensorStreamer.git
cd SensorStreamer
cd SimpleIGTLinkStreamer

From the cmake GUI: 

- run configure (Select x64 platform for the project generator)
- Add the path to the OpenIGTLink.Config in OpenIGTLink_DIR
- Add the path to the ATIDAQ C Library in DAQmx_DIR (This directory must contain both the .h and .lib files)
- Eventually change the CMAKE_INSTALL_PREFIX to the directory where you want your .exe file to be installed
- run configure again
- run generate
- open project in Visual Studio
- compile ALL_BUILD
- compile INSTALL

In your CMAKE_INSTALL_PREFIX you should now have the .exe file together with a configuration .json file. 
Before running the program, you should copy in the folder the calibration file for the force sensor as well as the .dll of the shared libraries
