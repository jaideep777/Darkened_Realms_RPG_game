#include <fstream>
using namespace std;

int main(){
	ofstream fout;
	fout.open("a.txt");
	fout << "This file was overwrutten by: \nJaideep";
	return 0;
}
