#include"Header.h"

#define PORT 8080

using namespace std;

struct sockaddr_in srv;

int nSocket;

fd_set fr, fw, fe;

int nmaxFd;

int nArrClient[10];
/////////////////////////////////////////////////////////////////////////////////
int qstate;
void insert(MYSQL* conn, vector<string>& db);
void display(MYSQL* conn);

void display(MYSQL* conn);
void ProcessNewMessage(int nClientSocket, MYSQL* conn);
void ProcessNewRequest(MYSQL* conn);


void insert(MYSQL* conn, vector<string>& db)
{
	int qstate = 0;
	stringstream ss;
	//cout << " Connection to database successful:" << endl;

	string hostname, clientUid, username, processorArchitecture, timeStamp;
	int socketID, totalDiskSpace, freeDiskSpace, totalRam, availRam, cpuIdleTime, processorType, noOfProcessors;
	float cpuLoad;

	socketID = stoi(db[0]);
	//cout << socketID << endl;
	clientUid = db[1];
	hostname = db[2];
	//cout << hostname << endl;
	username = db[3];
	totalRam = stoi(db[4]);
	//cout << hostname << endl;
	availRam = stoi(db[5]);
	totalDiskSpace = stoi(db[6]);
	freeDiskSpace = stoi(db[7]);
	cpuLoad = stof(db[8]);
	processorArchitecture = db[9];
	processorType = stoi(db[10]);
	noOfProcessors = stoi(db[11]);
	timeStamp = db[12];

	ss << " INSERT INTO sysmonitor (socketID,clientUid, hostname, username, totalRam, availRam, totalDiskSpace, freeDiskSpace, cpuLoad, processorArchitecture, processorType, noOfProcessors, timeStamp) values ('" << socketID << "','" << clientUid << "','" << hostname << "','" << username << " ','" << totalRam << "','" << availRam << "','" << totalDiskSpace << "','" << freeDiskSpace << "','" << cpuLoad << "','" << processorArchitecture << "','" << processorType << "','" << noOfProcessors << "','" << timeStamp << "')"; 

	string query = ss.str();
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);


	if (qstate == 0)
	{

		cout << " Record inserted successfully ..." << endl;
	}
	else
	{
		cout << " Error, data not inserted..." << endl;
	}
}


void display(MYSQL* conn)
{
	MYSQL_ROW row;
	MYSQL_RES* res;
	string query = "SELECT * FROM sysmonitor";
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			printf("Socket ID: %s, Host Name: %s, Username: %s, Total RAM: %s, Available RAM : %s, CPU Load: %s, CPU IDLE Time: %s, Processor Architecture: %s, Processor Type: %s, No of Processors: %s, Timestamp: %s\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10]);
		}
	}

	else
	{
		cout << "Query failed: " << mysql_error(conn) << endl;
	}


}

//////////////////////////////////////////////////////////////////////////////

void ProcessNewMessage(int nClientSocket, MYSQL* conn)
{
	cout << endl << "Processing the Data for Client Socket :" << nClientSocket << endl;
	char buff[5000] = { 0 };
	int nRet = recv(nClientSocket, buff, 5000, 0);
	if (nRet < 0)
	{
		cout << endl << "Something wrong happened Unable to connect to client closing connection...";
		closesocket(nClientSocket);
		for (int indx = 0; indx < 10; indx++)
		{
			if (nArrClient[indx] == nClientSocket)
			{
				nArrClient[indx] = 0;
				break;
			}
		}

	}
	else
	{
		//cout << endl << "The data Received From Client is: " << buff << endl;
		if (buff[0] == '1')
		{

			MYSQL_ROW row;
			MYSQL_RES* res;
			string nCs;
			string m;
			m = to_string(nClientSocket);
			nCs = m;
			string z;
			z = "3";
			//int nCs = nClientSocket;
			//cout << nCs;
			//string a = "top '" + z + "'";
			//string b = "SELECT * FROM sysmonitor where socketID = ' "+ nCs + "'";
			string query = "SELECT * FROM sysmonitor where socketID = ' " + nCs + "'  order by timeStamp desc";
			const char* q = query.c_str();
			string s;
			qstate = mysql_query(conn, q);
			if (!qstate)
			{
				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					s = s + "Socket ID: " + row[0] + "," + "Client UID: " + row[1] + "," + "Host Name: " + row[2] + "," + "Username: " + row[3] + "," + "Total RAM: " + row[4] + "," + "Available RAM: " + row[5] + "," + "Total Disk Space: " + row[6] + "," + "Free Disk Space: " + row[7] + "," + "CPU Load: " + row[8] + "," + "CPU IDLE Time: " + row[9] + "," + "Processor Architecture: " + row[10] + "," + "Processor Type: " + row[11] + "," + "No of Processors: " + row[12] + "," + "Timestamp: " + row[13];
				}
			}

			else
			{
				cout << "Query failed: " << mysql_error(conn) << endl;
			}
			int x = 0;
			for (; x < s.length(); x++)
			{
				buff[x] = s[x];
			}


			send(nClientSocket, buff, 5000, 0);
		}
		else
		{
			//data integrity check at server side
			vector<string> chdb;
			string tmp = "";
			string sto = buff;
			//cout << endl << "The data Received From Client is: " << sto << endl;
			
			for (int i = 0; i < sto.length()-1; i++)
			{
				if (buff[i] != ',')
				{
					tmp = tmp + buff[i];
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
			int chkS = 0;
			int checkSum = 0;
			
			chkS = stoi(chdb[0]);
			clientUid = chdb[1];
			hostname = chdb[2];
			
			username = chdb[3];
			totalRam = stoi(chdb[4]);
			
			availRam = stoi(chdb[5]);
			totalDiskSpace = stoi(chdb[6]);

			freeDiskSpace = stoi(chdb[7]);
			cpuLoad = stof(chdb[8]);

			processorArchitecture = chdb[9];
			noOfProcessors = stoi(chdb[10]);
			processorType = stoi(chdb[11]);
			timeStamp = chdb[12];

			parseData pD(clientUid, hostname, username, totalRam, availRam, totalDiskSpace, freeDiskSpace, cpuLoad, processorArchitecture, noOfProcessors, processorType, timeStamp, chkS);

			checkSum = pD.checkData();

			cout << cpuLoad << endl;

			//cout << "Client side checksum: " << chkS << endl;
			//cout << "Server side checksum: " << checkSum << endl;

			if (chkS == checkSum)
				cout << "Data fetched is untampered" << endl;
			else
				cout << "Data is tampered" << endl;

			////////////////////////////////

			string cid;
			string HN;
			string UN;
			string TR;
			string AR;
			string TDS;
			string FDS;
			string CL;
			string CIT;
			string PA;
			string NOP;
			string PT;
			string TS;
			string chk;

			stringstream ss(buff);
			vector<string> db;
			string socketid = to_string(nClientSocket);
			db.push_back(socketid);

			string line1 = "";

			while (getline(ss, line1))
			{
				stringstream inputString(line1);

				getline(inputString, chk, ',');

				getline(inputString, cid, ',');
				db.push_back(cid);
				getline(inputString, HN, ',');
				db.push_back(HN);
				getline(inputString, UN, ',');
				db.push_back(UN);
				getline(inputString, TR, ',');
				db.push_back(TR);
				getline(inputString, AR, ',');
				db.push_back(AR);
				getline(inputString, TDS, ',');
				db.push_back(TDS);
				getline(inputString, FDS, ',');
				db.push_back(FDS);
				getline(inputString, CL, ',');
				db.push_back(CL);
				getline(inputString, PA, ',');
				db.push_back(PA);
				getline(inputString, NOP, ',');
				db.push_back(NOP);
				getline(inputString, PT, ',');
				db.push_back(PT);
				getline(inputString, TS, ',');
				db.push_back(TS);

				line1 = "";
			}


			if (conn) {

				puts("Successful connection to database!");

				insert(conn, db);
				//display(conn);

			}
			else {
				puts("Connection to database has failed!");
			}
		}
	}
}

void ProcessNewRequest(MYSQL* conn)
{

	if (FD_ISSET(nSocket, &fr))
	{
		int nLen = sizeof(struct sockaddr);
		int nClientSocket = accept(nSocket, NULL, &nLen);
		if (nClientSocket > 0)
		{
			int indx = 0;
			for (; indx < 10; indx++)
			{
				if (nArrClient[indx] == 0)
				{
					nArrClient[indx] = nClientSocket;
					send(nClientSocket, "Got the connection successfully", 30, 0);
					break;
				}
			}
			if (indx == 10)
			{
				cout << endl << "No space for a new client/connection";

			}

		}
	}
	else
	{

		for (int nIndex = 0; nIndex < 10; nIndex++)
		{
			if (FD_ISSET(nArrClient[nIndex], &fr))
			{
				ProcessNewMessage(nArrClient[nIndex], conn);

			}
		}

	}
}

int main()
{
	/**************************************************************************************************/
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "Bigoht$1512", "testdb", 3306, NULL, 0);
	/**************************************************************************************************/
	int nRet = 0;

	WSADATA ws;

	if (WSAStartup(MAKEWORD(2, 2), &ws) < 0)
	{
		cout << endl << "WSA failed to initialize." << endl;
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else
	{
		cout << "WSA is initialized." << endl;
	}
	nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (nSocket < 0)
	{
		cout << "The Socket is not opened." << endl;
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else
	{
		cout << "The Socket is opened successfully." << endl;
	}

	srv.sin_family = AF_INET;
	srv.sin_port = htons(PORT);
	srv.sin_addr.s_addr = INADDR_ANY;
	memset(&(srv.sin_zero), 0, 8);
	u_long optval = 0;
	nRet = ioctlsocket(nSocket, FIONBIO, &optval);
	if (nRet != 0)
	{
		cout << endl << "fail blocking socket ioctl call";
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else
	{

	}

	nRet = bind(nSocket, (sockaddr*)&srv, sizeof(sockaddr));
	if (nRet < 0)
	{
		cout << "Fail to bind to Local port";
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else
	{

	}

	nRet = listen(nSocket, 10);

	if (nRet < 0)
	{
		cout << endl << "Fail to start to listen to Local port";
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else
	{
		cout << endl << "Start Successfully able to listening to local port : " << PORT;
	}

	nmaxFd = nSocket;
	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;

	while (1)
	{

		FD_ZERO(&fr);
		FD_ZERO(&fw);
		FD_ZERO(&fe);

		FD_SET(nSocket, &fr);
		FD_SET(nSocket, &fe);

		for (int nIndex = 0; nIndex < 10; nIndex++)
		{
			if (nArrClient[nIndex] != 0)
			{
				FD_SET(nArrClient[nIndex], &fr);
				FD_SET(nArrClient[nIndex], &fe);
			}
		}



		nRet = select(nmaxFd + 1, &fr, &fw, &fe, &tv);

		if (nRet > 0)
		{
			cout << endl << "Data on PORT ..... Processing now...";

			if (FD_ISSET(nSocket, &fe))
			{
				cout << endl << "There is exception....";
			}
			if (FD_ISSET(nSocket, &fw))
			{
				cout << endl << "Ready to write something....";
			}
			if (FD_ISSET(nSocket, &fr))
			{

				cout << endl << "Ready to read. Something at the PORT....";
			}

			ProcessNewRequest(conn);

		}
		else if (nRet == 0)
		{

		}
		else
		{
			cout << endl << "failed select call";
			WSACleanup();
			exit(EXIT_FAILURE);
		}
	}

	return 0;


}
