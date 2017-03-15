#include<iostream>
#include<list>
#include<map>
using namespace std;

list<int*> l;

list<int*>::iterator findint(int n, list<int*> &l){
	for ( list<int*>::iterator i = l.begin(); i!=l.end(); ++i){
		if (**i == n){
			cout << "Found";
			l.pop_front();
			return i;
		}
	}	
}

int main(){
	int a=1, b=2, c=3;
	l.push_back(&a);l.push_back(&b);l.push_back(&c);
	list <int*>::iterator i = findint(2, l);
	cout << **i;
	cout << *(l.front()) << '\n';
	l.pop_front();
	cout << *(l.front()) << '\n';
	map <string, int> m;
	m["jaideep"] = 1;
	m["tttt"] = 5;
	//m["a"] = 7;
	cout << m["jaideep"] << " " << m["tttt"] << " " << m["tttt"] << '\n';
	m["jaideep"] += 2;
	m["tttt"] += 1;
	m["a"] += 10;
	cout << m["jaideep"] << " " << m["tttt"] << " " << m["a"] << '\n';
	return 0;
}
