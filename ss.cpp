#include<iostream>
#include<winsock.h>

#define PORT 8080

using namespace std;

struct sockaddr_in srv; 

int nSocket; 

fd_set fr, fw, fe;   

int nmaxFd;

int nArrClient[10]; 

void ProcessNewMessage(int nClientSocket)
{
	cout << endl << "Processing the Data for Client Socket :" << nClientSocket;
	char buff[256] = { 0};
	int nRet = recv(nClientSocket, buff, 256, 0);
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
		cout << endl << "The data Received From Client is:" << buff;
		//string msg = "Data Fetched Successfully";
		//char const* ptr = msg;
		send(nClientSocket, "Data Fetched Successfully", 26, 0);
		cout << endl << "********************************************************";


	}
}

void ProcessNewRequest()
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
				ProcessNewMessage(nArrClient[nIndex]);
			
			}
		}

	}
}

int main()
{
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
		cout << endl << "Start Successfully able to listening to local port : "<<PORT;
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

			ProcessNewRequest();
		
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