#include"systemInteraction.h"

struct sockaddr_in srv;
#define PORT 8080
int nClientSocket;

char buff[5000] = { 0 };

void storeData::sendDataToServer(string uid)
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(4000));
		string s = uid + "," + fetchNewData();

		//Parsing data at client side
		vector<string> chdb;
		string tmp = "";

		for (int k = 0; k < s.length() - 1; k++)
		{
			if (s[k] != ',')
			{
				tmp = tmp + s[k];
			}
			else
			{
				chdb.push_back(tmp);
				tmp = "";
			}
		}
		chdb.push_back(tmp);

		string hostname, clientUid, username, processorArchitecture, timeStamp;
		int totalDiskSpace, freeDiskSpace, totalRam, availRam, processorType, noOfProcessors;
		float cpuLoad;

		int checkSum = 0;

		clientUid = chdb[0];
		hostname = chdb[1];

		username = chdb[2];
		totalRam = stoi(chdb[3]);

		availRam = stoi(chdb[4]);
		totalDiskSpace = stoi(chdb[5]);

		freeDiskSpace = stoi(chdb[6]);
		cpuLoad = stof(chdb[7]);

		processorArchitecture = chdb[8];
		noOfProcessors = stoi(chdb[9]);
		processorType = stoi(chdb[10]);
		timeStamp = chdb[11];

		parseData pD(clientUid, hostname, username, totalRam, availRam, totalDiskSpace, freeDiskSpace, cpuLoad, processorArchitecture, noOfProcessors, processorType, timeStamp);
		checkSum = pD.checkData();

		s = to_string(checkSum) + "," + s;

		int x = 0;
		for (; x < s.length(); x++)
		{
			buff[x] = s[x];
		}

		send(nClientSocket, buff, 5000, 0);
	}
}

int main()
{
	int nRet = 0;
	WSADATA ws;
	cout << endl << "**********************************************System-Monitor-Client*****************************************************" << endl;

	if (WSAStartup(MAKEWORD(2, 2), &ws) < 0)
	{
		cout << endl << "WSA failed to initialize.";
		WSACleanup();
		exit(EXIT_FAILURE);
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
		cout << endl << "WSA is initialized AND The Socket is opened successfully.";
	}
	srv.sin_family = AF_INET;
	srv.sin_port = htons(PORT);
	srv.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&(srv.sin_zero), 0, 8);

	string uid;
	cout << endl << "Enter the name of client :";
	cin >> uid;
	for (int i = 0; i < uid.length(); i++)
	{
		uid[i] = tolower(uid[i]);
	}
	cout << "Hello .....   I am CLIENT " << uid << "  connecting to the Server.............";

	nRet = connect(nClientSocket, (struct sockaddr*)&srv, sizeof(srv));
	if (nRet < 0)
	{
		cout << endl << "Connection Failed";
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else
	{
		recv(nClientSocket, buff, 255, 0);
		cout << endl << buff;
		cout << endl << "Connected to the server";
		cout << endl << "Now sending the System Information to the server............" << endl;

		storeData obj;
		obj.intialiseFetchDataThread();

		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		obj.intialiseSendDataThread(uid);

		char input;

		while (true)
		{
			cout << "Command to interact with Server." << endl;
			cout << "Press 1 to get Last five record sent to the Server." << endl;
			cout << "Press * to get Last ten record sent to the Server." << endl;
			cout << "Press # to delete my all data sent to the Server." << endl;
			cout << "Press $ to delete my all data sent to the Server AND CLOSE THE CLIENT." << endl;
			cout << "Press 2 to CLOSE the Client." << endl;
			//cout << "." << endl;
			cin >> input;
			char msg[5000] = { 0 };

			msg[0] = '0';
			msg[1] = ',';
			int i = 2, j = 0;
			while (j < uid.length())
			{
				msg[i++] = uid[j++];

			}
			msg[i] = '~';
			switch (input)
			{
			case '1':
				cout << "Last 5 record sent to Server. " << endl;
				msg[0] = '1';
				send(nClientSocket, msg, 5000, 0);
				recv(nClientSocket, msg, 5000, 0);
				cout << msg << endl;
				break;
			case '*': cout << "Last 10 record sent to Server" << endl;
				msg[0] = '*';
				send(nClientSocket, msg, 5000, 0);
				recv(nClientSocket, msg, 5000, 0);
				cout << msg << endl;;
				break;
			case '#': cout << "Deleting my ALL data from the server" << endl;
				msg[0] = '#';
				send(nClientSocket, msg, 255, 0);
				break;
			case '$': cout << "Deleting my ALL data from the server AND CLOSING THE CLIENT  : " << uid << endl;
				msg[0] = '#';
				send(nClientSocket, msg, 255, 0);
				exit(0);
			default:
				exit(0);
			}
		}
	}
	return 0;
}
