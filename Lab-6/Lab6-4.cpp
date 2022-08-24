#include <iostream>
#include <cstring>
using namespace std;

class Nedviznina{
    protected:
        char * adresa;
        int kvadratura;
        int cenaKvadrat;
    public:
        Nedviznina(char * _adresa="",int _kvadratura=0, int _cenaKvadrat=0){
            adresa= new char[strlen(_adresa)+1];
            strcpy(adresa,_adresa);
            kvadratura=_kvadratura;
            cenaKvadrat=_cenaKvadrat;
        }
        Nedviznina(const Nedviznina & n){
            adresa= new char[strlen(n.adresa)+1];
            strcpy(adresa,n.adresa);
            kvadratura=n.kvadratura;
            cenaKvadrat=n.cenaKvadrat;
        }
        Nedviznina & operator=(Nedviznina & n){
            if(this!=&n){
                delete [] adresa;
                adresa= new char[strlen(n.adresa)+1];
                strcpy(adresa,n.adresa);
                kvadratura=n.kvadratura;
                cenaKvadrat=n.cenaKvadrat;
            }
            return *this;
        }
        ~Nedviznina(){
            delete [] adresa;
        }
        friend istream &operator>>(istream &in, Nedviznina & n){
            in>>n.adresa>>n.kvadratura>>n.cenaKvadrat;
        }
        int cena(){
            return kvadratura*cenaKvadrat;
        }
        void pecati(){
            cout<<adresa<<", Kvadratura: "<<kvadratura<<", Cena po Kvadrat: "<<cenaKvadrat<<endl;
        }
        double danokNaImot(){
            return cena()/100.0*5;
        }
        char * getAdresa(){
            return adresa;
        }
};
class Vila : public Nedviznina{
    private:
        double danokNaLuksuz;
    public:
        Vila(char * _adresa="",int _kvadratura=0, int _cenaKvadrat=0, double _danokNaLuksuz=0) : Nedviznina(_adresa,_kvadratura,_cenaKvadrat){
            danokNaLuksuz=_danokNaLuksuz;
        }
        Vila(const Vila & v) : Nedviznina(v){
            danokNaLuksuz=v.danokNaLuksuz;
        }
        friend istream &operator>>(istream &in, Vila & v){
            in>>v.adresa>>v.kvadratura>>v.cenaKvadrat>>v.danokNaLuksuz;
        }
        double danokNaImot(){
             return cena() * (0.05 + danokNaLuksuz / 100.);
        }
        void pecati(){
             cout << adresa << ", Kvadratura: " << kvadratura << ", Cena po Kvadrat: "
             << cenaKvadrat << ", Danok na luksuz: " << danokNaLuksuz << endl;
        }
};
int main(){
    Nedviznina n;
    Vila v;
    cin>>n;
    cin>>v;
    n.pecati();
    cout<<"Danok za: "<<n.getAdresa()<<", e: "<<n.danokNaImot()<<endl;
    v.pecati();
    cout<<"Danok za: "<<v.getAdresa()<<", e: "<<v.danokNaImot()<<endl;
    return 0;
}
