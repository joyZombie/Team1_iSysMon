#include<iostream>
#include<winsock.h>
using namespace std;

#define PORT 8080
int nClientSocket;
struct sockaddr_in srv;
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
		cout << endl << "Now sending the new data to the server" <<endl;
		while (1)
		{
			fgets(buff, 256, stdin);
			send(nClientSocket, buff, 256, 0);
			cout << endl << "Press any key to see the response from server";
			getchar();
			recv(nClientSocket, buff, 256, 0);
			cout << endl << buff << endl << "Now send nxt iteration data"<<endl;
		}
	}
	return 0;
}
