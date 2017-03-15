#include "../include/commons.h"

// Vect3  ************************************************************************************
Vect3::Vect3(int xx, int yy, int zz){
	x = xx; y = yy; z = zz;
}
// ---------------------------------------------------------------------------------
Vect3::Vect3(){x = y = z = 0;}

// Room ************************************************************************************
Room::Room(Vect3 xyz, string des, map <string, int> ex){
	coords = xyz;
	desc = des;
	exits = ex;
}
// ---------------------------------------------------------------------------------
void Room::addPlayer(Player * p){
	players.push_back(p);
}
// ---------------------------------------------------------------------------------
void Room::removePlayer(list <Entity*>::iterator p){
	players.erase(p);
}
// ---------------------------------------------------------------------------------
void Room::removeMonster(Entity * e){
	list <Entity*>::iterator i = findEntity_ptr(e, monsters);	// find e in monsters list
	if (i != monsters.end() ){	
		monsters.erase(i);		// when found, erase
	}
}
// ---------------------------------------------------------------------------------
void Room::msgAll(string msg){
	for (list <Entity*>::iterator i = players.begin(); i!=players.end(); ++i){
		((Player*)*i)->actions.push(decodeColorInfo(msg, ((Player*)*i)->ansi));
	}
	return;
}
// ---------------------------------------------------------------------------------
void Room::msgOthers(string msg, Player * p){
	for (list <Entity*>::iterator i = players.begin(); i!=players.end(); ++i){
		if ((Player*)*i != p)	((Player*)*i)->actions.push(decodeColorInfo(msg, ((Player*)*i)->ansi));

	}
	return;
}
// ---------------------------------------------------------------------------------
void Room::displayRoom(){
	// display mob
	cout << "Monsters: ";
	for (list <Entity*>:: iterator it = monsters.begin(); it != monsters.end(); ++it){
		cout << (*it)->displayName << " ";
	}
	cout << '\n';
	// display objects
	cout << "Objects: ";
	for (list <Entity*>:: iterator it = objects.begin(); it != objects.end(); ++it){
		cout << (*it)->displayName << " ";
	}
	cout << '\n';
    //display roomDesc
    cout << desc << '\n';
    //display exits
    cout << "Obvious exits are: ";
	for(map <string, int>::iterator it = exits.begin(); it != exits.end(); ++it){
		if (it == exits.begin()) cout << it->first << " (" << it->second << ")";
		else cout << ", " << it->first << " (" << it->second << ")";
	}
	cout<< ".\n\n";
}
// ---------------------------------------------------------------------------------
string Room::encodeRoom(bool ansi){
	string s = "";
	map <int, int> m;
	if (ansi) s += colors['R'];
	// display players
	for (list <Entity*>::iterator i = players.begin(); i != players.end(); ++i){	// construct numbers map
		s = s + (*i)->displayName + '\n';
	}
	// display Monsters
	for (list <Entity*>::iterator i = monsters.begin(); i != monsters.end(); ++i){
		++m[(((*i)->gameID)%1000)*10 + ((Monster*)*i)->status];		// number = 120010 + 4 -> 00104
	}																//			gameID + sts -> gameID[0-3]sts
	for (map <int, int>::iterator im = m.begin(); im != m.end(); ++im){		// construct string
		int ssts = int((im->first)%10); int num = int(im->first/10);
		if (im->second == 1) s = s + decodeColorInfo(monsterTemplates[num].displayName, ansi)
								 + " " + shortStatus[ssts] + "\n";
		else if (im->second > 1) s = s + wordNums[im->second] + " " + 
									 decodeColorInfo(monsterTemplates[num].pluralName,ansi) 
									 + " " + shortStatus[ssts]+ "\n";
	}
	m.clear();
	s += "\n";
	
	// display objects
	if (ansi) s += colors['M'];
	for (list <Entity*>::iterator i = objects.begin(); i != objects.end(); ++i){ 
		++m[(*i)->gameID%1000];
	}
	for (map <int, int>::iterator im = m.begin(); im != m.end(); ++im){		// construct string
		if (im->second == 1) s = s + decodeColorInfo(objectTemplates[im->first].displayName, ansi) + ", ";
		else if (im->second > 1) s = s + wordNums[im->second] + " " + 
									 decodeColorInfo(objectTemplates[im->first].pluralName,ansi) + ", ";
	}
	if (objects.size() == 1) s +=  " is here.\n\n";
	else if (objects.size() > 1) s += "are here.\n\n";
	if (ansi) s += colors['w'];
	m.clear();
	
	//display roomDesc
	s += decodeColorInfo(desc, ansi) + "\n\n";
	
	//display exits
	if (ansi) s += colors['g'];
	if (exits.size() > 0){
		s += "Obvious exits are: ";
		for(map <string, int>::iterator it = exits.begin(); it != exits.end(); ++it){
			if (it == exits.begin()) s += it->first;
			else s += ", " + it->first;
		}
		s += "."; 
	}
	else s += "There are no obvious exits!";
	if (ansi) s += colors['w']; 
	s += "\n\n";

	return s;
}


// Monster ************************************************************************************
void Monster::addEnemy(Player *p){	// adds enemy at front, takes care to not add twice
	list <Player*>::iterator it = findPlayer(p, enemies);	// look up player in enemies list
	if (it != enemies.end()) enemies.erase(it);			// found, so delete
	enemies.push_front(p);								// then push_front
	if (enemies.size() > maxEnemies) enemies.pop_back();	// store only upto max enemies
}
// ---------------------------------------------------------------------------------
void Monster::removeEnemy(Player *p){
	list<Player*>::iterator it = findPlayer(p, enemies);	// find player in monster's enemies
	if (it != enemies.end()){	
		enemies.erase(it);		// when found, erase
	}
}
// ---------------------------------------------------------------------------------
void Monster::removeAllEnemies(){
	enemies.clear();
}
// ---------------------------------------------------------------------------------
void Monster::reset(){
	enemies.clear();
	life = maxLife;
	respawnTime = monsterTemplates[gameID%1000].respawnTime;
	status = 3;
}
// ---------------------------------------------------------------------------------
void Monster::updateStatus(){
	status = int((life-1)*4/maxLife);
	if (status < 0) status = 0;	// just to avoid error
}
// ---------------------------------------------------------------------------------
void Monster::die(Player * killer){
	for (list<Player*>::iterator i = enemies.begin(); i != enemies.end(); ++i){	// remove monster from his enemies' lists
		(*i)->removeEnemy(this);
	}
	enemies.clear();	// clear own enemies
	killer->currentPos->removeMonster(this);	// remove from room
	for (int i = 0; i< inventry.size(); ++i){
		Object * obj = new Object(objectTemplates[inventry[i]]);
		killer->currentPos->objects.push_back((Entity*)obj);
	}
	respawnList.push_back((Entity*)this);
	cout << "Pushed " << gName << " to chamber!\n";
	killer->currentPos->msgAll(encodeColorInfo("#b" + killer->displayName + " lands a killing blow!#w\n"));
	killer->currentPos->msgAll(encodeColorInfo("#y" + gName + " drops Dead before you!#w\n"));	///// SHUD REMOVE FROM HERE
}
// ---------------------------------------------------------------------------------
int Monster::respawn(){
	respawnTime -= 2;
	if (respawnTime <=0 ){
		cout << "respawing " << gName << '\n';
		reset();
		rooms[roomNum].monsters.push_back((Entity*)this);
		cout << "Spawned in room num: " << roomNum << '\n';
		return 0; // respawned
	}
	else return 1; // not respawned
}


// Player ************************************************************************************
void Player::addEnemy(Entity * e){		// adds monster/being to enemies list
	list <Entity*>::iterator it = findEntity_ptr(e, enemies);	// look up entity in enemies list
	if (it == enemies.end()) enemies.push_front(e);				// not found, so push_front
}
// ---------------------------------------------------------------------------------
void Player::removeEnemy(Entity * e){
	list<Entity*>::iterator it = findEntity_ptr(e, enemies);	// find Entity/Being in enemies list
	if (it != enemies.end()){	
		enemies.erase(it);		// when found, erase
	}
}
// ---------------------------------------------------------------------------------
string Player::codeInv(){
	string s = "";
	s += "\n\tYou are carrying:\n\t";
	for (list <Entity*>::iterator it = inventry.begin(); it != inventry.end(); ++ it){
		s += decodeColorInfo((*it)->displayName, ansi) + "\n\t";
	}
	return s + "\n";
}
