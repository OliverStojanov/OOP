#include <iostream>
#include <cstring>
using namespace std;

class Transport{
    protected:
        char *destinacija;
        int oCena;
        int rastojanieDes;
    public:
        Transport(char *d, int oc, int r){
            destinacija = new char [strlen(d)+1];
            strcpy(destinacija,d);
            oCena=oc;
            rastojanieDes=r;
        }
        virtual double cenaTransport(){
            return oCena;
        }
        bool operator<(Transport &t){
            return rastojanieDes<t.rastojanieDes;
        }
        friend ostream & operator<<(ostream &out, Transport & t){
            return out<<t.destinacija<<" "<<t.rastojanieDes<<" "<<t.cenaTransport()<<endl;
        }
};

class AvtomobilTransport : public Transport{
    private:
        bool platenSofer;
    public:
        AvtomobilTransport(char *d, int oc, int r, bool ps) : Transport(d, oc, r){
            platenSofer=ps;
        }
        double cenaTransport(){
            if(platenSofer){
                return Transport::cenaTransport()*1.2;
            }return Transport::cenaTransport();
        }
};

class KombeTransport : public Transport{
    private:
        int brLuge;
    public:
        KombeTransport(char *d, int oc, int r, int br) : Transport(d, oc, r){
            brLuge=br;
        }
        double cenaTransport(){
            return Transport::cenaTransport()-brLuge*200;
        }
};

void pecatiPoloshiPonudi(Transport **ponudi, int n, Transport t){
    Transport **polosi = new Transport*[n];
    int j=0;
    for(int i=0; i<n; i++){
        if(ponudi[i]->cenaTransport()>t.cenaTransport()){
            polosi[j]=ponudi[i];
            j++;
        }
    }
    for(int i=0; i<j ; i++){
        for(int k=i+1; k<j; k++){
            if(*polosi[k]<*polosi[i]){
                Transport *tmp=polosi[i];
                polosi[i]=polosi[k];
                polosi[k]=tmp;
            }
        }
    }
    for(int i=0; i<j; i++){
        cout<<*polosi[i];
    }
}

int main(){

char destinacija[20];
int tip,cena,rastojanie,lugje;
bool shofer;
int n;
cin>>n;
Transport  **ponudi;
ponudi=new Transport *[n];

for (int i=0;i<n;i++){

    cin>>tip>>destinacija>>cena>>rastojanie;
    if (tip==1) {
        cin>>shofer;
        ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

    }
    else {
        cin>>lugje;
        ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
    }


}

AvtomobilTransport nov("Ohrid",2000,600,false);
pecatiPoloshiPonudi(ponudi,n,nov);

for (int i=0;i<n;i++) delete ponudi[i];
delete [] ponudi;
return 0;
}
