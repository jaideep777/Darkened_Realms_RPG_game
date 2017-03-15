#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
using namespace std;

string int2str(int n){
  std::stringstream ss;
  ss << n;

	return ss.str();	
 
}

int main(){
	int a = 56;
 
 	string s = int2str(a);
  cout << "*" + s + "*" << endl;
  
}


