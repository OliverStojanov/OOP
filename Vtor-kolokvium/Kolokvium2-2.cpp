#include <iostream>
#include <cstring>
using namespace std;

class Vozac{
    protected:
        char ime[100];
        int vozrast, brTrki;
        bool veteran;
    public:
        Vozac(const char * i="", int v=0, int t=0, bool vet=false){
            strcpy(ime,i);
            vozrast=v;
            brTrki=t;
            veteran=vet;
        }
        friend ostream & operator<<(ostream &out, Vozac &vo){
            out<<vo.ime<<endl<<vo.vozrast<<endl<<vo.brTrki<<endl;
            if(vo.veteran){
                out<<"VETERAN"<<endl;
            }
            return out;
        }
        virtual double zarabotuvacka() = 0;
        virtual double danok() = 0;
        bool operator==(Vozac & vo){
            return zarabotuvacka()==vo.zarabotuvacka();
        }
};

class Avtomobilist : public Vozac{
    private:
        double cenaAvto;
    public:
        Avtomobilist(const char * i="", int v=0, int t=0, bool vet=false, double ca=0) : Vozac(i,v,t,vet){
            cenaAvto=ca;
        }
        double zarabotuvacka(){
            return cenaAvto/5;
        }
        double danok(){
            if(brTrki>10){
                return zarabotuvacka()*0.15;
            }else return zarabotuvacka()*0.1;
        }
};

class Motociklist : public Vozac{
    private:
        int moknostMotor;
    public:
        Motociklist(const char * i="", int v=0, int t=0, bool vet=false, int mm=0) : Vozac(i,v,t,vet){
            moknostMotor=mm;
        }
        double zarabotuvacka(){
            return moknostMotor*20;
        }
        double danok(){
            if(veteran){
                return zarabotuvacka()*0.25;
            }else return zarabotuvacka()*0.2;
        }
};

int soIstaZarabotuvachka(Vozac ** v, int n, Vozac *vo){
    int br=0;
    for(int i=0; i<n; i++){
        if(*v[i]==*vo){
            br++;
        }
    }
    return br;
}

int main() {
	int n, x;
	cin >> n >> x;
	Vozac **v = new Vozac*[n];
	char ime[100];
	int vozrast;
	int trki;
	bool vet;
	for(int i = 0; i < n; ++i) {
		cin >> ime >> vozrast >> trki >> vet;
		if(i < x) {
			float cena_avto;
			cin >> cena_avto;
			v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
		} else {
			int mokjnost;
			cin >> mokjnost;
			v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
		}
	}
	cout << "=== DANOK ===" << endl;
	for(int i = 0; i < n; ++i) {
		cout << *v[i];
		cout << v[i]->danok() << endl;
	}
	cin >> ime >> vozrast >> trki >> vet;
	int mokjnost;
	cin >> mokjnost;
	Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
	cout << "=== VOZAC X ===" << endl;
	cout << *vx;
	cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
	cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
	return 0;
}
