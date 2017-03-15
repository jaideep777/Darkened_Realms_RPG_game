// Player's Functions!!!

#include "../include/functions.h"
#include <unistd.h>
using namespace std;

#define C(x) void x(vector <string> &cmd, Player * p, list<Entity*>::iterator &it)
#define CERR(x) p->actions.push(x)
#define MSG(x) p->actions.push(x)
#define FCN(x,y) allFcns.insert(pair <string, fcn> (x, fcn(y)));

inline Entity * castSpell(vector <string> &cmd, Player * p){
	map <string, spell>::iterator sp = Spells.find(cmd[0]);
	if (cmd.size() > 3){
		CERR("Correct syntax:" + sp->second.name + "<monster / name (optional)> <number (optional)>");
		return NULL;
	}
	else if (cmd.size() == 1){
		if (p->enemies.size() > 0) {
			Monster * mon = (Monster*)p->enemies.front();
			MSG(decodeColorInfo(sp->second.mantra, p->ansi));
			mon->life -= sp->second.damage;
			int verbNum = (sp->second.damage*6/mon->maxLife);
			MSG("You " + hitMsgVerb[verbNum] + " " + mon->gName + " " + hitMsgAdverb[verbNum] + "with your magic!\n\n");
			if (mon->life <= 0) mon->die(p);
			return (Entity*)mon;
		}
		else {
			CERR(sp->second.name + " whom??\n");
			return NULL;
		}
	}
	else{
		int skip;
		if (cmd.size() == 3) {
			skip = atoi(cmd[2].c_str());
			if (skip == 0) skip = 1;
		}
		else skip = 1;

		list<Entity*>::iterator i = findEntity(cmd[1], p->currentPos->monsters,skip);
		if (i!= p->currentPos->monsters.end()){
			Monster* mon = ((Monster*)*i);
			((Monster*)*i)->addEnemy(p);	
			p->addEnemy(*i);
			MSG(decodeColorInfo(sp->second.mantra, p->ansi));
			mon->life -= sp->second.damage;
			int verbNum = (sp->second.damage*6/mon->maxLife);
			MSG("You " + hitMsgVerb[verbNum] + " " + mon->gName + " " + hitMsgAdverb[verbNum] + "with your magic!\n\n");
			if (mon->life <= 0) mon->die(p);
			return (Entity*)mon;
		}
		else {
			CERR("No " + cmd[1] + " here\n");
			return NULL;
		}
	}
}

C(ansi){
	if (cmd.size() != 2){
		CERR("Correct syntax: ansi <on/off>\n\n");
	}
	else {
		if (cmd[1] == "on"){
			p->ansi = true;
			string s = encodeColorInfo("#Ra#Bn#Ys#Gi#w has been turned on.\n\n");
			p->actions.push(decodeColorInfo(s, true));
		}
		else if (cmd[1] == "off"){
			p->ansi = false;
			p->actions.push("Ansi has been turned off.\n\n");
		}
		else{
			CERR("Correct syntax: ansi <on/off>\n\n");
		}
	}
}

C(help){
	p->actions.push("\nRemember where you came from; think twice before u take a step\n");
}

C(_exitR){
	map <string, int>::iterator ex_it;
	ex_it = p->currentPos->exits.find(cmd[0]);
	if (ex_it != p->currentPos->exits.end() ){
		Room * destRoom = &rooms[ex_it->second];
		string s = destRoom->encodeRoom(p->ansi);
		p->actions.push(s);
		list <Entity*>::iterator j = findPlayer(p, p->currentPos->players);	// find player in room's list
		if (j != p->currentPos->players.end()) {
			p->currentPos->removePlayer(j);	// remove self from room
			s = encodeColorInfo("#G" + p->displayName + " leaves " + ex_it->first + "\n" + "#w");
			p->currentPos->msgAll(s);	// msg others of ur leaving
			p->currentPos = destRoom;	// change room to new
			s = encodeColorInfo("#G" + p->displayName + " arrives\n" + "#w");	
			p->currentPos->msgAll(s);	// msg arrival in new room
			destRoom->addPlayer(p);	// add self to new room
		}
		else CERR("Fatal Error! Player not found in room list !!! :o ?\n");
	}
}

C(look){
	if (cmd.size() > 3){
		CERR("Correct syntax: look <object name (optional)> <number (optional)>");
	}
	else if (cmd.size() == 1){
		string s = p->currentPos->encodeRoom(p->ansi);
		p->actions.push(s);
		return;
	}
	else{
		int skip;
		if (cmd.size() == 3) skip = atoi(cmd[2].c_str());
		else skip = 1;
		list<Entity*>::iterator mon = findEntity(cmd[1], p->currentPos->monsters, skip);
		if (mon != p->currentPos->monsters.end()){
			string s = (*mon)->looks;
			// show enemies
			Monster * e = (Monster*)*mon;
			cout << "Enemies of " << e->names[0] << ": ";
			for	(list<Player*>::iterator it = e->enemies.begin();it != e->enemies.end(); ++it){
				cout << (*it)->names[0] << " ";
			}; cout<< '\n';
			// show life / max life
			s = decodeColorInfo(s, p->ansi) + "\nLife: " + int2str(e->life) + "/" + int2str(e->maxLife) + '\n';
			p->actions.push(s);
			return;
		}
		list<Entity*>::iterator obj = findEntity(cmd[1], p->currentPos->objects, skip);
		if (obj != p->currentPos->objects.end()){
			string s = decodeColorInfo((*obj)->looks, p->ansi);
			p->actions.push(s + "\n");
			return;
		}
	}
	CERR("You do not see that here\n\n");
}

C(inventry){
	p->actions.push(p->codeInv());
}

C(get){	// 6
	if (cmd.size() > 3){
		CERR("Correct syntax: get <object name / all> <number (optional)>");
	}
	else if (cmd.size() < 2) CERR("Get what?\n\n");
	else if (cmd.size() == 2 && cmd[1] == "all"){
		list<Entity*>::iterator i = p->currentPos->objects.begin();
		while (i!= p->currentPos->objects.end()){
			p->inventry.push_back(*i);
			MSG("You take " + decodeColorInfo((*i)->displayName,p->ansi) + ".\n");
			i = p->currentPos->objects.erase(i);
		}
		MSG("You take everything you can!\n");
	}
	else{
		int skip;
		if (cmd.size() == 3) {
			skip = atoi(cmd[2].c_str());
			if (skip == 0) skip = 1;
		}
		else skip = 1;
		list<Entity*>::iterator i = findEntity(cmd[1], p->currentPos->objects,skip);
		if (i!= p->currentPos->objects.end()){
			p->inventry.push_back(*i);
			MSG("You take " + decodeColorInfo((*i)->displayName,p->ansi) + ".\n");
			p->currentPos->objects.erase(i);
		}
	}
}

C(kill){
	if (cmd.size() > 3){
		CERR("Correct syntax: kill <monster / name (optional)> <number (optional)>");
	}
	if (cmd.size() < 2) CERR("Kill whom?\n\n");
	else{
		int skip;
		if (cmd.size() == 3) {
			skip = atoi(cmd[2].c_str());
			if (skip == 0) skip = 1;
		}
		else skip = 1;

		list<Entity*>::iterator i = findEntity(cmd[1], p->currentPos->monsters,skip);
		if (i!= p->currentPos->monsters.end()){
			((Monster*)*i)->addEnemy(p);	
			p->addEnemy(*i);
			string s =  colors['R'] + "You attack " + (*i)->gName + colors['w'] + "\n";
			p->actions.push(s);
			((Monster*)*i)->life -= 4;
			if (((Monster*)*i)->life <= 0) ((Monster*)*i)->die(p);
		}
		else CERR("No " + cmd[1] + " here\n");
	}
}

C(drop){
	if (cmd.size() > 3){
		CERR("Correct syntax: drop <object name / all> <number (optional)>");
	}
	else if (cmd.size() < 2) CERR("Drop what?\n\n");
	else if (cmd.size() == 2 && cmd[1] == "all"){
		list<Entity*>::iterator i = p->inventry.begin();
		while (i!= p->inventry.end()){
			p->currentPos->objects.push_back(*i);
			MSG("You drop " + decodeColorInfo((*i)->displayName,p->ansi) + ".\n");
			i = p->inventry.erase(i);
		}
	}
	else{
		int skip;
		if (cmd.size() == 3) {
			skip = atoi(cmd[2].c_str());
			if (skip == 0) skip = 1;
		}
		else skip = 1;
		list<Entity*>::iterator i = findEntity(cmd[1], p->inventry,skip);
		if (i!= p->inventry.end()){
			p->currentPos->objects.push_back(*i);
			MSG("You drop " + decodeColorInfo((*i)->displayName,p->ansi) + ".\n");
			p->inventry.erase(i);
		}
	}
}

//#10
C(score){
	if (cmd.size() ==1){
		string s = "\n************** Score *******************\nName: " + p->displayName + "\nLife: " 
					+ int2str(p->life) + "\nID: " + int2str(p->playerID) +
				   "\nEnemies: ";
		for (list<Entity*>::iterator i = p->enemies.begin(); i != p->enemies.end(); ++i){
			s = s + (*i)->names[0] + " ";
		}		   
		s += "\n****************************************\n\n";
		MSG(s);
	}
	else CERR("Correct syntax: score\n");
}

// #11
C(save){
	if (cmd.size() == 1){
		ofstream fout;
		string filename = "../players/" + p->names[0] + ".txt";
		fout.open(filename.c_str());
		if (fout){
			fout << "$ attr_begin\n";
			fout << "name " << p->names[0];
			fout << "\nansi " << p->ansi;
			fout << "\ncurrentPos 0";
			fout << "\ndisplayName " << p->displayName;
			fout << "\nlife " << p->life << "\n\n";
			fout << "$ alias_begin\n";
			for (map<string,string>::iterator i = p->aliases.begin(); i != p->aliases.end(); ++i){
				fout << i->first << " " << i->second << '\n';
			}
			fout << "#\n\n$ items_begin\n";
			for (list <Entity*>::iterator i = p->inventry.begin(); i != p->inventry.end(); ++i){
				fout << (*i)->gameID%1000 << " ";
			}
			fout << "-1\n\n$ end\n";
			MSG(p->displayName + " is now saved!\n\n");
		}
		else CERR("FATAL ERROR: Could not open file for saving!\n");
	}
}

C(quit){
	
	if (cmd.size() == 1){
		MSG("Disconnected from Game!\n\n");
		// remove player from all his enemies' enemy lists
		for (list<Entity*>::iterator i = p->enemies.begin(); i != p->enemies.end(); ++i){
			((Monster*)*i)->removeEnemy(p);
		}
		// remove player from room
		list <Entity*>::iterator j = findPlayer(p, p->currentPos->players);
		if (j != p->currentPos->players.end()) {
			p->currentPos->players.erase(j);	// erase self from room
			string s = encodeColorInfo(p->displayName + " has left the Earth.\n");
			p->currentPos->msgAll(s);	// msg others of ur leaving
		}
		else CERR("FATAL ERROR: could not find player in Room!\n");
		// remove player from allPlayers list
		list <Player*>::iterator jj = findPlayer(p, allPlayers);
		if (jj != allPlayers.end()) {
			cout << "Size before removal: " << allPlayers.size() << '\n';
			allPlayers.erase(jj);	// erase self from global players list
			cout << "Size after removal: " << allPlayers.size() << '\n';
		}
		else CERR("FATAL ERROR: could not find player Global list!\n");
		// close player's socket
		usleep(100000);
		cout << "Disconencting " << p->displayName << '\n';
		pthread_cancel(p->requestsThread);	// cancel all threads
		pthread_cancel(p->handlerThread);
		cout.flush();
		close(p->pSocket);
	}
	else CERR("Correct Syntax: quit\n");
}

C(bolt){
	Entity * e = castSpell(cmd,p);
}

C(fireball){
	Entity * e = castSpell(cmd,p);
}

C(gen_objfn_inv){
	if (cmd.size() < 3 && cmd.size() > 1){
		int skip;
		if (cmd.size() == 3) skip = atoi(cmd[2].c_str());
		else skip = 1;
		list<Entity*>::iterator e = findEntity(cmd[1], p->inventry, skip);	// look if object by name exists
		if (e != p->inventry.end()){
//			for{int i=0; i< ((Object*)*e)->commands.size(); ++i}	// look if that object understands command
//				if (cmd[1] ==  ((Object*)*e)->commands[i]){
					map <string, fcn>::iterator it = allFcns.find(cmd[0] + "_" + int2str((*e)->gameID));
					if (it != allFcns.end() ){
						it->second.func(cmd, p, e);
					}
					return;
//				}
//			}
		}
	}
	CERR("What??\n\n");

}

C(crush_10001){
	MSG("You Crush the leaf of Telperion. You can now use it as salve.\n");
	p->inventry.erase(it);
	//delete *it;
	Object * obj = new Object(objectTemplates[2]);
	p->inventry.push_back((Entity*)obj);
}

C(read_10000){
	string a = "A glowing portal opens before you. You are drawn into the portal by a strange \n";
	a+= "force. A myriad of colors and sounds surronds you for a moment. Soon, you land \n";
	a+="on hard ground.\n\n";
	MSG(a);
	Room * destRoom = &rooms[1];
	cout << "HERE\n";
	string s = destRoom->encodeRoom(p->ansi);
	p->actions.push(s);
	list <Entity*>::iterator j = findPlayer(p, p->currentPos->players);	// find player in room's list
	if (j != p->currentPos->players.end()) {
		p->currentPos->removePlayer(j);	// remove self from room
		s = encodeColorInfo("#GA portal is created in to the room.\n" + p->displayName + " enters into the portal.\n" + "#w");
		p->currentPos->msgAll(s);	// msg others of ur leaving
		p->currentPos = destRoom;	// change room to new
		s = encodeColorInfo("#G" + p->displayName + " incarnates into the Earth!\n" + "#w");	
		p->currentPos->msgAll(s);	// msg arrival in new room
		destRoom->addPlayer(p);	// add self to new room
	}
	else CERR("Fatal Error! Player not found in room list !!! :o ?\n");
}

/*------------------------------------------------------------------------------*/

void initFcns(){


	FCN("_exit",	_exitR);
	FCN("ansi", 	ansi);
	FCN("help", 	help);
	FCN("look", 	look);
	FCN("inventry",	inventry);
	FCN("get", 		get);
	FCN("kill", 	kill);
	FCN("drop", 	drop);
	FCN("save", 	save);
	FCN("quit", 	quit);
	FCN("score", 	score);
	FCN("bolt", 	bolt);
	FCN("fireball", fireball);
	FCN("read",		gen_objfn_inv);
	FCN("crush",	gen_objfn_inv);
}

void initObjFcns(){
	FCN("read_10000", read_10000);
	FCN("crush_10001", crush_10001);
}


