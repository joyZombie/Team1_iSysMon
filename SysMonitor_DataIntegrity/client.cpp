/*
* ####IGNORE CODE BETWEEN "#if 0   #endif"
*/

#include "sysInteraction.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
using namespace std;

#define PORT 8080
int nClientSocket;
struct sockaddr_in srv;

class SendData {

};

void main()
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
	//srv.sin_addr.s_addr = inet_addr("127.0.0.1");
	InetPton(AF_INET, _T("127.0.0.1"), &srv.sin_addr.s_addr);
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
#if 0
			storeData obj;
			obj.fetchData();

			string str = obj.stringify();
#endif
			int i = 0;
#if 0
			while (i != str.length())
			{
				buff[i] = str[i];
				i++;
			}
#endif
			//fetching data
			string arr;
			int securityKey = 97;
			
			storeData obj;
			obj.fetchData();
			arr = obj.stringify();
			

			
			//Parsing data at client side
			string hsN;
			string usN;
			int totRam;
			int avRam;
			float cpuL;
			int cpuIT;
			int nOP;
			int prcType;			

			vector<parseData> data;
			stringstream storeString(arr);
			string tempString;

			string line = "";
			string chkSum;

			while (getline(storeString, line)) {
				stringstream inputString(line);

				getline(inputString, hsN, ',');
				getline(inputString, usN, ',');

				getline(inputString, tempString, ',');
				totRam = atoi(tempString.c_str());
				tempString = "";

				getline(inputString, tempString, ',');
				avRam = atoi(tempString.c_str());
				tempString = "";

				getline(inputString, tempString, ',');
				cpuL = atof(tempString.c_str());
				tempString = "";

				getline(inputString, tempString, ',');
				cpuIT = atoi(tempString.c_str());
				tempString = "";

				getline(inputString, tempString, ',');
				nOP = atoi(tempString.c_str());
				tempString = "";

				getline(inputString, tempString, ',');
				prcType = atoi(tempString.c_str());
				tempString = "";
				

				parseData pD(hsN, usN, totRam, avRam, cpuL, cpuIT, nOP, prcType);

				int checkSum = pD.checkData();
				arr += to_string(checkSum);
#if 0
				//convert checkSum into string datatype
				stringstream conv;
				conv << checkSum;
				conv >> chkSum;
				//append checkSum at end of original data
				arr.append(chkSum);
#endif


				//for multiple data streams
				data.push_back(pD);

				line = "";

			}

			
			int temp = arr.length();

			//storing final data
			for (int j = 0; j < temp; j++)
			{
				buff[j] = arr[j];
			}


#if 0
			stringstream ss(str);
			string tempString;
			string ram;
			int age;

			// Making the string empty
			str = "";

			// Running loop till end of stream
			// and getting every word
			string line = "";
			while (getline(ss, line)) {
				stringstream inputString(line);


				getline(inputString, ram, ',');
				getline(inputString, tempString, ',');
				age = atoi(tempString.c_str());
				line = "";
		}
#endif

#if 0
				string hsN;
				string usN;
				int totRam;
				int avRam;
				float cpuL;
				int prcArch;
				int prcType;
				int nOP;
				int cpuIT;
				string tempString = "";

				stringstream inputString;
				line = "";
#endif


			
#if 0

			stringstream ss;
			ss << temp;
			string s;
			ss >> s;

#endif

			//fgets(buff, 256, stdin);

			send(nClientSocket, buff, sizeof(buff), 0);
			cout << endl << "Press any key to see the response from server";
			getchar();
			recv(nClientSocket, buff, 256, 0);
			cout << endl << buff << endl << "Now send nxt iteration data" << endl;
		}
	}
}
