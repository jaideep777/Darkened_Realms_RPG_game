#include <iostream>
#include <string>
#include <vector>
using namespace std;

void parse(string &a, vector <string> &s){
	cout << "last = ." << a[a.size()] << ".\n";
	string b,c;
	int d = a.size();
	for (int i=0; i<d; i++){
		d = a.size();
		if (i == d-1){
			b = a.substr(0,i+1);
			if (b != "" && b != " ") s.push_back(b);
		}
		else if (a[i] == ' '){
			b = a.substr(0,i);
			a = a.substr(i+1, d-i-1);
			i = -1;
			if (b != "" && b != " ") s.push_back(b);
		}
	}
}

int main(){
string a;
vector <string> v;

while(getline(cin,a)){

	parse(a,v);
	cout << '.';	
	for (int i=0; i<v.size();++i){
		cout << v[i] << ".";
	}
	cout << '\n';
}
//	system("PAUSE");v
}
