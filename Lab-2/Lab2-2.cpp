#include <iostream>
using namespace std;

class Krug {
    private:
    float radius;
    const float pi=3.14;
    public:
    Krug(){}
    Krug(float r){
        radius=r;
    }
    ~Krug(){}
    float perimetar(){
        return 2*pi*radius;
    }
    float plostina(){
        return pi*radius*radius;
    }
    int ednakvi(){
        if(perimetar()==plostina()){
            return 1;
        }else return 0;
    }
};

int main() {
	float r;
	cin >> r;
	Krug k(r);
	cout << k.perimetar() << endl;
	cout << k.plostina() << endl;
	cout << k.ednakvi() <<endl;
    //instanciraj objekt od klasata Krug cij radius ne e definiran
	return 0;
}
