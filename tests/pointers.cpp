#include <iostream>
using namespace std;

class num{
public:
	int n;
};

void funcc(num * d){
	sleep(1);
	cout << (d->n)*5 << '\n';
	delete d;
	if (d == NULL) cout << "P still exists!";
}

void func(int s){
	num * p = new num;
	p->n = s;
	funcc(p);
//	delete p;
}


int main(){

	func(5);	
	return 0;
}
