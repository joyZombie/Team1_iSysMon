#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<fstream>
#include <Lmcons.h>
#include<Winsock2.h>
#include<Windows.h>
#include<vector>
#include<chrono>
#include <Lmcons.h>
#include <thread>
#include <functional>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

class storeData
{
private:

    vector<string> v;

    string hostName;
    string userName;
    int totalRam;
    int availRam;
    float cpuLoad;
    int cpuIdleTime;
    string processorArchitecture;
    int processorType;
    int noOfProcessors;
    string timeStamp;


    // Functions
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
    string getCurrentTime();
    void timer_start();


public:

    string fetchNewData();
    void intialiseThread();
    void fetchData();
    string stringify();
};
