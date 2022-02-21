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
#include <in6addr.h>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

class storeData
{
private:

    //Data Members

    vector<string> v;
    string hostName;
    string userName;
    int totalRam;
    int availRam;
    int totalDiskSpace;
    int freeDiskSpace;
    float cpuLoad;
    int cpuIdleTime;
    string processorArchitecture;
    int processorType;
    int noOfProcessors;
    string timeStamp;

    //Member Functions

    string getHostName();
    int getTotalRAM();
    int getAvailRAM();
    void getHardDiskSpace();
    string getUserName();
    float GetCPULoad();
    int getProcessorArchitecture();
    int getProcessorType();
    int getNoOfProcessors();
    int getCpuIdleTime();
    string getCurrentTime();
    void timer_start();
    string stringify();
    void fetchData();

public:

    void intialiseThread();
    string fetchNewData();
};
