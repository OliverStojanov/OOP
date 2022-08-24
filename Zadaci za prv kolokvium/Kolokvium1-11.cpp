#include <iostream>
#include <cstring>
using namespace std;

class Ucesnik{
    private:
        char * ime;
        bool pol;
        int vozrast;
    public:
        Ucesnik(char * _ime="", bool _pol=false, int _vozrast=0){
            ime=new char[strlen(_ime)+1];
            strcpy(ime,_ime);
            pol=_pol;
            vozrast=_vozrast;
        }
        ~Ucesnik(){}
        Ucesnik & operator>(Ucesnik & u){
            if(vozrast>u.vozrast)
                return *this;
        }
        int getVozrast(){
            return vozrast;
        }
        friend ostream &operator<<(ostream &out, Ucesnik & u){
            out<<u.ime<<endl;
            if(u.pol==0){
            out<<"zhenski"<<endl;
            }
            else{
            out<<"mashki"<<endl;
            }
            out<<u.vozrast<<endl;
            return out;
        }
};
class Maraton{
    private:
        char lokacija[100];
        Ucesnik * ucesnik;
        int brUcesnici;
    public:
        Maraton(char * _lokacija, Ucesnik _ucesnik[]=0, int _brUcesnici=0){
            strcpy(lokacija,_lokacija);
            brUcesnici=_brUcesnici;
            ucesnik= new Ucesnik[brUcesnici];
            for(int i=0; i<brUcesnici; i++){
                ucesnik[i]=_ucesnik[i];
            }
        }
        Maraton & operator+=(Ucesnik & u){
            Ucesnik * tmp= new Ucesnik[brUcesnici+1];
            for(int i=0; i<brUcesnici; i++){
                tmp[i]=ucesnik[i];
            }
            delete [] ucesnik;
            ucesnik=tmp;
            ucesnik[brUcesnici]=u;
            brUcesnici++;
            return *this;
        }
        double prosecnoVozrast(){
            double vkVozrast=0;
            for(int i=0; i<brUcesnici; i++){
                vkVozrast+=ucesnik[i].getVozrast();
            }
            return vkVozrast/brUcesnici;
        }
        void pecatiPomladi(Ucesnik &u){
            for(int i=0; i<brUcesnici; i++){
                if(ucesnik[i].getVozrast()<u.getVozrast()){
                    cout<<ucesnik[i];
                }
            }
        }
};
int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
    	u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
	m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for(int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
	return 0;
}
