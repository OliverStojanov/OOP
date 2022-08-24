#include<iostream>
using namespace std;
class Vozilo{
    protected:
        double masa;
        int sirina,visina;
    public:
        Vozilo(double m=0, int s=0, int v=0){
            masa=m;
            sirina=s;
            visina=v;
        }
        double getMasa(){
            return masa;
        }
        int getSirina(){
            return sirina;
        }
        int getVisina(){
            return visina;
        }
        virtual int tip() = 0;
        virtual int vratiDnevnaCena() = 0;
};
class Avtomobil : public Vozilo{
    private:
        int brVrati;
    public:
        Avtomobil(double m=0, int s=0, int v=0, int br=0) : Vozilo(m,s,v){
            brVrati=br;
        }
        int tip(){
            return 1;
        }
        int vratiDnevnaCena(){
            if(brVrati<5){
                return 100;
            }else return 130;
        }
};
class Avtobus : public Vozilo{
    private:
        int brPatnici;
    public:
        Avtobus(double m=0, int s=0, int v=0, int br=0) : Vozilo(m,s,v){
            brPatnici=br;
        }
        int tip(){
            return 2;
        }
        int vratiDnevnaCena(){
            return brPatnici*5;
        }
};
class Kamion : public Vozilo{
    private:
        double maxMasa;
    public:
        Kamion(double m=0, int s=0, int v=0, int mm=0) : Vozilo(m,s,v){
            maxMasa=mm;
        }
        double getNosivost(){
            return maxMasa;
        }
        int tip(){
            return 3;
        }
        int vratiDnevnaCena(){
            return (maxMasa + masa)*0.02;
        }
};
class ParkingPlac{
    private:
        Vozilo ** vozilo;
        int brElementi;
    public:
        ParkingPlac(Vozilo ** vozil=0, int brE=0){
            brElementi = brE;
            vozilo= new Vozilo*[brE];
            for(int i=0; i<brE; i++){
                vozilo[i]=vozil[i];
            }
        }
        ~ParkingPlac(){
            delete [] vozilo;
        }
        ParkingPlac &operator+=(Vozilo * vo){
            Vozilo **tmp = new Vozilo*[brElementi+1];
            for(int i=0; i<brElementi; i++){
                tmp[i]=vozilo[i];
            }
            delete [] vozilo;
            vozilo=tmp;
            vozilo[brElementi]=vo;
            brElementi++;
            return *this;
        }
        double presmetajVkupnaMasa(){
            double vkupnaMasa=0;
            for(int i=0;i<brElementi; i++){
                vkupnaMasa+=vozilo[i]->getMasa();
            }
            return vkupnaMasa;
        }
        int brojVozilaPoshirokiOd(int l){
            int n=0;
            for(int i=0;i<brElementi; i++){
                if(vozilo[i]->getSirina() >l){
                    n++;
                }
            }
            return n;
        }
        void pecati(){
            int c=0,b=0,t=0;
            for(int i=0;i<brElementi;i++){
                if(vozilo[i]->tip()==1){
                    c++;
                }else if(vozilo[i]->tip()==2){
                    b++;
                }else if(vozilo[i]->tip()==3){
                    t++;
                }
            }
            cout<<"Brojot na avtomobili e "<<c<<", brojot na avtobusi e "<<b<<" i brojot na kamioni e "<<t<<"."<<endl;
        }
        int pogolemaNosivostOd(Vozilo& v){
            int br=0;
            for(int i=0;i<brElementi;i++){
                Kamion *kam = dynamic_cast<Kamion *>(vozilo[i]);
                if(kam != 0 && kam->getNosivost()){
                    br++;
                }
            }
            return br;
        }
        int vratiDnevnaZarabotka(){
            int zarabotka=0;
            for(int i=0;i<brElementi;i++){
                zarabotka+=vozilo[i]->vratiDnevnaCena();
            }
            return zarabotka;
        }
};

int main(){
ParkingPlac p;

int n;
cin>>n;
int shirina,visina, broj;
float masa,nosivost;
for (int i=0;i<n;i++){
    int type;
    cin>>type;
    if(type==1){
        cin>>masa>>shirina>>visina>>broj;
        Avtomobil *a=new Avtomobil(masa,shirina,visina,broj);
        p+=a;
    }
    if(type==2){
        cin>>masa>>shirina>>visina>>broj;
        p+=new Avtobus(masa,shirina,visina,broj);
    }
    if(type==3){
        cin>>masa>>shirina>>visina>>nosivost;
        p+=new Kamion(masa,shirina,visina,nosivost);
    }
}

p.pecati();

cout<<"\nZarabotkata e "<<p.vratiDnevnaZarabotka()<<endl;
cout<<"Vkupnata masa e "<<p.presmetajVkupnaMasa()<<endl;
cout<<"Brojot poshiroki od 5 e "<<p.brojVozilaPoshirokiOd(5)<<endl;
Avtomobil a(1200,4,3,5);
cout<<"Brojot na kamioni so nosivost pogolema od avtomobilot e "<<p.pogolemaNosivostOd(a)<<endl;


}
