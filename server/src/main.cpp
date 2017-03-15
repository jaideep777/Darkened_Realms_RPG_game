#include <iostream>
#include <cstdlib>
#include "../include/classes.h"
#include "../include/globals.h"
#include "../include/utils.h"
#include "../include/functions.h"
#include "../include/networkengine.h"
#include "../include/creator.h"
#include "../include/ai.h"


int main(){
	initColors();
	initEscapeChars();
	initSpells();
	initObjects();
	initMonsters();
	initFcns();
	initObjFcns();
	initRooms();

	showObjects();
	showMonsters();
	showRooms();

	initServer();

	pthread_create(&roomAI , NULL, roomAIfn, NULL);	// thread for room AI
	while(1) acceptClients();

	return 0;
}
