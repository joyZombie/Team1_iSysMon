#include "sysInt.h"

string storeData::getHostName()
{
    char szPath[128] = "";
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
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
void storeData::getRamInformation()
{
    int ret = 0;
    MEMORYSTATUSEX m;
    m.dwLength = sizeof(m);
    GlobalMemoryStatusEx(&m);

    totalRam = (int)((m.ullTotalPhys >> 20));
    availRam = (int)(m.ullAvailPhys >> 20);

}

void storeData::getDiskSpace()
{
    BOOL fResult;
    unsigned __int64 i64FreeBytesToCaller,
        i64TotalBytes,
        i64FreeBytes;
    fResult = GetDiskFreeSpaceEx(L"C:",
        (PULARGE_INTEGER)&i64FreeBytesToCaller,
        (PULARGE_INTEGER)&i64TotalBytes,
        (PULARGE_INTEGER)&i64FreeBytes);
    if (fResult)
    {
        totalDiskSpace = i64TotalBytes / (1024 * 1024 * 1024);
        freeDiskSpace = i64FreeBytes / (1024 * 1024 * 1024);
    }
}

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

float storeData::getCpuLoad()
{
    FILETIME idleTime, kernelTime, userTime;
    float cpuLoad = GetSystemTimes(&idleTime, &kernelTime, &userTime) ? CalculateCPULoad(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime) + FileTimeToInt64(userTime)) : -1.0f;
    return cpuLoad * 100;
}

void storeData::getProcessorInformation()
{
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    processorArchitecture = to_string(sysInfo.wProcessorArchitecture);
    string ret = processorArchitecture;

    if (ret == "0")
        processorArchitecture = "x86";
    else if (ret == "5")
        processorArchitecture = "ARM";
    else if (ret == "6")
        processorArchitecture = "Intel Itanium-based";
    else if (ret == "9")
        processorArchitecture = "x64(AMD or Intel)";
    else if (ret == "12")
        processorArchitecture = "ARM64";
    else
        processorArchitecture = "Unknown";

    processorType = sysInfo.dwProcessorType;
    noOfProcessors = sysInfo.dwNumberOfProcessors;
}

int storeData::getCpuIdleTime()
{
    LASTINPUTINFO li = { 0 };
    li.cbSize = sizeof(LASTINPUTINFO);

    GetLastInputInfo(&li);

    return GetTickCount64() - li.dwTime;
}

string storeData::getCurrentTime()
{
    auto start = std::chrono::system_clock::now();
    auto legacyStart = std::chrono::system_clock::to_time_t(start);
    char tmBuff[30];
    ctime_s(tmBuff, sizeof(tmBuff), &legacyStart);

    return tmBuff;
}

void storeData::fetchData()
{
    hostName = getHostName();

    userName = getUserName();

    getRamInformation();

    getDiskSpace();

    cpuLoad = getCpuLoad();

    getProcessorInformation();

    //cpuIdleTime = getCpuIdleTime();

    timeStamp = getCurrentTime();
}
string storeData::stringify()
{
    string str;
    str += (hostName)+", ";
    str += (userName)+", ";
    str += to_string(totalRam) + "MB, ";
    str += to_string(availRam) + "MB, ";
    str += to_string(totalDiskSpace) + "GB, ";
    str += to_string(freeDiskSpace) + "GB, ";
    str += to_string(cpuLoad) + "%, ";
    //str += to_string(cpuIdleTime) + "ms, ";
    str += processorArchitecture + ", ";
    str += to_string(noOfProcessors) + ", ";
    str += to_string(processorType) + ", ";
    str += timeStamp;
    return str;
}

void storeData::timerStart()
{
    while (true)
    {
        fetchData();

        int count = 0;

        if (count < 1000)
        {
            v.push_back(stringify());
            count++;
        }
        else
        {
            v.erase(v.begin());
            v.push_back(stringify());
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}

void storeData::intialiseFetchDataThread()
{
    v.resize(1000);
    thread t1(&storeData::timerStart, this);
    t1.detach();
}

void storeData::intialiseSendDataThread(string uid)
{
    thread t(&storeData::sendDataToServer, this, uid);
    t.detach();
}
string storeData::fetchNewData()
{
    static string str;
    if (!v.empty())
    {
        str = v.back();
        v.erase(v.end() - 1);
        return str;
    }
    else
    {
        str = "NO DATA AVAILABLE";
        return str;
    }
}