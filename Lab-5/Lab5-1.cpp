#include <iostream>
#include <cstring>
using namespace std;

class Automobile {
    private:
        char * marka;
        int * registracija;
        int maxBrzina;
    public:
        Automobile(char * _marka="", int *_registracija=0, int _maxBrzina=0){
            marka = new char [strlen(_marka)+1];
            strcpy(marka,_marka);
            registracija=new int[5];
            if(_registracija!=0){
                for(int i=0;i<5;i++){
                    registracija[i]=_registracija[i];
                }
            }
            maxBrzina=_maxBrzina;
        }
        Automobile(const Automobile & avto){
            marka = new char [strlen(avto.marka)+1];
            strcpy(marka,avto.marka);
            registracija=new int[5];
            for(int i=0;i<5;i++){
                registracija[i]=avto.registracija[i];
            }
            maxBrzina=avto.maxBrzina;
        }
        ~Automobile(){
            delete [] marka;
            delete [] registracija;
        }
        Automobile &operator=(const Automobile & avto){
            if(this!=&avto){
                delete [] marka;
                delete [] registracija;
                marka = new char [strlen(avto.marka)+1];
                strcpy(marka,avto.marka);
                registracija=new int[5];
                for(int i=0;i<5;i++){
                    registracija[i]=avto.registracija[i];
                }
            maxBrzina=avto.maxBrzina;
            }
            return *this;
        }
        bool operator==(const Automobile & avto){
            for(int i=0;i<5;i++){
                if(registracija[i]!=avto.registracija[i]){
                    return false;
                }
            }
            return true;
        }
        friend ostream & operator<<(ostream &out, Automobile &avto){
            out<<"Marka\t"<<avto.marka<<"\tRegistracija[ ";
            for(int i=0;i<5;i++){
                out<<avto.registracija[i]<<" ";
            }
            out<<"]"<<endl;
            return out;
        }
        int getMaxBrzina(){
            return maxBrzina;
        }
};
class RentACar{
    private:
        char ime[100];
        Automobile *a;
        int brAuto;
    public:
        RentACar(char *_ime=0){
            strcpy(ime,_ime);
            a=new Automobile[0];
            brAuto=0;
        }

        RentACar &operator+=(const Automobile &avto){
            Automobile *temp= new Automobile[brAuto+1];
            for(int i=0;i<brAuto;i++){
                temp[i]=a[i];
            }
            delete [] a;
            a=temp;
            a[brAuto]=avto;
            brAuto++;
            return *this;
        }
        RentACar &operator-=(const Automobile &avto){
            Automobile *temp= new Automobile[brAuto-1];
            int j=0;
            for(int i=0;i<brAuto;i++){
                if(!(a[i]==avto)){
                    temp[j]=a[i];
                    j++;
                }
            }
            delete [] a;
            a=temp;
            brAuto=j;
        }
        void pecatiNadBrzina(int max){
            cout<<ime<<endl;
            for(int i=0;i<brAuto;i++){
                if(a[i].getMaxBrzina()>max){
                    cout<<a[i];
                }
            }
        }
};
int main()
{
   RentACar agencija("FINKI-Car");
   int n;
   cin>>n;

   for (int i=0;i<n;i++)
   {
    	char marka[100];
    	int regisracija[5];
    	int maximumBrzina;

       	cin>>marka;

       	for (int i=0;i<5;i++)
    		cin>>regisracija[i];

    	cin>>maximumBrzina;

       	Automobile nov=Automobile(marka,regisracija,maximumBrzina);

    	//dodavanje na avtomobil
       	agencija+=nov;

   }
    //se cita grehsniot avtmobil, za koj shto avtmobilot so ista registracija treba da se izbrishe
    char marka[100];
    int regisracija[5];
    int maximumBrzina;
    cin>>marka;
    for (int i=0;i<5;i++)
    cin>>regisracija[i];
    cin>>maximumBrzina;

    Automobile greshka=Automobile(marka,regisracija,maximumBrzina);

    //brishenje na avtomobil
    agencija-=greshka;

    agencija.pecatiNadBrzina(150);

    return 0;
}
