#include<stdio.h>
#include<iostream>
#include<string>
#include<fstream>
#include<Winsock2.h>
#include<Windows.h>

#pragma comment(lib, "Ws2_32.lib")
using namespace std;

class storeData
{
private:
    string hostName;
    int totalRam;
    int availRam;
    string getHostName();
    int getTotalRAM();
    int getAvailRAM();



public:

    void fetchData();
    string stringify();
    void writeInFile();
};
