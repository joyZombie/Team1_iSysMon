#include<iostream>
#include<winsock.h>
#include"si.h"
#include<string.h>
using namespace std;

#define PORT 8080
int nClientSocket;
struct sockaddr_in srv;

////////////////////////////////////////

string storeData::getHostName()
{ //Character array to store the host name
	char szPath[128] = ""; //The WSADATA structure contains information about the Windows Sockets implementation.
	WSADATA wsaData;// Creating a variable of type WSADATA ; //The WSAStartup function initiates use of the Winsock DLL by a process
	WSAStartup(MAKEWORD(2, 2), &wsaData); //gethostname()----returns the name of the host processor that the program is running on
	gethostname(szPath, sizeof(szPath));
	return szPath;
}
int storeData::getTotalRAM()
{
	int ret = 0; //MEMORYSTAUSEX IS A STURUCTURE THAT Contains information about the current state of both physical and virtual memory, including extended memory.
	MEMORYSTATUSEX m;
	m.dwLength = sizeof(m);
	GlobalMemoryStatusEx(&m);
	ret = (int)(m.ullTotalPhys >> 20); return ret;
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
void storeData::fetchData()
{
	hostName = getHostName();
	totalRam = getTotalRAM();
	availRam = getAvailRAM();
}
string storeData::stringify()
{
	string str;
	str += (hostName)+", ";
	str += to_string(totalRam) + "MB, ";
	str += to_string(availRam) + "MB, "; return str;
}
/*void storeData::writeInFile()
{
	ofstream myFile("Stats.txt");
	//Writing into the file
	myFile << stringify() << endl << endl;
	myFile.close();
}
*/








///////////////////////////////////////
int main()
{
	int nRet = 0;
	WSADATA ws;
	

	if (WSAStartup(MAKEWORD(2, 2), &ws) < 0)
	{
		cout << endl << "WSA failed to initialize.";
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else
	{
		cout << endl << "WSA is initialized.";
	}
	nClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (nClientSocket < 0)
	{
		cout << endl << "The Socket is not opened.";
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else
	{
		cout << endl << "The Socket is opened successfully.";
	}
	srv.sin_family = AF_INET;
	srv.sin_port = htons(PORT);
	srv.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&(srv.sin_zero), 0, 8);

	nRet = connect(nClientSocket, (struct sockaddr*)&srv, sizeof(srv));
	if (nRet < 0)
	{
		cout << endl << "Connection Failed";
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else
	{

		cout << endl << "Connected to the srever";
		char buff[255] = { 0 };
		recv(nClientSocket, buff, 255, 0);
		cout << endl << "Press something to see msg by server";
		getchar();
		cout << endl << buff;
		cout << endl << "Now sending the new data to the server" << endl;
		while (1)
		{
			//fgets(buff, 256, stdin);
			storeData obj;
			obj.fetchData();

			string s=obj.stringify();
			for (int x = 0; x < s.length(); x++)
			{
				buff[x] = s[x];
			}
			send(nClientSocket, buff, 256, 0);
			cout << endl << "Press any key to see the response from server";
			getchar();
			recv(nClientSocket, buff, 256, 0);
			cout << endl << buff << endl << "Now send nxt iteration data" << endl;
		}
	}
	return 0;
}