#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<fstream>
#include <Lmcons.h>
#include<Winsock2.h>
#include<Windows.h>
#include<vector>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

class storeData
{
private:

    string hostName;
    string userName;
    int totalRam;
    int availRam;
    float cpuLoad;
    int processorArchitecture;
    int processorType;
    int noOfProcessors;
    int cpuIdleTime;

    string getHostName();
    int getTotalRAM();
    int getAvailRAM();
    string getUserName();
    uint32_t getTotalVirtualMemory();
    float GetCPULoad();
    int getProcessorArchitecture();
    int getProcessorType();
    int getNoOfProcessors();
    int getCpuIdleTime();

public:

    void fetchData();
    string stringify();
    void writeInFile();
};
