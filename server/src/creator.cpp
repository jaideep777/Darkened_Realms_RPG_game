#include "../include/creator.h"

ifstream fin;

int initSpells(){
	fin.open("../data/spells.txt");
	if (!fin) {cout << "Fatal Error: Could not open Objects File!!!\n"; fin.close(); return 1;}
	else {
	    cout << "Creating Spells...";
		string a, s, cmd, waste;
		int t, n;
		spell * sp = NULL;
		cout.flush();
		while (fin >> t){
			sp = new spell;
			while (fin >> s && s != "$" ){}	// wait till valid command
			if (fin >> cmd && cmd == "attr_begin"){
				fin >> cmd >> sp->name; 			//name				
				fin >> cmd >> sp->damage; 			//damage				
				if (fin >> cmd && cmd == "mantra") sp->mantra = readLine(fin, ">", true);	// displayName; getline() is painful, so do it this way!
			}
			else {cout << "No valid attr_begin found for Object #" << t << '\n'; return 1;}

			allSpells.push_back(*sp);
			delete sp;
		}
		sp = NULL;
		cout << " " << allSpells.size() << " Spells created.\n";
		fin.clear();
		fin.close();
		
		for (int i=0; i<allSpells.size(); ++i){
			Spells.insert(pair<string, spell> (allSpells[i].name, allSpells[i]));
		}
	}
}

int initObjects(){
	fin.open("../data/objects.txt");
	if (!fin) {cout << "Fatal Error: Could not open Objects File!!!\n"; fin.close(); return 1;}
	else {
	    cout << "Creating Object templates...";
		string a, s, cmd, waste;
		int t, n;
		Object * obj = NULL;
		cout.flush();
		while (fin >> t){
			obj = new Object;
			obj->gameID = t;	// gameID = template number
			while (fin >> s && s != "$" ){}	// wait till valid command
			if (fin >> cmd && cmd == "names_begin"){
				while (fin >> s && s!= "#")	obj->names.push_back(s); // get names
			}
			else {cout << "No valid names_begin found for Object #" << t << '\n'; return 1;}
			while (fin >> waste && waste != "$" ){}	// wait till valid cmd
			if (fin >> cmd && cmd == "attr_begin"){
				fin >> cmd >> obj->type; 			//type				
				if (fin >> cmd && cmd == "dispName") obj->displayName = readLine(fin, ">", true);	// displayName; getline() is painful, so do it this way!
				if (fin >> cmd && cmd == "pluralName") obj->pluralName = readLine(fin, ">", true);	// displayName; getline() is painful, so do it this way!
				if (fin >> cmd && cmd == "looks") obj->looks = readLine(fin, ">", true);	// looks
			}
			else {cout << "No valid attr_begin found for Object #" << t << '\n'; return 1;}

			while (fin >> waste && waste != "$" ){}
			if (fin >> cmd && cmd == "cmds_begin"){
				while(fin >> s && s != "#"){		// get commands
					obj->commands.push_back(s);
				}
			}
			else {cout << "No valid cmds_begin found for Object #" << t << '\n'; return 1;}

			objectTemplates.push_back(*obj);
			delete obj;
		}
		obj = NULL;
		cout << " " << objectTemplates.size() << " Object templates created.\n";
		fin.clear();
		fin.close();
	}
}

int initMonsters(){
	fin.open("../data/monsters.txt");
	if (! fin) cout << "Fatal Error: Could not open Monsters File!!!\n";
	else {
	    cout << "Creating Monster templates...";
		string a, s, cmd, waste;
		int t, n;
		Monster * mon = NULL;
		while (fin >> t){
		    mon = new Monster;
		    mon->gameID = t;
		    mon->roomNum = 0; ////// GET FROM FILE;
		    mon->status = 3;
		    mon->life = mon->maxLife = 50;	////// GET FROM FILE
		    mon->maxEnemies = 5;	////// GET FROM FILE
		    mon->respawnTime = 15;	////// GET FROM FILE
			while (fin >> waste && waste != "$" ){}
			if (fin >> cmd && cmd == "names_begin"){
				while (fin >> s && s!= "#"){	// get names
					mon->names.push_back(s);
				}
			}
			else {cout << "No valid names_begin found for Monster #" << t << '\n'; return 1;}
		
			while (fin >> waste && waste != "$" ){}
			if (fin >> cmd && cmd == "attr_begin"){
				if (fin >> cmd && cmd == "gname") mon->gName = readLine(fin, ">", false); // gName getline() is painful, so do it this way!
				fin >> waste >> mon->type;							//type
				if (fin >> cmd && cmd == "dispName") mon->displayName = readLine(fin, ">", true); // displayName
				if (fin >> cmd && cmd == "plural") mon->pluralName = readLine(fin, ">", true);  // pluralName
				if (fin >> cmd && cmd == "looks") mon->looks = readLine(fin, ">", true); // looks
			}
			else {cout << "No valid attr_begin found for Monster #" << t << '\n'; return 1;}

			while (fin >> s && s != "$" ){}		// commands
			if (fin >> cmd && cmd == "cmds_begin"){
				while(fin >> s && s != "#"){
					mon->commands.push_back(s);
				}
			}
			else {cout << "No valid cmds_begin found for Monster #" << t << '\n'; return 1;}
			
			while (fin >> s && s != "$" ){}	// AI actions
			if (fin >> cmd && cmd == "ai_begin"){
				while(fin >> s && s != "#"){
					mon->actions.push_back(aiAct(s,5));
				}
			}
			else {cout << "No valid ai_begin found for Monster #" << t << '\n'; return 1;}
			
			while (fin >> s && s != "$" ){}	// Items
			if (fin >> cmd && cmd == "items_begin"){
				while (fin >> n && n != -1){
					mon->inventry.push_back(n);
				}
			}
			else {cout << "No valid items_begin found for Monster #" << t << '\n'; return 1;}

			monsterTemplates.push_back(*mon);
			delete mon;
		}
		mon = NULL;
		cout << " " << monsterTemplates.size() << " Monster Templates created.\n";
		fin.clear();
		fin.close();
	}
}

int initRooms(){
	fin.open("../data/rooms.txt");
	if (! fin) cout << "Fatal Error: Could not open Rooms File!!!\n";
	else {
	    cout << "Creating rooms...";
		string a, s, cmd, waste, desc;
		int t, n;
	    Room * w;
		while (fin >> t){
		    map <string, int> ex;
			int x, y, z;
	
			while (fin >> s && s != "$" ){}	// wait till start of valid command
			if (fin >> cmd && cmd == "attr_begin"){
				if (fin >> cmd && cmd == "coords") fin >> x >> y >> z;			// coords  
				if (fin >> cmd && cmd == "desc") desc = readLine(fin, ">", true); // desc
			}
			else {cout << "No valid attr_begin found for Room #" << t << '\n'; return 1;}

			while (fin >> waste && waste != "$" ){}		
			if (fin >> cmd && cmd == "exits_begin"){
				while(fin >> s && s != "#"){		// exits
					fin >> n;
					ex.insert(pair<string, int> (s, n));
				}
			}
			else {cout << "No valid exits_begin found for Monster #" << t << '\n'; return 1;}
			
			w = new Room(Vect3(x,y,z),desc,ex);
			
			while (fin >> waste && waste != "$" ){}	
			if (fin >> cmd && cmd == "items_begin"){
				Object * obj = NULL;
				while(fin >> n && n != -1){		// objects
					++numEntities;
					obj = new Object(objectTemplates[n]);
					w->objects.push_back(obj);
				}
				obj = NULL;
			}
			else {cout << "No valid items_begin found for Monster #" << t << '\n'; return 1;}
			
			while (fin >> waste && waste != "$" ){}
			if (fin >> cmd && cmd == "monsters_begin"){
				while (fin >> n && n != -1){	// monsters
					++numEntities;
					Monster * mon = new Monster(monsterTemplates[n]);
					w->monsters.push_back(mon);
				}
			}
			else {cout << "No valid monsters_begin found for Monster #" << t << '\n'; return 1;}

	        rooms.push_back(*w);
	        delete w;
		}
		w = NULL;
		cout << " " << rooms.size() << " rooms created.\n";
		cout << "Total Entities created: " << numEntities << '\n';
		fin.clear();
		fin.close();

	}
}

