#include <iostream>
#include <cstring>
using namespace std;

class Ekipa{
    protected:
        char ime[15];
        int brPobedi, brPorazi;
    public:
        Ekipa(char * _ime="",int _brPobedi=0, int _brPorazi=0){
            strcpy(ime,_ime);
            brPobedi=_brPobedi;
            brPorazi=_brPorazi;
        }
        void pecati(){
            cout<<"Ime: "<<ime<<" Pobedi: "<<brPobedi<<" Porazi: "<<brPorazi;
        }
};
class FudbalskaEkipa : public Ekipa{
    private:
        int brCrveni,brZolti,brNereseni;
    public:
        FudbalskaEkipa(char * _ime="",int _brPobedi=0, int _brPorazi=0,int crveni=0,int zolti=0, int nereseni=0) : Ekipa(_ime,_brPobedi,_brPorazi){
            brCrveni=crveni;
            brZolti=zolti;
            brNereseni=nereseni;
        }
        void pecati(){
            cout<<"Ime: "<<ime<<" Pobedi: "<<brPobedi<<" Porazi: "<<brPorazi<<" Nereseni: "<<brNereseni<<" Poeni: "<<brPobedi*3+brNereseni;
        }
};

int main(){
	char ime[15];
	int pob,por,ck,zk,ner;
	cin>>ime>>pob>>por>>ck>>zk>>ner;
	FudbalskaEkipa f1(ime,pob,por,ck,zk,ner);
	f1.pecati();
	return 0;
}
