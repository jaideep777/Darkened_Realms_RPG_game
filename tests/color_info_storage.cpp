#include <iostream>
#include <string>
#include <vector>
using namespace std;

const char RED[]     = "\x1b[31m";
const char GREEN[]   = "\x1b[32m";
const char YELLOW[]  = "\x1b[33m";
const char BLUE[]    = "\x1b[34m";
const char MAGENTA[] = "\x1b[35m";
const char CYAN[]    = "\x1b[36m";

string encryptColorInfo(string s){
	vector <int> is;
	int i=0;
	while(1){
		i = (int)s.find('#');
		if (i!=string::npos){
			s.replace(i,1,"");
			is.push_back(i);
 		}
		else break;
	}

	char buffer[50];
	int siz = (int)s.size();
	itoa(siz, buffer, 10);
	string ss = buffer;
	
	s = ss+" "+s;

	for(int i=0; i<(int)is.size(); ++i){
		itoa(is[i], buffer, 10);
		ss = buffer;
		s = s + " " + ss;
	}
	return s;
}

string decodeColorInfo(string s){
	int f = (int)s.find_first_of(" ");
	int len = atoi(s.substr(0,f).c_str());
	string a = s.substr(f+1,len);
	string b;
	if (f+2+len < s.size()) b = s.substr(f+2+len, s.size()-f-len-2);
	else b = "";

	vector <int> res;
	char *p=strtok((char*)b.c_str()," ");
	while (p!=NULL){
		res.push_back(atoi(p));
		p=strtok(NULL," ");
	}

	for (int i=0; i<(int)res.size(); ++i){
		a[res[i]] = '^';
	}
	return a;
}


int main(){
	string s;
	while(getline(cin, s)){

	// aquisition
	s = encryptColorInfo(s);
	cout << s << '\n';

	// recovery
	string a = decodeColorInfo(s);
	
	cout << "\"" << a << "\"" << '\n';
	}
//	cout << "\"" << b << "\"" << '\n';
	system("PAUSE");
}

