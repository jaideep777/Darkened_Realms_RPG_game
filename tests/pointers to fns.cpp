#include <iostream>
using namespace std;
#include <vector>

class jaideep{
    private:
       int a;
       
    public:
       jaideep(int (*p) (int,int));
       int (* p_callFunction) (int,int);      
       int execute(int cmd, int cmd2);
};

jaideep::jaideep(int (*p) (int,int)){
    p_callFunction = p;    
}

int jaideep::execute(int cmd, int cmd2){
    return (* p_callFunction)(cmd,cmd2);
}

int fA(int cmd, int cmd2){
    cout << cmd << " " << cmd2 <<": this is function of A\n";   
	return 0;
}
int (* p1) (int,int ) = fA;

int fB(int cmd, int cmd2){
    cout << cmd << " " << cmd2 <<": this is function of B\n";    
	return 0;
}
int (* p2) (int, int ) = fB;

jaideep A(p1);
jaideep B(p2);

//jaideep myfunctions[2] = {A, B};
vector <jaideep> myfunctions;
myfunctions.push_back(A);

int main(){

int a,b;
cin >> a >> b;
myfunctions[0].execute(a,b);

cin >> a >> b;
myfunctions[1].execute(a,b);

cin >> a;
return 0;
}
