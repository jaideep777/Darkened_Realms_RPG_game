#include <iostream>
#include <sstream>
using namespace std;

int main(){

	string s;
	getline(cin, s);
	std::stringstream ss;
	ss << s;
	cout << ss.str() << '\n';
	return 0;

}


