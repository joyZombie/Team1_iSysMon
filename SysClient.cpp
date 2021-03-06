#include"sysInt.h"
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
		string cuid;
		string hsN;
		string usN;
		int totRam;
		int avRam;
		int totDiskSp;
		int freeDiskSp;
		float cpuL;
		string prcArch;
		int nOP;
		int prcType;
		string timeStmp;

		int checkSum = 0;

		vector<parseData> data;
		stringstream storeString(s);
		string tempString;

		string line = "";

		while (getline(storeString, line)) {
			stringstream inputString(line);

			getline(inputString, cuid, ',');

			getline(inputString, hsN, ',');

			getline(inputString, usN, ',');

			getline(inputString, tempString, ',');
			totRam = atoi(tempString.c_str());
			tempString = "";

			getline(inputString, tempString, ',');
			avRam = atoi(tempString.c_str());
			tempString = "";

			getline(inputString, tempString, ',');
			totDiskSp = atoi(tempString.c_str());
			tempString = "";

			getline(inputString, tempString, ',');
			freeDiskSp = atoi(tempString.c_str());
			tempString = "";

			getline(inputString, tempString, ',');
			cpuL = atof(tempString.c_str());
			tempString = "";

			getline(inputString, prcArch, ',');

			getline(inputString, tempString, ',');
			nOP = atoi(tempString.c_str());
			tempString = "";

			getline(inputString, tempString, ',');
			prcType = atoi(tempString.c_str());
			tempString = "";

			getline(inputString, timeStmp, ',');

			parseData pD(cuid, hsN, usN, totRam, avRam, totDiskSp, freeDiskSp, cpuL, prcArch, nOP, prcType, timeStmp); //, cpuIT

			checkSum = pD.checkData();

			line = "";
		}

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
	//cout << uid;

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

		int input;

		while (true)
		{
			cout << "Command to interact with Server." << endl;
			cout << "Press 1 to get Last five record sent to the Server." << endl;
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
			case 1:
				cout << "Last 5 record sent to Server. " << endl;
				msg[0] = '1';
				send(nClientSocket, msg, 5000, 0);
				recv(nClientSocket, msg, 5000, 0);
				cout << msg << endl;
				break;
				/*case 2: cout << "Last 10 record sent to Server" << endl;
				msg[0] = '2';
				send(nClientSocket, msg, 5000, 0);
				recv(nClientSocket, msg, 5000, 0);
				cout << msg << endl;;
				break;
				case 3: cout << "I'm in case 3";
				msg[0] = 3;
				send(nClientSocket, msg, 255, 0);
				recv(nClientSocket, msg, 255, 0);
				break;*/
			default:
				exit(0);
			}
		}
	}
	return 0;
}