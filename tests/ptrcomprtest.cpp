#include <iostream>
using namespace std;

class num{
public:
	int a;
	int b;
	num(int p, int q){a = p; b=q;};
};

int main(){
	num a(2,3);
	num b(2,3);
	num * p = &a;
	num * q = &b;
	num * r = &a;
	if (p == q) cout << "pq equal!\n";
	if (p == r) cout << "pr equal!\n";
	return 0;
}
