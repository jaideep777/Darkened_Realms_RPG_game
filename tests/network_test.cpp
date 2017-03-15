#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>
//#include <string.h>
#include <string>
#include <queue>
using namespace std;
//#include "classes.h"
//

//network globals
typedef int SOCKET;
#define BACKLOG 20
#define DEFAULT_BUFLEN 100
#define PORT "27015"
const char* IP = "127.0.0.1";
//char recvbuf[DEFAULT_BUFLEN];
int recvbuflen = DEFAULT_BUFLEN;
int iResult, iSendResult;
struct addrinfo * result = NULL, * ptr = NULL, hints;
SOCKET listenSocket = -1;
sockaddr_in service;

int numClients=0;

int initServer(){
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the local address and port to be used by the server
	iResult = getaddrinfo(IP, PORT, &hints, &result);
		if ( iResult == -1) {cout << "getaddrinfo failed!\n"; return 1;}

	// Create a SOCKET for the server to listen for client connections
	listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (listenSocket == -1) {cout << "Error creating ListenSocket!\n"; return 1; }
	
	//bind listenSocket with service
	iResult = bind( listenSocket, result->ai_addr, result->ai_addrlen);
	if ( iResult == -1) cout << "bind() failed!\n";

	// Listen for incoming connection requests on the created socket
	iResult = listen(listenSocket, BACKLOG);
	if ( iResult == -1) cout << "listen() failed!\n";
	else cout << "Listening on socket...\n";

return iResult;
}
//
//void handleConnection(Player * player);

int main(){
	initServer();
	SOCKET clientSocket0 = accept(listenSocket, NULL, NULL);
	while(1){
			if (clientSocket0 == -1) {cout << "Accept failed.\n"; } 
			else {
				char recvbuf[DEFAULT_BUFLEN];
				iResult = recv(clientSocket0, recvbuf, sizeof(recvbuf), 0);
				for (int i=0; i<iResult; ++i){
					cout << int(recvbuf[i]) << "-";
				}
				cout << "\nBytes Received: " << iResult << '\n';
				if (iResult >0){
					for (int i=iResult-2; i<=iResult; ++i){
						if (recvbuf[i] == 13 || recvbuf[i] == 10){
							recvbuf[i] = '\0'; break;
						};
					}
					string s = recvbuf;
					if (s.length() > 0){
						cout << "string received: " << s << s.length() << '\n';
						s = "***" + s + "***";
						cout << "string sent: \n" << "." << s << "." << '\n';
						char sendbuf[] = "HIIIIIIIII";
						// sendbuf = (char*)s.c_str();
						iSendResult = send(clientSocket0, sendbuf, sizeof(sendbuf),0);
						cout << "Bytes sent = " << iSendResult << '\n';
					}
				}	
				else if (iResult == 0) {
					cout << "Connection closed by client. Exiting...\n"; return 1;
				}
				else {
					cout << "Error in connection...please reconnect!\n";
				}
			}
	}
}

