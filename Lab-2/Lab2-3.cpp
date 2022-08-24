#include <iostream>
#include <cstring>
using namespace std;

class film{
    private:
        char ime[100];
        char reziser[50];
        char zanr[50];
        int godina;
    public:
        film(){}
        film(char * i, char * r, char * z,int god){
            strcpy(ime,i);
            strcpy(reziser,r);
            strcpy(zanr,z);
            godina=god;
        }
        ~film(){}
        void setIme(char *i){
            strcpy(ime,i);
        }
        void setReziser(char *r){
            strcpy(reziser,r);
        }
        void setZanr(char *z){
            strcpy(zanr,z);
        }
        int setGodina(int god){
            godina=god;
        }
        char* getIme(){
            return ime;
        }
        char* getReziser(){
            return reziser;
        }
        char* getZanr(){
            return zanr;
        }
        int getGodina(){
            return godina;
        }

};

void pecati_po_godina(film *f, int n, int godina){
    for(int i=0;i<n;i++){
        if(f[i].getGodina()==godina){
            cout<<"Ime: "<<f[i].getIme()<<endl<<"Reziser: "<<f[i].getReziser()<<endl<<"Zanr: "<<f[i].getZanr()<<endl<<"Godina: "<<f[i].getGodina()<<endl;
        }
    }
}

int main() {
 	int n;
 	cin >> n;
 	film filmovi[20];
 	for(int i = 0; i < n; ++i) {
 		char ime[100];
 		char reziser[50];
 		char zanr[50];
 		int godina;
 		cin >> ime;
 		cin >> reziser;
 		cin >> zanr;
 		cin >> godina;
 		filmovi[i].setIme(ime);
 		filmovi[i].setReziser(reziser);
 		filmovi[i].setZanr(zanr);
 		filmovi[i].setGodina(godina);
 	}
 	int godina;
 	cin >> godina;
 	pecati_po_godina(filmovi,n,godina);
 	return 0;
 }
