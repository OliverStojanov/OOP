#include<iostream>
#include<cstring>
using namespace std;

class Zichara{
    private:
        char *mesto;
        int dnevnaCena;
    public:
        Zichara(char *_mesto="", int dc=0){
            mesto=new char[strlen(_mesto)+1];
            strcpy(mesto,_mesto);
            dnevnaCena=dc;
        }
        int getCena(){
            return dnevnaCena;
        }
};
class PlaninarskiDom{
    private:
        char ime[15];
        int cenaSezona[2];
        char klasa;
        bool daliImaZichara;
        Zichara * zicara;
    public:
        PlaninarskiDom(){}
        PlaninarskiDom(char  _ime[15], int *_cenaSezona, char _klasa){
            strcpy(ime,_ime);
            for(int i=0; i<2; i++){
                cenaSezona[i]=_cenaSezona[i];
            }
            klasa=_klasa;
            daliImaZichara=false;
        }
        ~PlaninarskiDom(){}
        void setZichara(Zichara & z){
            zicara=&z;
            daliImaZichara=true;
        }
        PlaninarskiDom &operator=(PlaninarskiDom &other){
            strcpy(ime, other.ime); this->klasa = other.klasa; daliImaZichara = other.daliImaZichara;
            for(int i=0;i<2;i++){cenaSezona[i]=other.cenaSezona[i];} zicara = other.zicara;
        }
        PlaninarskiDom operator--(){
            if(klasa=='F'){
                return *this;
            }
            klasa++;
            return *this;
        }
        friend ostream & operator<<(ostream &out, PlaninarskiDom &pd){
             out<<pd.ime<<" klasa:"<<pd.klasa;
             if(pd.daliImaZichara){
                 out<<" so Zichara"<<endl;
             }
             else out<<endl;
             return out;
        }
        bool operator<=(char c){
            if((int)toupper(this->klasa)>=(int)toupper(c))
                return true;
            else return false;
        }
        void presmetajDnevenPrestoj(int day, int month, int &sum){
            if (day > 31 || day <= 0 || month > 12 || month <= 0){
                throw 1;
            }
            sum = (this->daliImaZichara?this->zicara->getCena():0) + (month>=4||(month <= 9 && day == 1)?cenaSezona[0]:cenaSezona[1]);
        }
};

int main(){

   PlaninarskiDom p; //креирање на нов објект од класата планинарски дом

   //во следниот дел се вчитуваат информации за планинарскиот дом
   char imePlaninarskiDom[15],mestoZichara[30],klasa;
   int ceni[12];
   int dnevnakartaZichara;
   bool daliZichara;
   cin>>imePlaninarskiDom;
   for (int i=0;i<2;i++) cin>>ceni[i];
   cin>>klasa;
   cin>>daliZichara;

   //во следниот дел се внесуваат информации и за жичарата ако постои
   if (daliZichara) {
      cin>>mestoZichara>>dnevnakartaZichara;
      PlaninarskiDom pom(imePlaninarskiDom,ceni,klasa);
      Zichara r(mestoZichara,dnevnakartaZichara);
      pom.setZichara(r);
      p=pom;
   }
   else{
      PlaninarskiDom *pok=new PlaninarskiDom(imePlaninarskiDom,ceni,klasa);
      p=*pok;
   }

   //се намалува класата на планинарскиот дом за 2
   --p;
   --p;

   int cena;
   int den,mesec;
   cin>>den>>mesec;
   try{
   p.presmetajDnevenPrestoj(den,mesec,cena); //тука се користи функцијата presmetajDnevenPrestoj
   cout<<"Informacii za PlaninarskiDomot:"<<endl;
   cout<<p;
   if (p<='D')
       cout<<"Planinarskiot dom za koj se vneseni informaciite ima klasa poniska ili ista so D\n";

   cout<<"Cenata za "<<den<<"."<<mesec<<" e "<<cena; //се печати цената за дадениот ден и месец
   }
   catch (int){
      cout<<"Mesecot ili denot e greshno vnesen!";
   }
}
