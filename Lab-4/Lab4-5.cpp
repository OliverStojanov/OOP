#include <iostream>
#include <cstring>
using namespace std;

class Pica{
    private:
        char ime[15], *sostojki;
        int cena, namalenie;
    public:
        Pica(char * i="",int c=0, char *s="", int n=0){
            strcpy(ime,i);
            cena=c;
            sostojki=new char[strlen(s)+1];
            strcpy(sostojki,s);
            namalenie=n;
        }
        Pica(const Pica & pica){
            strcpy(ime,pica.ime);
            cena=pica.cena;
            sostojki=new char[strlen(pica.sostojki)+1];
            strcpy(sostojki,pica.sostojki);
            namalenie=pica.namalenie;
        }
        ~Pica(){
            delete [] sostojki;
        }
        Pica & operator=(Pica &pica){
            if(this!=&pica){
                delete [] sostojki;
                strcpy(ime,pica.ime);
                cena=pica.cena;
                sostojki=new char[strlen(pica.sostojki)+1];
                strcpy(sostojki,pica.sostojki);
                namalenie=pica.namalenie;
            }
            return *this;
        }
        void pecati(){
            cout<<ime<<" - "<<sostojki<<","<<cena<<endl;
        }
        bool istiSe(Pica p){
            if(!strcmp(sostojki,p.sostojki)){
                return true;
            }else return false;
        }
        char * getIme(){
            return ime;
        }
        int getNamaluvanje(){
            return namalenie;
        }
        char * getSostojki(){
            return sostojki;
        }
        int getCena(){
            return cena;
        }
};
class Picerija{
    private:
        char ime[15];
        Pica * pica;
        int brPica;
    public:
        Picerija(char * _ime="", Pica _pica[]=0,int br=0){
            strcpy(ime,_ime);
            pica=new Pica[br];
            brPica=br;
            for(int i=0;i<br;i++){
                pica[i]=_pica[i];
            }
        }
        Picerija(const Picerija & pi){
            strcpy(ime,pi.ime);
            pica=new Pica[pi.brPica];
            brPica=pi.brPica;
            for(int i=0;i<pi.brPica;i++){
                pica[i]=pi.pica[i];
            }
        }
        Picerija & operator=(Picerija & pi){
            if(this!=&pi){
                delete [] pica;
                strcpy(ime,pi.ime);
                pica=new Pica[pi.brPica];
                brPica=pi.brPica;
                for(int i=0;i<pi.brPica;i++){
                    pica[i]=pi.pica[i];
                }
            }return *this;
        }
        char * getIme(){
            return ime;
        }
        void setIme(char *i){
            strcpy(ime,i);
        }
        ~Picerija(){
            delete [] pica;
        }
        void dodadi(Pica p){
            Pica *temp=new Pica[brPica+1];
            for(int i=0; i<brPica; i++){
                if(!strcmp(pica[i].getSostojki(),p.getSostojki())){
                    return;
                }
            }
            for(int i=0;i<brPica;i++){
                temp[i]=pica[i];
            }
            delete [ ]pica;
            pica=temp;
            pica[brPica]=p;
            brPica++;
        }
        void piciNaPromocija(){
            for(int i=0; i<brPica; i++){
                if(pica[i].getNamaluvanje()>0){
                    cout<<pica[i].getIme()<<" - "<<pica[i].getSostojki()<<", "<<pica[i].getCena();
                    cout<<" "<<pica[i].getCena() - (pica[i].getNamaluvanje() / 100. * pica[i].getCena())<<endl ;
                }
            }
        }
};
int main () {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for(int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp,100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki,100);
        int popust;
        cin >> popust;
        Pica p(imp,cena,sostojki,popust);
        p1.dodadi(p);
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp,100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki,100);
    int popust;
    cin >> popust;
    Pica p(imp,cena,sostojki,popust);
    p2.dodadi(p);

    cout<<p1.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p1.piciNaPromocija();

    cout<<p2.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p2.piciNaPromocija();

	return 0;
}

