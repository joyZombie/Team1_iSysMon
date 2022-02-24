#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream> 
#include <Lmcons.h>
#include<Winsock.h>
#include<Windows.h>
#include<vector>
#include<chrono>
#include <Lmcons.h>
#include <thread>
#include <functional>
#include <in6addr.h>
#include<type_traits>
#include<cstdint>

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
    string getUserName();
    void getRamInformation();
    void getDiskSpace();
    float getCpuLoad();
    void getProcessorInformation();
    int getCpuIdleTime();
    string getCurrentTime();
    void fetchData();
    string stringify();
    void timerStart();
    void sendDataToServer(string uid);

public:

    void intialiseFetchDataThread();
    void intialiseSendDataThread(string uid);
    string fetchNewData();
};

class parseData {
public:

    parseData(
        string cuid,
        string hsN,
        string usN,
        int totRam,
        int avRam,
        int tDskSpce,
        int fDskSpce,
        float cpuL,
        int cpuIT,
        string prcArch,
        int nOP,
        int prcType,
        string timstmp
    )
    {
        cliUid = cuid;
        hstName = hsN;
        usrName = usN;
        totlRam = totRam;
        avlblRam = avRam;
        totlDiskSpace = tDskSpce;
        freeDiskSpace = fDskSpce;
        cpuLd = cpuL;
        cpuIdTime = cpuIT;
        prcssArcht = prcArch;
        noOfPrc = nOP;
        prcssType = prcType;
        timeStmp = timstmp;
    }


    int checkData() {

        int cS = 0;
        int temp = 0;

        for (int i = 0; i < cliUid.length(); i++)
        {
            temp = '|' - cliUid[i];
            cS = temp ^ cS;
        }
        temp = 0;

        for (int i = 0; i < hstName.length(); i++)
        {
            temp = '|' - hstName[i];
            cS = temp ^ cS;
        }
        temp = 0;

        for (int i = 0; i < usrName.length(); i++)
        {
            temp = '|' - usrName[i];
            cS = temp ^ cS;
        }
        temp = 0;

        cS += totlRam;
        cS += avlblRam;
        cS += totlDiskSpace;
        cS += freeDiskSpace;
        cS += cpuLd;
        cS += cpuIdTime;

        for (int i = 0; i < prcssArcht.length(); i++)
        {
            temp = '|' - prcssArcht[i];
            cS = temp ^ cS;
        }
        temp = 0;

        cS += noOfPrc;
        cS += prcssType;

        for (int i = 0; i < timeStmp.length(); i++)
        {
            temp = '|' - timeStmp[i];
            cS = temp ^ cS;
        }
        temp = 0;

        return cS;

    }


#if 0
    string checkData() {

        int key = 10;
        string cS = "";
        for (int i = 0; i < hstName.length(); i++)
        {
            cS += hstName[i] + key;
        }
        for (int i = 0; i < usrName.length(); i++)
        {
            cS += usrName[i] + key;
        }

        cS += totlRam + key;
        cS += avlblRam + key;
        cS += totlDiskSpace + key;
        cS += freeDiskSpace + key;
        cS += cpuLd + key;
        cS += cpuIdTime + key;
        for (int i = 0; i < prcssArcht.length(); i++)
        {
            cS += prcssArcht[i] + key;
        }
        cS += noOfPrc + key;
        cS += prcssType + key;
        for (int i = 0; i < timeStmp.length(); i++)
        {
            cS += timeStmp[i] + key;
        }
        return cS;
    }
#endif

#if 0
    int checkData() {

        int key = 101;
        int cS = 0;
        cS += (sizeof(hstName) ^ key);
        cS += (sizeof(usrName) ^ key);
        cS += (sizeof(totlRam) ^ key);
        cS += (sizeof(avlblRam) ^ key);
        cS += (sizeof(totlDiskSpace) ^ key);
        cS += (sizeof(freeDiskSpace) ^ key);
        cS += (sizeof(cpuLd) ^ key);
        cS += (sizeof(cpuIdTime) ^ key);
        cS += (sizeof(prcssArcht) ^ key);
        cS += (sizeof(noOfPrc) ^ key);
        cS += (sizeof(prcssType) ^ key);
        cS += (sizeof(timeStmp) ^ key);
        return cS;
    }
#endif

    string cliUid;
    string hstName;
    string usrName;
    int totlRam;
    int avlblRam;
    int totlDiskSpace;
    int freeDiskSpace;
    float cpuLd;
    int cpuIdTime;
    string prcssArcht;
    int noOfPrc;
    int prcssType;
    string timeStmp;
};
