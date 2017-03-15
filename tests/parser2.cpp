#include <iostream>
#include <string>
#include <vector>
using namespace std;

void parse(string &s, vector <string> &v){
	string::iterator i = s.begin();
	string::iterator j = s.begin();
}

int main(){
	string s = "   Give   50 gold coins  to       Talona      ";
	vector <string> v;
	parse(s,v);
	cout << "string was :";
	for (int i=0; i< v.size(); ++i){
		cout << v[i] << " ";
	}
	cout << "\"";
}
