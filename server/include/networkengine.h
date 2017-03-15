#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/errno.h>

#include "commons.h"
//

//network globals
#define BACKLOG 20
#define DEFAULT_BUFLEN 512
#define PORT "27015"
static const char* IP = "127.0.0.1";
static struct addrinfo * result = NULL, * ptr = NULL, hints;
static SOCKET listenSocket = -1;

int initServer();
void acceptClients();
void * getRequests(void * p);	//THREAD FCN
inline int sendActions(Player * player);
inline int sendLine(string &s, Player *player);
inline string recvLine(Player *player);

int welcomeNew(Player * player, string name);
int welcomeExisting(Player * player, string filename);
inline int welcome(Player * player);
void processRequest(Player * player);
void * handleConnection(void * p); //THREAD FCN

#endif
