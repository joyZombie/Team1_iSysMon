#include"systemInteraction.h"

string storeData::getHostName()
{

    //Character array to store the host name
    char szPath[128] = "";

    //The WSADATA structure contains information about the Windows Sockets implementation.
    // Creating a variable of type WSADATA

    WSADATA wsaData;

    //The WSAStartup function initiates use of the Winsock DLL by a process
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    //gethostname()----returns the name of the host processor that the program is running on 
    gethostname(szPath, sizeof(szPath));
    return szPath;
}
int storeData:: getTotalRAM()
{
    int ret = 0;

    //MEMORYSTAUSEX IS A STURUCTURE THAT Contains information about the current state of both physical and virtual memory, including extended memory.


    MEMORYSTATUSEX m;
    m.dwLength = sizeof(m);
    GlobalMemoryStatusEx(&m);
    ret = (int)(m.ullTotalPhys >> 20);

    return ret;
}

int storeData::getAvailRAM()
{
    int ret = 0;
    MEMORYSTATUSEX m;
    m.dwLength = sizeof(m);
    GlobalMemoryStatusEx(&m);
    ret = (int)(m.ullAvailPhys >> 20);
    return ret;
}
    void storeData:: fetchData()
    {
        hostName = getHostName();
        cout << "Hostname is " << hostName << endl;
        totalRam = getTotalRAM();
        cout << "Total RAM is " << totalRam<< " MB" << endl;
        availRam = getAvailRAM();
        cout << "Total Available RAM is " << availRam<<" MB" << endl;
        
    }
    string storeData::stringify()
    {
        string str;
        str += (hostName) + ", ";
        str +=to_string(totalRam) + "MB, ";
        str += to_string(availRam) + "MB, ";

        return str;
    }

    void storeData::writeInFile()
    {
        
         ofstream myFile("Stats.txt");
   
        //Writing into the file
        myFile << stringify()<<endl<<endl;
        myFile.close(); 
        
    }