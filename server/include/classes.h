#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <queue>
using namespace std;


/*
	CLASS HIEARCHY

		Entity _________ 
	     /    \		    \
	 Object  Being    Player    
               |	
            Monster


	Live beings have list of Entities (Compound, Object)
	Room has list of Entities (Beings, Objects etc)

	inventry structure (all inventries are vector <int> except player's inventry) :
	Room: (beings, players, objects) index of the object in that allEntities vector
	Monster: index of the object from the template vectors.

	for templates, gameID = template number
	for real objects, gameID = unique identification ID

	USE OF CONTAINERS:
		for commands, exits, names etc, (things that dont change), maps & vectors are used
		inventry, monster/object lists need traversal anyway to determine matching name, 
			and need quick insertion/removal. so list is used

	Note On Pointers:
	
	Objects and what points to them:
		Monster: its Enemies' enemy lists; room; 
		Object: Room / player Inventry
*/

typedef int SOCKET;

// a generic 3D vector
struct Vect3{
	int x;
	int y;
	int z;
	Vect3(int xx, int yy, int zz);
	Vect3();
};

// struct to hold AI actions of entities along with their frequency
struct aiAct{
	string action;
	int delay;
	aiAct(string _action, int _delay){action = _action; delay = _delay;};
	aiAct();
};

struct spell{
	string name;
	int damage;
	string mantra;
};

// the fundamental object in the game, from which all others are derived
// all lists will be of this type, to acces members of the list,
// typecast pointers into required class and use
class Entity{
public:
	vector <string> names;
	string displayName;
	string pluralName;
	string looks;
	string gName;
	int type;
	int gameID;
};

// a real object which can really be created.
// Also serves as a template for objects.
class Object: public Entity{
public:
	vector <string> commands;	// commands understood by object, e.g. split, unlock
};

// generic living objects which can move about or perform AI
class Being: public Entity{
public:
};

class Player;

class Corpse: public Entity{
	public:
	Entity * body;
	vector <string> messages;
};

// monsters
class Monster: public Being{
public:
	// constants
	int aiSpeed;
	int maxEnemies;
	int roomNum;
	int maxLife;
	
	vector <string> commands;	// commands understood by monster, e.g. kill
	vector <aiAct> actions;	// AI-actions performed by monster, e.g. speak, move
	vector <int> inventry;		// list of template numbers that the Being carries
	
	void addEnemy(Player *p);
	void removeEnemy(Player *p);
	void removeAllEnemies();
	void die(Player * killer);
	void updateStatus();
	int respawn();
	void reset();

	// variables
	int life;
	int respawnTime;		// time left till respawn
	list <Player*> enemies;	// * players whom this monster has attacked
	int status;
};

struct Exit{
	string name;
	Vect3 num;
};

// room, of course
class Room{
public:
	Vect3 coords;
	int roomNum;
	string desc;
	map <string, int> exits;	// map <exit_name, exit_room_number>
	vector <string> commands;	// commands understood by room, e.g. search
	list <Entity*> monsters;
	list <Entity*> objects;
	list <Entity*> players;
	
	Room(){};
	Room(Vect3 xyz, string des, map <string, int> ex);
	void displayRoom();
	string encodeRoom(bool ansi);
	void addPlayer(Player * p);
	void removePlayer(list <Entity*>::iterator p);
	void removeMonster(Entity * e);
	void msgAll(string msg);	////// ADD FCN AS CLASS FCN
	void msgOthers(string msg, Player * p);
};

// and of course, player. He/She is somewhat special, so its not derived from live
class Player: public Entity{
public:
	int playerID;
	SOCKET pSocket;
	queue <string> requests;
	queue <string> actions;

	Room * currentPos;
	bool ansi;
	map <string, string> aliases;
	int life;
	list <Entity*> inventry;
	list <Entity*> enemies;

	pthread_t handlerThread;
	pthread_t requestsThread;

	void addEnemy(Entity * e);
	void removeEnemy(Entity * e);
	string codeInv();
};

// a class to store pointers to functions
class fcn{
public:
	fcn(void (*f)(vector <string> &cmd, Player * p, list<Entity*>::iterator &it)){func = f;};
	void (* func)(vector <string> &cmd, Player * p, list<Entity*>::iterator &it);
};

#endif
