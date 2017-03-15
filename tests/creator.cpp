#include <iostream>
#include <string>
#include <fstream>
using namespace std;

ifstream fin;
string waste;

int initObjects(){
	fin.open("../Server/data/objects.txt");
	if (!fin) {cout << "Fatal Error: Could not open Objects File!!!\n"; fin.close(); return 1;}
	else {
	    cout << "Creating Object templates...";
		string a, s, cmd, waste;
		int t, n;
		while (fin >> t){
			cout << "Object #" << t << '\n';		// object number
			//Object * obj = new Object;
			while (fin >> s && s != "$" ){cout << s << '\n';}	// wait till valid command
			if (fin >> cmd && cmd == "names_begin"){
				cout << "Names:\n";
				while (fin >> s && s!= "#"){
					cout << "." << s << "*\n";		// get names
					//obj->names.push_back(s);
				}
			}
			else {cout << "No valid names_begin found for Object #" << t << '\n'; return 1;}
		
			while (fin >> waste && waste != "$" ){}	// wait till valid cmd
			if (fin >> cmd && cmd == "attr_begin"){
				cout << "Attributes:\n";
				fin >> cmd >> n; cout << "type = " << n << '\n';			//type				
				if (fin >> cmd && cmd == "dispName"){			// displayName; getline() is painful, so do it this way!
					a = "";
					while (fin >> s && s != ">") a = a + s +  " ";		
					cout << "dispName = ." << a << "*\n";
					//obj->displayName = encodeColorInfo(a);
				}
				if (fin >> cmd && cmd == "looks"){			// looks
					a = "";
					while (fin >> s && s != ">") a = a + s +  " ";		
					cout << "looks = ." << a << "*\n";
					//obj->looks = encodeColorInfo(a);
				}
			}
			else {cout << "No valid attr_begin found for Object #" << t << '\n'; return 1;}

			while (fin >> waste && waste != "$" ){}
			if (fin >> cmd && cmd == "cmds_begin"){
				cout << "Commands: \n";
				while(fin >> s && s != "#"){		// get commands
					fin >> n;
					//obj->commands.insert(pair<string, int> (s,n));
					cout << s << " " <<  n << '\n';
				}
			}
			else {cout << "No valid cmds_begin found for Object #" << t << '\n'; return 1;}
			cout << "End\n\n";
			
			//objectTemplates.push_back(*obj);
			//delete obj;
		}
		//cout << " " << objectTemplates.size() << " Object templates created.\n";
		fin.clear();
		fin.close();
	}
}

//int initObjects(){
//	pfin.open("../Server/data/objects.txt");
//	if (! pfin) cout << "Fatal Error: Could not open Objects File!!!\n";
//	else {
//		string s, cmd, waste;
//		int n;
//		while (pfin >> n){
//			cout << "Object #" << n << '\n';
//			while (pfin >> s && s != "$" ){cout << s << '\n';}
//			pfin >> cmd;
//			if (cmd == "names_begin"){
//				cout << "Names:\n";
//				while (pfin >> s && s!= "#"){
//					cout << "." << s << "*\n";
//				}
//			}
//			else cout << "Error reading Object names...";
//		
//			while (pfin >> s && s != "$" ){}
//			pfin >> cmd;
//			if (cmd == "attr_begin"){
//				cout << "Attributes:\n";
//				pfin >> waste >> n; cout << "type = " << n << '\n';			//type
//				if (pfin >> waste && waste == "dispName"){			// displayName; getline() is painful, so do it this way!
//					waste = "";
//					while (pfin >> s && s != ">") waste = waste + s +  " ";		
//					cout << "dispName = ." << waste << "*\n";
//				}
//				if (pfin >> waste && waste == "looks"){			// looks
//					waste = "";
//					while (pfin >> s && s != ">") waste = waste + s +  " ";		
//					cout << "looks = ." << waste << "*\n";
//				}
//			}
//			else cout << "Error reading Object attributes...";

//			while (pfin >> s && s != "$" ){}
//			pfin >> cmd;
//			waste = "";
//			if (cmd == "cmds_begin"){
//				cout << "Commands: \n";
//				while(pfin >> cmd && cmd != "#"){
//					pfin >> n;
//					cout << cmd << " " <<  n << '\n';
//				}
//			}
//			cout << "End\n\n";
//		}
//	}
//}

//int initMonsters(){
//	pfin.open("../Server/data/monsters.txt");
//	if (! pfin) cout << "Fatal Error: Could not open Monsters File!!!\n";
//	else {
//		string s, cmd, waste;
//		int n;
//		while (pfin >> n){
//			cout << "Monster #" << n << '\n';
//			while (pfin >> s && s != "$" ){cout << s << '\n';}
//			pfin >> cmd;
//			if (cmd == "names_begin"){
//				cout << "Names:\n";
//				while (pfin >> s && s!= "#"){
//					cout << "." << s << "*\n";
//				}
//			}
//			else cout << "Error reading Player file! Creating new Player...";
//		
//			while (pfin >> s && s != "$" ){}
//			pfin >> cmd;
//			if (cmd == "attr_begin"){
//				cout << "Attributes:\n";
//				pfin >> waste >> n; cout << "type = " << n << '\n';			//type
//				if (pfin >> waste && waste == "dispName"){			// displayName; getline() is painful, so do it this way!
//					waste = "";
//					while (pfin >> s && s != ">") waste = waste + s +  " ";		
//					cout << "dispName = ." << waste << "*\n";
//				}
//				if (pfin >> waste && waste == "looks"){			// looks
//					waste = "";
//					while (pfin >> s && s != ">") waste = waste + s +  " ";		
//					cout << "looks = ." << waste << "*\n";
//				}
//			}
//			else cout << "Error reading Player file! Creating new Player...";

//			while (pfin >> s && s != "$" ){}		// commands
//			pfin >> cmd;
//			waste = "";
//			if (cmd == "cmds_begin"){
//				cout << "Commands: \n";
//				while(pfin >> cmd && cmd != "#"){
//					pfin >> n;
//					cout << cmd << " " <<  n << '\n';
//				}
//			}

//			while (pfin >> s && s != "$" ){}	// AI actions
//			pfin >> cmd;
//			waste = "";
//			if (cmd == "ai_begin"){
//				cout << "AI: \n";
//				while(pfin >> cmd && cmd != "#"){
//					pfin >> n;
//					cout << cmd << " " <<  n << '\n';
//				}
//			}
//			
//			while (pfin >> s && s != "$" ){}
//			pfin >> cmd;
//			if (cmd == "items_begin"){
//				while (pfin >> n && n != -1){
//					cout << n << " ";
//				}
//			}
//			else cout << "Error reading Player file! Creating new Player...";

//			cout << "End\n\n";
//		}
//	}
//}

//int initRooms(){
//	pfin.open("../Server/data/rooms.txt");
//	if (! pfin) cout << "Fatal Error: Could not open Rooms File!!!\n";
//	else {
//		string s, cmd, waste;
//		int n;
//		while (pfin >> n){
//			cout << "Room #" << n << '\n';
//			while (pfin >> s && s != "$" ){}	// wait till start of valid command
//			pfin >> cmd;
//			if (cmd == "attr_begin"){
//				cout << "Attributes:\n";
//				if (pfin >> waste && waste == "coords"){
//					int x, y, z;
//					pfin >> x >> y >> z;	// coords  
//					cout << "coords = " << x << " " << y << " " << z << '\n';	
//				}
//				if (pfin >> waste && waste == "desc"){			// desc
//					waste = "";
//					while (pfin >> s && s != ">") waste = waste + s +  " ";		
//					cout << "desc = ." << waste << "*\n";
//				}
//			}
//			else cout << "Error reading Player file! Creating new Player...";

//			while (pfin >> s && s != "$" ){}		// exits
//			pfin >> cmd;
//			waste = "";
//			if (cmd == "exits_begin"){
//				cout << "Exits: \n";
//				while(pfin >> cmd && cmd != "#"){
//					pfin >> n;
//					cout << cmd << " " <<  n << '\n';
//				}
//			}

//			while (pfin >> s && s != "$" ){}	// objects
//			pfin >> cmd;
//			if (cmd == "items_begin"){
//				cout << "Items: ";
//				while(pfin >> n && n != -1){
//					cout << n << " ";
//				}
//				cout << '\n';
//			}
//			else cout << "Error reading items...\n";
//			
//			while (pfin >> s && s != "$" ){}
//			pfin >> cmd;
//			if (cmd == "monsters_begin"){
//				cout << "Monsters: " ;
//				while (pfin >> n && n != -1){
//					cout << n << " ";
//				}
//				cout << '\n';
//			}
//			else cout << "Error reading Player file! Creating new Player...";

//			cout << "End\n\n";
//		}
//	}
//}

int main(){
	initObjects();
	return 0;
}
