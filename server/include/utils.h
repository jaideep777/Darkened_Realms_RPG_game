#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "classes.h"
#include "extglobals.h"
using namespace std;


void parse(string &s, vector <string> &v); // parser
string readLine(ifstream &fin, string delim, bool encode_flag);	// read line from stream and encode if asked
string int2str(int n);	// convert from int to string

// find Entity by name and return iterator in list
list<Entity*>::iterator findEntity(string &name, list <Entity*> &elist, int skip);
// find Entity by pointer and return <Entity*> iterator
list<Entity*>::iterator findEntity_ptr(Entity * p, list <Entity*> &elist);
// find Player by pointer and return <Entity*> iterator
list<Entity*>::iterator findPlayer(Player * p, list <Entity*> &elist);
// find Player by pointer and return <Player*> iterator
list<Player*>::iterator findPlayer(Player * p, list <Player*> &elist);
// find object by name and return Object* pointer
Object * findObject(string &name, list <Entity*> objects, int skip);

// display
void initEscapeChars();
void initColors();
string encodeColorInfo(string s);
string decodeColorInfo(string s, bool ansi);

// debug
void showRooms();
void showObjects();
void showMonsters();


#endif
