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
using namespace std;

void ProcessNewMessage(int nClientSocket);
void ProcessNewRequest();

class parseData {
public:

    parseData(string hsN,
        string usN,
        int totRam,
        int avRam,
        float cpuL,
        int nOP,
        int chkSum,
        int prcType
        )
        //int cpuIT
    {
        hstName = hsN;
        usrName = usN;
        totlRam = totRam;
        avlblRam = avRam;
        cpuLd = cpuL;
        prcssType = prcType;
        noOfPrc = nOP;
        //cpuIdTime = cpuIT;
        checkS = chkSum;
    }

    void display() {
        cout << "HostName: " << hstName << endl;
        cout << "UserName: " << usrName << endl;
        cout << "Total RAM: " << totlRam << " MB" << endl;
        cout << "Avlbl RAM: " << avlblRam << " MB" << endl;
        cout << "CPU Load: " << cpuLd << " %" << endl;
        //cout << "CPU Idle Time: " << cpuIdTime << " ms" << endl;
        cout << "No. of Processors: " << noOfPrc << endl;
        cout << "Processor Type: " << prcssType << endl;
        cout << "CheckSum at client side: " << checkS << endl;
    }

    int checkData() {
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
    }

    string hstName;
    string usrName;
    int totlRam;
    int avlblRam;
    float cpuLd;
    //int prcssArch;
    int prcssType;
    int noOfPrc;
    //int cpuIdTime;
    int checkS;
};
