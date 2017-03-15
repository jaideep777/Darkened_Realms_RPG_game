#ifndef PFCNS_H
#define PFCNS_H
// Player's Functions!!!

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "commons.h"
using namespace std;

#define C(x) void x(vector <string> &cmd, Player * p, list<Entity*>::iterator &it)

void initFcns();
void initObjFcns();

#endif
