#include "sysInteraction.h"


static float CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
    static unsigned long long _previousTotalTicks = 0;
    static unsigned long long _previousIdleTicks = 0;



    unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
    unsigned long long idleTicksSinceLastTime = idleTicks - _previousIdleTicks;



    float ret = 1.0f - ((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime) / totalTicksSinceLastTime : 0);



    _previousTotalTicks = totalTicks;
    _previousIdleTicks = idleTicks;
    return ret;
}



static unsigned long long FileTimeToInt64(const FILETIME& ft) { return (((unsigned long long)(ft.dwHighDateTime)) << 32) | ((unsigned long long)ft.dwLowDateTime); }


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
string storeData::getUserName()
{
    char username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    GetUserNameA(username, &username_len);
    return username;
}
int storeData::getTotalRAM()
{
    int ret = 0;

    //MEMORYSTAUSEX IS A STURUCTURE THAT Contains information about the current state of both physical and virtual memory, including extended memory.


    MEMORYSTATUSEX m;
    m.dwLength = sizeof(m);
    GlobalMemoryStatusEx(&m);
    ret = (int)((m.ullTotalPhys >> 20));

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

float storeData::GetCPULoad()
{
    FILETIME idleTime, kernelTime, userTime;
    float cpuLoad = GetSystemTimes(&idleTime, &kernelTime, &userTime) ? CalculateCPULoad(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime) + FileTimeToInt64(userTime)) : -1.0f;
    return cpuLoad * 100;
}
int storeData::getProcessorArchitecture()
{
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    return sysInfo.wProcessorArchitecture;
}
int storeData::getProcessorType()
{
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    return sysInfo.dwProcessorType;
}
int storeData::getNoOfProcessors()
{
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    return sysInfo.dwNumberOfProcessors;
}
int storeData::getCpuIdleTime()
{
    LASTINPUTINFO li = { 0 };
    li.cbSize = sizeof(LASTINPUTINFO);

    //This function contains the time of last input event was received
    GetLastInputInfo(&li);

    return GetTickCount64() - li.dwTime;
}
void storeData::fetchData()
{
    hostName = getHostName();
    //cout << "Hostname is " << hostName << endl;

    userName = getUserName();
    // cout << "Username is " << userName << endl;

    totalRam = getTotalRAM();
    //cout << "Total RAM is " << totalRam<< " MB" << endl;

    availRam = getAvailRAM();
    //cout << "Total Available RAM is " << availRam<<" MB" << endl;

    cpuLoad = GetCPULoad();
    //  cout << "CPU Load is " << cpuLoad << " %" << endl;

    processorArchitecture = getProcessorArchitecture();
    //cout << "The processor architecture is " << processorArchitecture << endl;

    processorType = getProcessorType();
    // cout << "Type of the Processor is " << processorType<<endl;

    noOfProcessors = getNoOfProcessors();
    // cout << "Number of Processors Present " << noOfProcessors<<endl;

    cpuIdleTime = getCpuIdleTime();
}
string storeData::stringify()
{
    string str;
    str += (hostName)+", ";
    str += (userName)+", ";
    str += to_string(totalRam) + "MB, ";
    str += to_string(availRam) + "MB, ";
    str += to_string(cpuLoad) + "%, ";
    str += to_string(cpuIdleTime) + "ms, ";
    str += to_string(noOfProcessors) + ", ";
    str += to_string(processorType) + ", ";

    return str;
}

void storeData::writeInFile()
{

    ofstream myFile("Stats.txt");

    //Writing into the file
    myFile << stringify() << endl << endl;
    myFile.close();

}