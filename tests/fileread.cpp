#include <iostream>
#include <string>
#include <fstream>
using namespace std;

ifstream pfin;

int welcomeExisting(string name){
	string nameFile = name + ".txt";
	pfin.open(nameFile.c_str());
	if (! pfin) cout << "Fatal Error: Could not open File!!!\n";
	string s, cmd, waste;
	int n;

	while (pfin >> s && s != "$" ){}
	pfin >> cmd;
	if (cmd == "attr_begin"){
		cout << "Attributes:\n";
		pfin >> waste >> n; cout << "ansi = " << bool(n) << '\n';//ansi
		pfin >> waste >> n; cout << "pos = " << n<< '\n';//currentPos
		pfin >> waste >> s; cout << "name = " << s<< '\n';//displayName
		pfin >> waste >> n; cout << "life = " << n<< '\n'; //life
	}
	else cout << "Error reading Player file! Creating new Player...";
	
	while (pfin >> s && s != "$" ){}
	pfin >> cmd;
	if (cmd == "alias_begin"){
		cout << "Aliases:\n";
		while (pfin >> s && s != "#"){
			pfin >> cmd; cout << s << " " << cmd << '\n';
			//player->aliases.insert(pair<string,string> (s,cmd));
		}
	}
	else cout << "Error reading Player file! Creating new Player...";
	
	while (pfin >> s && s != "$" ){}
	pfin >> cmd;
	if (cmd == "items_begin"){
		while (pfin >> n && n != -1){
			cout << n << " ";
		}
	}
	else cout << "Error reading Player file! Creating new Player...";
	cout << '\n';

	return 0;
}



int main(){

	welcomeExisting("../Server/data/talena");
	return 0;
}
