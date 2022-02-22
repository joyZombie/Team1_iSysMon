#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream> 
#include<Lmcons.h>
#include<Winsock2.h>
#include<Windows.h>
#include<Ws2tcpip.h>
#include<tchar.h>
#include<vector>
#include<type_traits>
#include<cstdint>
#include <cstdlib>
#include <inttypes.h>

//#include <System.SysUtils.hpp>

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

class parseData {
public:

    parseData(string hsN,
        string usN,
        int totRam,
        int avRam,
        float cpuL,
        int nOP,
        int prcType
    )
        //int cpuIT     
    {
        hstName = hsN;
        usrName = usN;
        totlRam = totRam;
        avlblRam = avRam;
        cpuLd = cpuL;
        //cpuIdTime = cpuIT;
        noOfPrc = nOP;
        prcssType = prcType;
    }

    /*int checkData() {

        int key = 101;
        int cS = 0;
        cS += (sizeof(hstName) ^ key);
        cS += (sizeof(usrName) ^ key);
        cS += (sizeof(totlRam) ^ key);
        cS += (sizeof(avlblRam) ^ key);
        cS += (sizeof(cpuLd) ^ key);
        //cS += (sizeof(cpuIdTime) ^ key);
        cS += (sizeof(noOfPrc) ^ key);
        cS += (sizeof(prcssType) ^ key);
        return cS;
    }*/
    string checkData()
    {
        string cS = "";
        int key = 10;
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


        cS += (int)cpuLd + key;


        //cS += cpuIdTime ^ key;


        cS += noOfPrc + key;


        cS += prcssType + key;

         //__int64 size = StrToInt64(cS);
        //__int64 v = _atoi64(cS.c_str());
        //cout << "Client CS" << cS<<endl;
        return cS;

        



    }

    string hstName;
    string usrName;
    int totlRam;
    int avlblRam;
    float cpuLd;
    //int cpuIdTime;
    int noOfPrc;
    int prcssType;

};
