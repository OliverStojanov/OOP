#include <iostream>

using namespace std;
class Kvadrat {
    protected:
        double a;
    public:
        Kvadrat(double _a=0){
            a=_a;
        }
        Kvadrat(const Kvadrat & k){
            a=k.a;
        }
        double perimetar(){
            return 4*a;
        }
        double plostina(){
            return a*a;
        }
        void pecati(){
            cout<<"Kvadrat so dolzina a="<<a<<" ima plostina P="<<plostina()<<" i perimetar L="<<perimetar()<<endl;
        }
};

class Pravoagolnik : public Kvadrat{
    private:
        double x,y;
    public:
        Pravoagolnik() : Kvadrat(){
            x=0;
            y=0;
        }
        Pravoagolnik (const Kvadrat &k, double _x, double _y) : Kvadrat(k){
            x=_x;
            y=_y;
        }
        Pravoagolnik (const Pravoagolnik & p) : Kvadrat(p){
            x=p.x;
            y=p.y;
        }
        double perimetar(){
            return 2*(a+x)+2*(a+y);
        }
        double plostina(){
            return (a+x)*(a+y);
        }
        void pecati(){
            if((a+x)==(a+y)){
                Kvadrat(a+x).pecati();
            }else{
                cout<<"Pravoagolnik so strani: "<<a+x<<" i "<<a+y<<" ima plostina P="<<plostina()<<" i perimetar L="<<perimetar()<<endl;
            }
        }
};

int main() {
	int n;
    double a,x,y;
	Kvadrat * kvadrati;
	Pravoagolnik * pravoagolnici;

	cin>>n;

    kvadrati = new Kvadrat [n];
    pravoagolnici = new Pravoagolnik [n];

	for (int i=0;i<n;i++){
		cin>>a;

		kvadrati[i] = Kvadrat(a);
	}

	for (int i=0;i<n;i++){
		cin>>x>>y;

		pravoagolnici[i]=Pravoagolnik(kvadrati[i],x,y);
	}

	int testCase;
	cin>>testCase;

	if (testCase==1){
		cout<<"===Testiranje na klasata Kvadrat==="<<endl;
		for (int i=0;i<n;i++)
			kvadrati[i].pecati();
	}
	else {
		cout<<"===Testiranje na klasata Pravoagolnik==="<<endl;
		for (int i=0;i<n;i++)
			pravoagolnici[i].pecati();
	}
}
