extern map <char, string> colors;
extern string wordNums[11];
extern string shortStatus[4];
extern string longStatus[4];
extern string hitMsgVerb[6];
extern string hitMsgAdverb[6];
extern map <string, char> escapeChars;

extern vector <Room> rooms;
extern vector <Object> objectTemplates;
extern vector <Monster> monsterTemplates;
extern map <string, fcn> allFcns;

extern vector <fcn> gameFcns;
extern vector <spell> allSpells;
extern map <string, spell> Spells;

extern vector <Entity*> allObjects;
extern vector <Entity*> allMonsters;
extern list <Player*> allPlayers;

extern int numEntities;
extern int numPlayers;

extern pthread_t gameAI;
extern pthread_t roomAI;
extern pthread_t areaAI;

extern list <Entity*> respawnList;
