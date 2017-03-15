#ifndef GLOBALS_H
#define GLOBALS_H

map <char, string> colors;
string wordNums[11] = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten"};
string shortStatus[4] = {"(dying)", "(bleeding)", "(injured)", ""};
string longStatus[4] = {"is mortally wounded.", "is lightly wounded.", "is bruised", "is in top shape."};
string hitMsgVerb[6] = {"tickle", "tap", "hurt", "sting", "send", "destroy"};
string hitMsgAdverb[6] = {"lightly", "gently", "mildly", "painfully", "a bone crushing blow", "utterly"};
map <string, char> escapeChars;

vector <Room> rooms;
vector <Object> objectTemplates;
vector <Monster> monsterTemplates;
map <string, fcn> allFcns;
vector <fcn> gameFcns;
vector <spell> allSpells;
map <string, spell> Spells;

vector <Entity*> allObjects;
vector <Entity*> allMonsters;
list <Player*> allPlayers;

int numEntities = 0;
int numPlayers = 0;

pthread_t gameAI;
pthread_t roomAI;
pthread_t areaAI;

list <Entity*> respawnList;

#endif

