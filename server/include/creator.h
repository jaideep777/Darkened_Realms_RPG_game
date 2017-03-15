#ifndef CREATER_H
#define CREATER_H

#include <iostream>
#include <fstream>
#include <string>
#include "commons.h"
using namespace std;

/*******
CREATION:
real objects are created only when they are required to exist 
typically along with creation of rooms. from the data files, 
only templates are created. Same with monsters, compounds etc.
when templates are created, their gameID refers to their tamplate numnber.
when real objects are created, as many same number of objects are created as 
are required, each having a unique gameID.

*******/

int initObjects();
int initMonsters();
int initRooms();
int initSpells();

#endif

