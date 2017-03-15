#include <iostream>
#include <vector>
using namespace std;

class num{
	public:
	int n;
	int * p;
};

int main(){
	
	int x = 8, y = 3, z= 1;

	vector <num> nums;
	
	num * a = new num;
	a->n = 5;
	a->p = &x;
	
	nums.push_back(*a);

	x = 6;
	a->n = 9;

	nums[0].n = 4;
	*(nums[0].p) = 0;

	cout << a->n << " " << *(a->p) << '\n';
	for(int i=0; i<nums.size(); ++i){
		cout << nums[i].n << " " << *(nums[i].p) << '\n';
	}
	
	
}
