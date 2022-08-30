#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

class NegativnaVrednost{
    public:
        void message(){
            cout<<"Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!"<<endl;
        }
};

class Oglas{
    private:
        char naslov[50], kategorija[30], opis[100];
        double cena;
    public:
        Oglas(char * _naslov="" , char *_kategorija="", char * _opis="", double _cena=0){
            strcpy(naslov,_naslov);
            strcpy(kategorija,_kategorija);
            strcpy(opis,_opis);
            cena=_cena;
        }
        bool operator>(Oglas & o){
            return cena>o.cena;
        }
        friend ostream & operator<<(ostream &out, Oglas &o){
            return out<<o.naslov<<endl<<o.opis<<endl<<o.cena<<" evra"<<endl;
        }
        double getCena(){
            return cena;
        }
        char * getKategorija(){
            return kategorija;
        }
};
class Oglasnik{
    private:
        char ime[20];
        Oglas * oglas;
        int brOglasi;
    public:
        Oglasnik(const char * _ime=""){
            strcpy(ime,_ime);
        }
        Oglasnik(const Oglasnik &o){
            strncpy(ime, o.ime, 20);
            oglas = new Oglas[o.brOglasi];
            brOglasi = o.brOglasi;
            for(int i = 0; i < brOglasi; i++){
                oglas[i] = o.oglas[i];
            }
        }
        Oglasnik & operator+=(Oglas & o){
            if(o.getCena()<0){
                throw NegativnaVrednost();
            }else{
                Oglas *tmp = new Oglas[brOglasi+1];
                for(int i=0; i<brOglasi; i++){
                    tmp[i]=oglas[i];
                }
                delete [] oglas;
                oglas=tmp;
                oglas[brOglasi]=o;
                brOglasi++;
                return *this;
            }
        }
        friend ostream & operator<<(ostream & out, Oglasnik & o){
            out<<o.ime<<endl;
            for(int i=0; i<o.brOglasi; i++){
                out<<o.oglas[i]<<endl;
            }
            return out;
        }
        void oglasiOdKategorija(const char *k){
            for(int i=0; i<brOglasi; i++){
                if(!strcmp(oglas[i].getKategorija(), k)){
                    cout<<oglas[i]<<endl;
                }
            }
        }
        void najniskaCena(){
            int min=0;
            for(int i=0; i<brOglasi; i++){
                if(oglas[i].getCena()<oglas[min].getCena()){
                    min=i;
                }
            }
            cout<<oglas[min]<<endl;
        }
};

int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
    	cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }
            catch(NegativnaVrednost &n){
                n.message();
            }
        }
        cout<<ogl;
    }
    else if (tip==4){
      	cout<<"-----Test oglasOdKategorija -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }
            catch(NegativnaVrednost &n){
                n.message();
            }
        }
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
    	cout<<"-----Test Exception -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
			try{
                ogl+=o;
            }
            catch(NegativnaVrednost &n){
                n.message();
            }
        }
        cout<<ogl;

    }
    else if (tip==6){
    	cout<<"-----Test najniskaCena -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }
            catch(NegativnaVrednost &n){
                n.message();
            }
        }
        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();

    }
    else if (tip==7){
    	cout<<"-----Test All -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }
            catch(NegativnaVrednost &n){
                n.message();
            }
        }
        cout<<ogl;

        cin.get();
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();

    }

	return 0;
}
