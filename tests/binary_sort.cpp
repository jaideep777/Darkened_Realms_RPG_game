#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector <string> cmds;
string a[10];

int main(){
	string s;
	for(int i =0; i<10; ++i){
		getline(cin, s, '\n');
		cmds.push_back(s);
	}
	vector<string>::iterator it = cmds.begin();
//	sort(it,it+cmds.size());
	for(int i =0; i<10; ++i){
		cout<< cmds[i] << '\n';	
	}
	cout << "\n" << binary_search(it,it+cmds.size(),"g");
 system("PAUSE");
}


