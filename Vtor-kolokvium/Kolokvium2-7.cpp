#include<iostream>
#include<string.h>
using namespace std;

class OutOfBoundException{
    public:
        OutOfBoundException(){}
        void message(){
            cout<<"Brojot na pin kodovi ne moze da go nadmine dozvolenoto"<<endl;
        }
};

class Karticka{
   protected:
       char smetka[16];
       int pin;
       bool povekjePin;
   public:
    Karticka(char* smetka,int pin){
       strcpy(this->smetka,smetka);
       this->pin=pin;
       this->povekjePin=false;
    }
    ~Karticka(){}
    virtual int tezinaProbivanje()const{
        int brCifri=0;
        int pinn=pin;
        for(int i=0; pinn!=0; pinn/=10){
            brCifri++;
        }
        return brCifri;
    }
    friend ostream & operator<<(ostream & out, Karticka & k){
        return out<<k.smetka<<": "<<k.tezinaProbivanje()<<endl;
    }
    bool getDopolnitelenPin(){
        return povekjePin;
    }
    char *getSmetka(){
        return smetka;
    }
};

class SpecijalnaKarticka : public Karticka{
    private:
        int * pinovi, brPinovi;
        static const int p=4;
    public:
        SpecijalnaKarticka(char* s,int pinn) : Karticka(s,pinn){
            brPinovi=0;
            pinovi=new int[0];
            povekjePin=true;
        }
        ~SpecijalnaKarticka(){
            delete [] pinovi;
        }
        int tezinaProbivanje()const{
            return Karticka::tezinaProbivanje()+brPinovi;
        }
        SpecijalnaKarticka &operator+=(int pi){
            if(brPinovi+1<=p){
                int * tmp= new int [brPinovi+1];
                for(int i=0; i<brPinovi; i++){
                    tmp[i]=pinovi[i];
                }
                delete [] pinovi;
                pinovi=tmp;
                pinovi[brPinovi]=pi;
                brPinovi++;

            }
            else {
                throw OutOfBoundException();
            }
        }
};
//вметнете го кодот за SpecijalnaKarticka



class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int limit;
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
      strcpy(this->naziv,naziv);
      for (int i=0;i<broj;i++){
        //ako kartickata ima dopolnitelni pin kodovi
        if (karticki[i]->getDopolnitelenPin()){
            this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
        }
        else this->karticki[i]=new Karticka(*karticki[i]);
      }
      this->broj=broj;
    }
    ~Banka(){
    for (int i=0;i<broj;i++) delete karticki[i];
    }
    static void setLIMIT(int n){
        limit=n;
    }
    void pecatiKarticki(){
        cout<<"Vo bankata "<<naziv<<" moze da se probijat kartickite:"<<endl;
        for(int i=0; i<broj; i++){
            if(karticki[i]->tezinaProbivanje()<=limit){
                SpecijalnaKarticka *tmp= dynamic_cast<SpecijalnaKarticka*>(karticki[i]);
                if(tmp!=0){
                    cout<<*tmp;
                }else{
                    cout<<*karticki[i];
                }
            }
        }
    }
    void dodadiDopolnitelenPin(char * smetka, int novPin){
        for(int i=0; i<broj; i++){
            if(!strcmp(karticki[i]->getSmetka(), smetka)){
                if(karticki[i]->getDopolnitelenPin()){
                    SpecijalnaKarticka *tmp= dynamic_cast<SpecijalnaKarticka*>(karticki[i]);
                    if(tmp!=0){
                        *tmp+=novPin;
                    }
                }
            }
        }
    }
};
int Banka::limit=7;


int main(){

Karticka **niza;
int n,m,pin;
char smetka[16];
bool daliDopolnitelniPin;
cin>>n;
niza=new Karticka*[n];
for (int i=0;i<n;i++){
   cin>>smetka;
   cin>>pin;
   cin>>daliDopolnitelniPin;
   if (!daliDopolnitelniPin)
    niza[i]=new Karticka(smetka,pin);
   else
    niza[i]=new SpecijalnaKarticka(smetka,pin);
}

Banka komercijalna("Komercijalna",niza,n);
for (int i=0;i<n;i++) delete niza[i];
delete [] niza;
cin>>m;
for (int i=0;i<m;i++){
   cin>>smetka>>pin;

   komercijalna.dodadiDopolnitelenPin(smetka,pin);

}

Banka::setLIMIT(5);

komercijalna.pecatiKarticki();

}
