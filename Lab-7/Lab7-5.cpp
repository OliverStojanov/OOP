#include <iostream>
#include <cstring>
using namespace std;

class ZicanInstrument{
    protected:
        char ime[20];
        int brZici;
        int osnovnaCena;
    public:
        ZicanInstrument(char * i="", int z=0, int cena=0){
            strcpy(ime,i);
            brZici=z;
            osnovnaCena=cena;
        }
        bool operator==(ZicanInstrument & zi){
            if(brZici==zi.brZici){
                return true;
            }else return false;
        }
        friend ostream & operator<<(ostream &out,const ZicanInstrument &zi){
            return out<<zi.ime<<" "<<zi.brZici<<" "<<zi.osnovnaCena<<endl;
        }
        virtual double cena()=0;
};
class Mandolina : public ZicanInstrument{
    private:
        char forma[20];
    public:
        Mandolina(char * i="", int z=0, int cena=0, char *f="") : ZicanInstrument(i,z,cena){
            strcpy(forma,f);
        }
        double cena(){
            if(!strcmp(forma,"Neapolitan")){
                return osnovnaCena*0.15+osnovnaCena;
            }else return osnovnaCena;
        }
};
class Violina : public ZicanInstrument{
    private:
        double golemina;
    public:
        Violina(char * i="", int z=0, int cena=0, double g=0) : ZicanInstrument(i,z,cena){
            golemina=g;
        }
        double cena(){
            if(golemina==0.25){
                return osnovnaCena*0.1+osnovnaCena;
            }else if(golemina==1){
                return osnovnaCena*0.2+osnovnaCena;
            }else return osnovnaCena;
        }
};
int pecatiInstrumenti(ZicanInstrument &zi, ZicanInstrument **i, int n){
    for(int j=0;j<n;j++){
        if(*i[j] == zi){
            cout << i[j]->cena() << endl;
        }
    }
}
int main() {
	char ime[20];
	int brojZici;
	float cena;
	char forma[20];
	cin >> ime >> brojZici >> cena >> forma;
	Mandolina m(ime, brojZici, cena, forma);
	int n;
	cin >> n;
	ZicanInstrument **zi = new ZicanInstrument*[2 * n];
	for(int i = 0; i < n; ++i) {
		cin >> ime >> brojZici >> cena >> forma;
		zi[i] = new Mandolina(ime, brojZici, cena, forma);
	}
	for(int i = 0; i < n; ++i) {
		float golemina;
		cin >> ime >> brojZici >> cena >> golemina;
		zi[n + i] = new Violina(ime, brojZici, cena, golemina);
	}
	pecatiInstrumenti(m, zi, 2 * n);
	for(int i = 0; i < 2 * n; ++i) {
		delete zi[i];
	}
	delete [] zi;
	return 0;
}
