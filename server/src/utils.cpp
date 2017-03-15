#include "../include/utils.h"

// parser
void parse(string &s, vector <string> &v){
	char *p=strtok((char*)s.c_str()," ");
	while (p!=NULL){
		v.push_back(p);
		p=strtok(NULL," ");
	}
}

// read a line word by word from ifstream fin
string readLine(ifstream &fin, string delim, bool encode_flag){
	string a = "", s = "";
	while (fin >> s && s != delim) {
		if (s.substr(0,1) == "!"){
			s = escapeChars[s];
			a = a + s;
		}
		else a = a + s +  " ";
	}
	a = a.substr(0, a.size()-1);	// remove the trailing space
	if (encode_flag) a = encodeColorInfo(a);
	return a;
}

// convert from int to string
string int2str(int n){
	std::stringstream ss;
	ss << n;
	return ss.str();	
}

// find Entity by name and return iterator in list
list<Entity*>::iterator findEntity(string &name, list <Entity*> &elist, int skip){
	int t = 0;
	for (list <Entity*>::iterator i = elist.begin(); i!=elist.end(); ++i){
		for (unsigned int j = 0; j< (*i)->names.size(); ++j){
			if ( (*i)->names[j] == name){
				--skip;
				if (skip == 0){
					return i;
				}
			}
		}
	}
	return elist.end();
}

// find Entity by pointer and return <Entity*> iterator
list<Entity*>::iterator findEntity_ptr(Entity * p, list <Entity*> &elist){
	for (list <Entity*>::iterator i = elist.begin(); i!=elist.end(); ++i){
		if ( (*i) == p){
			return i;
		}
	}
	return elist.end();
}

// find Player by pointer and return <Entity*> iterator
list<Entity*>::iterator findPlayer(Player * p, list <Entity*> &elist){
	for (list <Entity*>::iterator i = elist.begin(); i!=elist.end(); ++i){
		if ( ((Player*)*i) == p){
			return i;
		}
	}
	return elist.end();
}

// find Player by pointer and return <Player*> iterator
list<Player*>::iterator findPlayer(Player * p, list <Player*> &elist){
	for (list <Player*>::iterator i = elist.begin(); i!=elist.end(); ++i){
		if ( (*i) == p){
			return i;
		}
	}
	return elist.end();
}

// find object by name and return Object* pointer
Object * findObject(string &name, list <Entity*> objects, int skip){
	for (list <Entity*>::iterator i = objects.begin(); i!=objects.end(); ++i){
		for (unsigned int j = 0; j< (*i)->names.size(); ++j){
			if ( (*i)->names[j] == name){
				--skip;
				if (skip == 0){
					return (Object*)(*i);
				}
			}
		}
	}
	return NULL;
}


// ******** display utils ******************

void initEscapeChars(){
	escapeChars["!n"] = '\n';
	escapeChars["!t"] = '\t';
}

void initColors(){
	//normal colors
	colors['r'] = "\x1b[0;31m";	// red
	colors['g'] = "\x1b[0;32m";	// green
	colors['y'] = "\x1b[0;33m";	// yellow
	colors['b'] = "\x1b[0;34m";	// blue
	colors['m'] = "\x1b[0;35m";	// magenta
	colors['c'] = "\x1b[0;36m";	// cyan
	colors['w'] = "\x1b[0;37m";	// white
	// bold colors
	colors['R'] = "\x1b[1;31m";	// bold red
	colors['G'] = "\x1b[1;32m";	// bold green
	colors['Y'] = "\x1b[1;33m";	// bold yellow
	colors['B'] = "\x1b[1;34m";	// bold blue
	colors['M'] = "\x1b[1;35m";	// bold magenta
	colors['C'] = "\x1b[1;36m";	// bold cyan
	colors['W'] = "\x1b[1;37m";	// bold white (grey)
}

string encodeColorInfo(string s){	
	vector <int> is;
	int i=0;
	while(1){
		i = (int)s.find('#');
		if (i!=string::npos){	
			s.replace(i,1,"");	// remove the #'s
			is.push_back(i);	// store the position of # into a vector
 		}
		else break;
	}
	
	string ss = int2str(s.size());	// prefix the string with its size
	s = ss+" "+s;

	for(int i=0; i<(int)is.size(); ++i){
		ss = int2str(is[i]);	// append the string with all positions of #
		s = s + " " + ss;
	}
	return s;
}


string decodeColorInfo(string s, bool ansi){
	int f = (int)s.find_first_of(" "); 		// find start of real string
	int len = atoi(s.substr(0,f).c_str());	// extract length of real string (prefixed)
	string a = s.substr(f+1,len);			// extract the original string 
	string b;
	if (f+2+len < (int)s.size())			// extract color info string
		b = s.substr(f+2+len, s.size()-f-len-2);
	else b = "";

	vector <int> res;
	char *p=strtok((char*)b.c_str()," ");
	while (p!=NULL){						// make a vector of color positions by parsing color info string
		res.push_back(atoi(p));
		p=strtok(NULL," ");
	}		
	int count = 0;
	if (ansi == true){						// is ansi on, replace color alphabets by color sequence
		for (int i=0; i<(int)res.size(); ++i){
			string s = colors.find(a[res[i]+count])->second;
			a.replace(res[i]+count, 1, s);
			count += (int)s.size()-1;
		}
	}
	else{									// else replace color alphabets by ""
		for (int i=0; i<(int)res.size(); ++i){
			string s = "";
			a.replace(res[i]+count, 1, s);
			count += (int)s.size()-1;
		}
	}
	return a;
}

//************* debug utils ***********************
void showRooms(){
	for (int i=0; i<int(rooms.size()); ++i){
		cout << "Room #" << i << '\n';
		rooms[i].displayRoom();
	}
}

void showObjects(){
	// display all objects
	for (int i=0; i<int(objectTemplates.size()); ++i){
		cout << "Object #" << i << '\n';
		cout << objectTemplates[i].displayName << '\n';
		cout << "l: " << objectTemplates[i].looks << '\n';
		cout << "ID: " << objectTemplates[i].gameID << '\n';
		cout << "Names: ";
		for (int j=0; j<int(objectTemplates[i].names.size()); ++j){
			cout << '"' <<  objectTemplates[i].names[j] << '"' << ", ";
		}
		cout << "\nCommands: ";
		for (int j=0; j<objectTemplates[i].commands.size(); ++j){
			cout << '"' <<  objectTemplates[i].commands[j] << '"' << ", ";
		}
		cout << "\n\n";
	}
}

void showMonsters(){
	// display all monsters
	for (int i=0; i<int(monsterTemplates.size()); ++i){
		cout << "Monster #" << i << '\n';
		cout << monsterTemplates[i].displayName << '\n';
		cout << "l: " << monsterTemplates[i].looks << '\n';
		cout << "Names: ";
		for (int j=0; j<int(monsterTemplates[i].names.size()); ++j){
			cout << '"' <<  monsterTemplates[i].names[j] << '"' << " ";
		}
		cout << "\nCommands: ";
		for (int j=0; j<monsterTemplates[i].commands.size(); ++j){
			cout << '"' <<  monsterTemplates[i].commands[j] << '"' << ", ";
		}
		cout << "\nAI: ";
		for (int j=0; j<monsterTemplates[i].actions.size(); ++j){
			cout << '"' <<  monsterTemplates[i].actions[j].action << '"' << ", ";
		}
		cout << "\nInventry: ";
		for (vector <int>::iterator j = monsterTemplates[i].inventry.begin(); j != monsterTemplates[i].inventry.end(); ++j){
			cout << '"' <<  *j << '"' << ", ";
		}
		cout << "\n\n";
	}
}

