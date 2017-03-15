#include "../include/networkengine.h"

inline int sendLine(string &s, Player *player){
	char * sendbuf = (char*)s.c_str();
	int iSendResult = send(player->pSocket, sendbuf, (int)strlen(sendbuf),MSG_NOSIGNAL);
	if (iSendResult == -1 && errno == EPIPE) return -1;
	return 0;
}

inline string recvLine(Player *player){
	char recvbuf1[DEFAULT_BUFLEN];
	int iResult = recv(player->pSocket, recvbuf1, sizeof(recvbuf1), 0);	// get cmd
	if (iResult > 0){
		for (int i=iResult-3; i<iResult; ++i){
			if (recvbuf1[i] == 13 || recvbuf1[i] == 10){
				recvbuf1[i] = '\0'; break;
			};
		}
		string s = recvbuf1;
		return s;
	}
	else if (iResult == 0) {
		cout << "Connection closed by client. Exiting...\n";
		delete player;
		return "";
	}
	else {
		cout << "Error in connection...please reconnect!\n";
		delete player;
		return "";
	}
}

int initServer(){
	int iResult;
	//struct addrinfo * result = NULL, * ptr = NULL, hints;
	
	// give info to create socket
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the local address and port to be used by the server
	iResult = getaddrinfo(IP, PORT, &hints, &result);
	if ( iResult == -1) {cout << "getaddrinfo failed!\n"; return 1;}

	// Create a SOCKET for the server to listen for client connections
	listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (listenSocket == -1) {cout << "Error creating ListenSocket!\n"; return 1; }
	
	//bind listenSocket with the port of obtained address
	iResult = bind( listenSocket, result->ai_addr, result->ai_addrlen);
	if ( iResult == -1) {cout << "bind() failed!\n"; return 1;}

	// Listen for incoming connection requests on the created socket
	iResult = listen(listenSocket, BACKLOG);
	if ( iResult == -1) {cout << "listen() failed!\n"; return 1;}
	else cout << "Listening on socket...\n";

	return iResult;
}

void acceptClients(){
	SOCKET clientSocket0 = accept(listenSocket, NULL, NULL);
		if (clientSocket0 == -1) {cout << "Accept failed.\n"; } 
		else {
			Player * player = new Player;		// new player
			player->pSocket = clientSocket0;	// save socket
			cout << "Created Player with SOCKET: " << player->pSocket << '\n';
			pthread_t ht;
			int i = pthread_create( &ht, NULL, handleConnection, (void*)player);	// thread to serve player
			player->handlerThread = ht;	// save thread ID in player
			usleep(500000);
			player = NULL;
		}
}

void * getRequests(void * p){	//THREAD FCN
	Player * player = (Player*)p;
	p = NULL;
	int iResult;
	char recvbuf[DEFAULT_BUFLEN];
	while(1){
		iResult = recv(player->pSocket, recvbuf, sizeof(recvbuf), 0);
		if (iResult > 0){
			for (int i=iResult-2; i<iResult; ++i){
				if (recvbuf[i] == 13 || recvbuf[i] == 10){
					recvbuf[i] = '\0'; break;
				};
			}
			string s = recvbuf;
			if (s.length() > 0){
				player->requests.push(s);
			}
		}
		else if (iResult == 0) {
			cout << "Connection closed by " << player->names[0] << ". Exiting...\n"; break;
		}
		else {
			cout << "Error in connection...please reconnect!\n"; break;
		}
		usleep(100000);
	}
}

inline int sendActions(Player * player){
	char * sendbuf = NULL;
	int iSendResult;
	if (! player->actions.empty()){
		string s = player->actions.front();
		sendbuf = (char*)s.c_str();
		player->actions.pop();
		iSendResult = send(player->pSocket, sendbuf, (int)strlen(sendbuf),MSG_NOSIGNAL);
		if (iSendResult == -1 && errno == EPIPE) return 1;
	}
	return 0;
}

int welcomeNew(Player * player, string name){

	int iSendResult, iResult;
	string filename = "../players/" + name + ".txt";
	ofstream pfout;
	pfout.open(filename.c_str());
	
	string dispName = name;
	dispName[0] = toupper(dispName[0]);
	pfout << "$ attr_begin\n";
	player->names.push_back(name); pfout << "name " << name << "\n";
	player->ansi = true;	pfout << "ansi 1\n";
	player->currentPos = &rooms[0];	pfout << "currentPos 0\n";
	player->displayName = dispName;		pfout << "displayName " << dispName << '\n';
	player->gameID = 1;
	player->life = 100;	pfout << "life 100\n";
	
	pfout << "\n$ alias_begin\n";
	player->aliases["e"] = "east"; 		pfout << "e east\n";
	player->aliases["w"] = "west";		pfout << "w west\n";
	player->aliases["n"] = "north"; 	pfout << "n north\n";
	player->aliases["s"] = "south"; 	pfout << "s south\n";
	player->aliases["l"] = "look"; 		pfout << "l look\n";
	player->aliases["i"] = "inventry"; 	pfout << "i inventry\n";
	player->aliases["d"] = "down"; 		pfout << "d down\n";
	player->aliases["u"] = "up"; 		pfout << "u up\n";

	pfout << "#\n\n$ items_begin\n-1\n\n$ end\n";
	
	string s;
	s = "\n\nYou open your transcedental eyes only to find void all around you...\n You are alone, your mind is blank...\n\n";
	if (sendLine(s,player) == -1 ) return 1;

	sleep(4);
	s = "Slowly, your mind fills with a Vision...\n\n"; 
	if (sendLine(s,player) == -1 ) return 1;
		
	sleep(4);
	s = "Vision of a land with Trees, High Mountains, Clear rivers, Beautiful Birds...\n\n"; 
	if (sendLine(s,player) == -1 ) return 1;
	
	sleep(4);
	s = "An intuition fills your mind: I must realise this world, mend it, heal it, \nshape it back to its beautiful form...\n\n";
	if (sendLine(s,player) == -1 ) return 1;

	sleep(4);
	s = "A list of races appears in your mind as your senses develop. You must \"pick\" \na race to be able to incarnate in the land of your Vision...\n(You may type \"list\" to see the races you may choose)\n\n"; 
	if (sendLine(s,player) == -1 ) return 1;

	while (1){
		s = recvLine(player);
		if (s.size() > 0){
			vector <string> v;
			parse(s,v);
			
			if (v[0] == "list"){
				s = "\n\nRaces of Earth:\nElf\nHuman\nWight\nCentaur\nKender\nGoblin\nOrc\nTroll\nOgre\nImp\nFaerie\n\nTo choose a race, \"pick <race>\".\n\n";
				if (sendLine(s,player) == -1 ) return 1;
			}
			else if (v[0] == "pick"){
				s = "\n\nYou enter into a body of a " + v[1] + " and descend onto Earth. \nYou are now ready to venture into adventure... \n\n";
				if (sendLine(s,player) == -1 ) return 1;
				break;
			}
		}
	}
	
	player = NULL;			

	pfout.clear();
	pfout.close();
	return 0;
}

int welcomeExisting(Player * player, string filename){
	ifstream pfin;
	pfin.open(filename.c_str());
	if (! pfin) cout << "Fatal Error: Could not open File!!!\n";
	string s, cmd, waste;
	int n;

	while (pfin >> s && s != "$" ){}
	pfin >> cmd;
	if (cmd == "attr_begin"){
		pfin >> waste >> s; player->names.push_back(s); cout << "name = " << s << '\n'; // name
		pfin >> waste >> n; player->ansi = (bool)n;	cout << "ansi = " << bool(n) << '\n';//ansi
		pfin >> waste >> n; player->currentPos = &rooms[n]; cout << "pos = " << n<< '\n';//currentPos
		pfin >> waste >> s; player->displayName = s; cout << "name = " << s<< '\n';//displayName
		pfin >> waste >> n; player->life = n; cout << "life = " << n<< '\n'; //life
	}
	else cout << "Error reading Player attributes!\n";
	
	while (pfin >> s && s != "$" ){}
	pfin >> cmd;
	if (cmd == "alias_begin"){
		while (pfin >> s && s != "#"){
			pfin >> cmd;
			player->aliases.insert(pair<string,string> (s,cmd));
		}
	}
	else cout << "Error reading Player aliases!\n";
	
	while (pfin >> s && s != "$" ){}
	pfin >> cmd;
	if (cmd == "items_begin"){
		Object * obj;
		while (pfin >> n && n != -1){
			++numEntities;
			obj = new Object(objectTemplates[n]);
			player->inventry.push_back(obj);
		}
		obj = NULL;
	}
	else cout << "Error reading Player Items!\n";

	while (pfin >> s && s != "$" ){}
	if (pfin >> cmd && cmd == "end"){
		player->actions.push("\n\nWelcome back!\n");
	}
	else cout << "Error reading Player end!\n";

	pfin.clear();
	pfin.close();
	player = NULL;
	return 0;
}


inline int welcome(Player * player){

	string a = "\n\n\n\n\t\tWelcome to Earth!\n\n\nWhat name do u wish?";
	if (sendLine(a, player) == -1) return 1;;

	string name;
	while (1){
		name = recvLine(player);
		if (name.length() > 0) break;
	}
	
	if (name.length() > 0){
		cout << name << '\n'; cout.flush();
		string s = "../players/" + name + ".txt";
		ifstream players_fin;
		players_fin.open(s.c_str());
		if (players_fin) 	welcomeExisting(player, s);
		else 				welcomeNew(player, name);
		// set common player attributes
		player->playerID = numPlayers;	// set playerID
		++ numPlayers;
		player->currentPos->players.push_back((Entity*)player);	// insert player into starting room
		s = player->currentPos->encodeRoom(player->ansi);	// show starting room
		player->actions.push(s);
		allPlayers.push_back(player);	// insert player into allPlayers list

		players_fin.clear();
		players_fin.close();
		return 0;
	}
	else return 1;
}


void * handleConnection(void * p){	//THREAD FCN
	Player * player = (Player*)p;
	p = NULL;
	
	welcome(player);
	
	pthread_t rt;
	int i = pthread_create(&rt , NULL, getRequests, (void*)player);	// thread to get requests
	player->requestsThread = rt;	// save thread
	sleep(1);
	
	while(1){
		processRequest(player);
		int i = sendActions(player);
		if (i != 0) {cout << "Send While Broken for " << player->names[0] <<"\n";break;};
		usleep(100000);
	}	
}


void processRequest(Player * player){
	if (! player->requests.empty()){
		string s = player->requests.front();
		player->requests.pop();
		vector <string> v;
		
		parse(s, v);

		// handle aliases
		map <string, string>:: iterator a_it = player->aliases.find(v[0]);
		if (a_it != player->aliases.end() ){
			v[0] = a_it->second;
		}

		list<Entity*>::iterator i;
		
		// exits have priority
		if (v.size() == 1){
			allFcns.find("_exit")->second.func(v, player, i);
		}
		
		// player's functions
		map <string, fcn>::iterator it;
		it = allFcns.find(v[0]);
		if (it != allFcns.end() ){
			it->second.func(v, player, i);
		}
	}
}

