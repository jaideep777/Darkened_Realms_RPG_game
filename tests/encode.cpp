#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <sstream>
#include <stdlib.h>
using namespace std;

map <char, string> colours;

void initColours(){
	colours['r'] = "\x1b[0;31m";	// red
	colours['g'] = "\x1b[0;32m";	// green
	colours['y'] = "\x1b[0;33m";	// yellow
	colours['b'] = "\x1b[0;34m";	// blue
	colours['m'] = "\x1b[0;35m";	// magenta
	colours['c'] = "\x1b[0;36m";	// cyan
	colours['w'] = "\x1b[0;37m";	// white
	// bold colours
	colours['R'] = "\x1b[1;31m";	// bold red
	colours['G'] = "\x1b[1;32m";	// bold green
	colours['Y'] = "\x1b[1;33m";	// bold yellow
	colours['B'] = "\x1b[1;34m";	// bold blue
	colours['M'] = "\x1b[1;35m";	// bold magenta
	colours['C'] = "\x1b[1;36m";	// bold cyan
	colours['W'] = "\x1b[1;37m";	// bold white (grey)
}


string int2str(int n){
	stringstream ss;
	ss << n;
	return ss.str();	
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
	int f = (int)s.find_first_of(" "); //cout << f << endl;
	int len = atoi(s.substr(0,f).c_str()); //cout << len << endl;
	string a = s.substr(f+1,len);	// extract the original string 
	//cout << s << endl;
	string b;
	if (f+2+len < (int)s.size())	// extract color info string
		b = s.substr(f+2+len, s.size()-f-len-2);
	else b = "";
	// make a vector of colour positions
	vector <int> res;
	char *p=strtok((char*)b.c_str()," ");
	while (p!=NULL){
		res.push_back(atoi(p));
		p=strtok(NULL," ");
		//cout << p << endl;
	}		
	int count = 0;
	if (ansi == true){
		for (int i=0; i<(int)res.size(); ++i){
			string s = colours.find(a[res[i]+count])->second;
			a.replace(res[i]+count, 1, s);
			count += (int)s.size()-1;
		}
	}
	else{
		for (int i=0; i<(int)res.size(); ++i){
			string s = "";
			a.replace(res[i]+count, 1, s);
			count += (int)s.size()-1;
		}
	}
	return a;
}


int main(){
	initColours();
	string s = "hi im #Rjaideep#w. I am in #YIIT#g. Nice to meet u!";	
	s = encodeColorInfo(s); cout << s << endl;
	cout << decodeColorInfo(s,true) << endl;

	return 0;
}
