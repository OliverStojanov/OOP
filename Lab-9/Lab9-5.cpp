#include<iostream>
#include<cstring>
using namespace std;

class InvalidDateException{
    private:
        int den,mes,god;
    public:
        InvalidDateException(int d,int m,int g){
            den=d;
            mes=m;
            god=g;
        }
        void message(){
            cout<<"Invalid Date "<<den<<"/"<<mes<<"/"<<god<<endl;
        }
};
class NotSupportedCurrencyException{
    private:
        char valuta[4];
    public:
        NotSupportedCurrencyException(char * v){
            strcpy(valuta,v);
        }
        void message(){
            cout<<valuta<<" is not a supported currency"<<endl;
        }
};
class Transakcija{
    protected:
        int den,mesec,godina;
        double iznos;
        static double USD,EUR;
    public:
        Transakcija(int d=1, int m=1, int g=1990, double i=0){
            if(d<1 || d>31 || m<1 || m>12){
                throw InvalidDateException(d,m,g);
            }else{
                den=d;
                mesec=m;
                godina=g;
                iznos=i;
            }
        }
        virtual double voDenari() = 0;
        virtual double voEvra() = 0;
        virtual double voDolari() = 0;
        virtual void pecati() = 0;
        static void setEUR(double newEUR){
            EUR=newEUR;
        }
        static void setUSD(double newUSD){
            USD=newUSD;
        }
        static double getKursEur(){
            return EUR;
        }
        static double getKursUsd(){
            return USD;
        }
};
class DeviznaTransakcija : public Transakcija{
    private:
        char valuta[4];
    public:
        DeviznaTransakcija(int d=1, int m=1, int g=1990, double i=0 , char * v="") : Transakcija(d,m,g,i){
            if(!strcmp(v,"USD") || !strcmp(v,"EUR")){
                strcpy(valuta,v);
            }else{
                throw NotSupportedCurrencyException(v);
            }
        }
        double voDenari(){
            if(!strcmp(valuta,"USD")){
                return iznos*USD;
            }else if(!strcmp(valuta,"EUR")){
                return iznos*EUR;
            }
        }
        double voEvra(){
            if(!strcmp(valuta,"EUR")){
                return iznos;
            }else if(!strcmp(valuta,"USD")){
                return iznos*USD/EUR;
            }
        }
        double voDolari(){
            if(!strcmp(valuta,"EUR")){
                return iznos*EUR/USD;
            }else if(!strcmp(valuta,"USD")){
                return iznos;
            }
        }
        void pecati(){
            cout<<den<<"/"<<mesec<<"/"<<godina<<" "<<iznos<<" "<<valuta<<endl;
        }
};

class DenarskaTransakcija : public Transakcija{
    public:
        DenarskaTransakcija(int d=1, int m=1, int g=1990, double i=0) : Transakcija(d,m,g,i){}
        double voDenari(){
            return iznos;
        }
        double voEvra(){
            return iznos/EUR;
        }
        double voDolari(){
            return iznos/USD;
        }
        void pecati(){
            cout<<den<<"/"<<mesec<<"/"<<godina<<" "<<iznos<<" MKD"<<endl;
        }
};

class Smetka{
    private:
        Transakcija ** transakcii;
        int brTransakcii;
        char brSmetka[16];
        double saldoDen;
    public:
        Smetka(char * brS="", double saldo=0){
            strcpy(brSmetka,brS);
            saldoDen=saldo;
            transakcii = new Transakcija*[0];
            brTransakcii=0;
        }
        ~Smetka(){
            delete [] transakcii;
        }
        Smetka &operator+=(Transakcija * t){
            Transakcija **tmp= new Transakcija*[brTransakcii+1];
            for(int i=0;i<brTransakcii;i++){
                tmp[i]=transakcii[i];
            }
            delete [] transakcii;
            transakcii = tmp;
            transakcii[brTransakcii]=t;
            brTransakcii++;
            return *this;
        }
        void izvestajVoDenari(){
            double saldoDenari=saldoDen;
            for(int i=0;i<brTransakcii; i++){
                saldoDenari+=transakcii[i]->voDenari();
            }
            if((double)(saldoDenari - (int)saldoDenari) == 0.5) saldoDenari -= 0.5;
            cout<<"Korisnikot so smetka: "<<brSmetka<<" ima momentalno saldo od "<<saldoDenari<<" MKD"<<endl;
        }

        void izvestajVoEvra(){
            double saldoEUR=saldoDen / Transakcija::getKursEur();
            for(int i=0;i<brTransakcii; i++){
                saldoEUR+=transakcii[i]->voEvra();
            }
            cout<<"Korisnikot so smetka: "<<brSmetka<<" ima momentalno saldo od "<<saldoEUR<<" EUR"<<endl;
        }
        void izvestajVoDolari(){
            double saldoUSD=saldoDen / Transakcija::getKursUsd();
            for(int i=0;i<brTransakcii; i++){
                saldoUSD+=transakcii[i]->voDolari();
            }
            cout<<"Korisnikot so smetka: "<<brSmetka<<" ima momentalno saldo od "<<saldoUSD<<" USD"<<endl;
        }
        void pecatiTransakcii(){
            for(int i=0;i<brTransakcii; i++){
                transakcii[i]->pecati();
            }
        }
};
double Transakcija::USD = 50;
double Transakcija::EUR = 61;

int main () {

	Smetka s ("300047024112789",1500);

	int n, den, mesec, godina, tip;
	double iznos;
	char valuta [3];

	cin>>n;
    cout<<"===VNESUVANJE NA TRANSAKCIITE I SPRAVUVANJE SO ISKLUCOCI==="<<endl;
	for (int i=0;i<n;i++){
		cin>>tip>>den>>mesec>>godina>>iznos;
		if (tip==2){
			cin>>valuta;
			try{
			Transakcija * t = new DeviznaTransakcija(den,mesec,godina,iznos,valuta);
			s+=t;
            //delete t;
            }
            catch(NotSupportedCurrencyException &valuta){
			    valuta.message();
			}
			catch(InvalidDateException &datum){
                datum.message();
            }
		}
		else {
		    try{
			Transakcija * t = new DenarskaTransakcija(den,mesec,godina,iznos);
			s+=t;
            //delete t;
		    }
		    catch(NotSupportedCurrencyException &valuta){
			    valuta.message();
			}
			catch(InvalidDateException &datum){
                datum.message();
            }
		}

	}
    cout<<"===PECHATENJE NA SITE TRANSAKCII==="<<endl;
    s.pecatiTransakcii();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.izvestajVoDenari();


    cout<<"\n===PROMENA NA KURSOT NA EVROTO I DOLAROT===\n"<<endl;


    double newEUR, newUSD;
    cin>>newEUR>>newUSD;
    Transakcija::setEUR(newEUR);
    Transakcija::setUSD(newUSD);
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.izvestajVoDenari();




	return 0;
}
