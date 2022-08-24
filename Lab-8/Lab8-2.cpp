#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class Igrachka {
public:
    Igrachka(){}
    virtual float getVolumen() = 0;
    virtual float getMasa() = 0;
    virtual float getPlostina() = 0;
};

class Forma {
protected:
    char boja[100];
    int gustina;
public:
    Forma(char * b="", int g=0){
        strcpy(boja,b);
        gustina=g;
    }
    // да се имплементираат потребните методи

};
class Topka : public Forma, public Igrachka{
    private:
        int radius;
    public:
        Topka(char * b="", int g=0, int r=0) : Forma(b,g){
            radius=r;
        }
        float getVolumen(){
            return 4/3. * 3.14 * radius * radius * radius;
        }
        float getMasa(){
            return getVolumen()*gustina;
        }
        float getPlostina(){
            return 4 * 3.14 * radius * radius;
        }
};
class Kocka : public Forma, public Igrachka{
    private:
        int visina, sirina, dlabocina;
    public:
        Kocka(char * b="", int g=0, int v=0, int s=0, int d=0) : Forma(b,g){
            visina=v;
            sirina=s;
            dlabocina=d;
        }
        float getVolumen(){
            return visina*sirina*dlabocina;
        }
        float getMasa(){
            return getVolumen()*gustina;
        }
        float getPlostina(){
            return 2 * sirina * visina + 2 * sirina * dlabocina + 2 * dlabocina * visina;
        }
};


int main(){
    int n;
    cin>>n;
    Igrachka **kupche=new Igrachka*[n];
    double vkMasa=0, maxVolumen=0, minPlostina=11110;

    for (int i=0; i<n;i++){
        int br, gustina;
        char boja[100];
        cin>>br>>boja>>gustina;
        if(br==1){
            int radius;
            cin>>radius;
            kupche[i]=new Topka(boja,gustina,radius);
        }else if(br==2){
            int visina, sirina, dlabocina;
            cin>>visina>>sirina>>dlabocina;
            kupche[i]= new Kocka(boja,gustina,visina,sirina,dlabocina);
        }
        vkMasa+=kupche[i]->getMasa();
        if(kupche[i]->getVolumen() > maxVolumen){
            maxVolumen=kupche[i]->getVolumen();
        }
        if(kupche[i]->getPlostina() < minPlostina){
            minPlostina=kupche[i]->getPlostina();
        }
    }
    int gus, vis, sir, dlab;
    char bojaa[100];
    cin>>bojaa>>gus>>vis>>sir>>dlab;
    Kocka Petra(bojaa,gus,vis,sir,dlab);
    if(vkMasa>Petra.getMasa()){
        cout<<"DA"<<endl;
    }else cout<<"NE"<<endl;
    cout<<"Razlikata e: "<<fabs(maxVolumen-Petra.getVolumen())<<endl;
    cout<<"Razlikata e: "<<fabs(minPlostina- Petra.getPlostina())<<endl;
	return 0;
}
