#include<iostream>
#include<string.h>
using namespace std;

class Delo{
    private:
        char ime[50],zemjaPoteklo[50];
        int godNapisano;
    public:
        Delo(const char *i="", int god=0, char * zm=""){
            strcpy(ime,i);
            strcpy(zemjaPoteklo,zm);
            godNapisano=god;
        }
        bool operator==(Delo &d){
            return !strcmp(ime,d.ime);
        }
        int getGod(){
            return godNapisano;
        }
        char * getZemja(){
            return zemjaPoteklo;
        }
        char * getIme(){
            return ime;
        }
};
class Pretstava{
    protected:
        Delo delo;
        int brProdadeniKarti;
        char data[15];
    public:
        Pretstava(Delo d=0, int brProdadeni=0, char * _data=""){
            delo=d;
            brProdadeniKarti=brProdadeni;
            strcpy(data,_data);
        }
        virtual double cena(){
            if(!strcmp(delo.getZemja(),"Rusija")){
                if(delo.getGod()>=1900){
                    return 200;
                }else if(delo.getGod()>=1800){
                    return 225;
                }else return 250;
            }else if(!strcmp(delo.getZemja(),"Italija")){
                if(delo.getGod()>=1900){
                    return 150;
                }else if(delo.getGod()>=1800){
                    return 175;
                }else return 200;
            }else{
                if(delo.getGod()>=1900){
                    return 130;
                }else if(delo.getGod()>=1800){
                    return 155;
                }else return 180;
            }
        }
        int getKarti(){
            return brProdadeniKarti;
        }
        Delo getDelo(){
            return delo;
        }
};
class Opera : public Pretstava{
    public:
        Opera(Delo d=0, int brProdadeni=0, char * _data="") : Pretstava(d,brProdadeni,_data){}
        double cena(){
            return Pretstava::cena();
        }
};
class Balet : public Pretstava{
    private:
        static int dopCena;
    public:
        Balet(Delo d=0, int brProdadeni=0, char * _data="") : Pretstava(d,brProdadeni,_data){}
        static int setCenaBalet(int n){
            dopCena=n;
        }
        double cena(){
            return Pretstava::cena()+dopCena;
        }
};

double prihod(Pretstava ** pretstavi, int n){
    double vkupno=0;
    for(int i=0; i<n; i++){
        vkupno+=pretstavi[i]->cena()*pretstavi[i]->getKarti();
    }
    return vkupno;
}

int brojPretstaviNaDelo(Pretstava ** pretstavi, int n, Delo d){
    int brPretstavi=0;
    for(int i=0; i<n; i++){
        if(pretstavi[i]->getDelo()==d)
        brPretstavi++;
    }
    return brPretstavi;
}

int Balet::dopCena = 150;
//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
    case 1:
    //Testiranje na klasite Opera i Balet
    {
        cout<<"======TEST CASE 1======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->getDelo().getIme()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->getDelo().getIme()<<endl;
    }break;

    case 2:
    //Testiranje na  klasite Opera i Balet so cena
    {
        cout<<"======TEST CASE 2======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->cena()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->cena()<<endl;
    }break;

    case 3:
    //Testiranje na operator ==
    {
        cout<<"======TEST CASE 3======="<<endl;
        Delo f1=readDelo();
        Delo f2=readDelo();
        Delo f3=readDelo();

        if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
        if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

    }break;

    case 4:
    //testiranje na funkcijata prihod
    {
        cout<<"======TEST CASE 4======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();

        }
        cout<<prihod(pole,n);
    }break;

    case 5:
    //testiranje na prihod so izmena na cena za 3d proekcii
    {
        cout<<"======TEST CASE 5======="<<endl;
        int cenaBalet;
        cin>>cenaBalet;
        Balet::setCenaBalet(cenaBalet);
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }
        cout<<prihod(pole,n);
        }break;

    case 6:
    //testiranje na brojPretstaviNaDelo
    {
        cout<<"======TEST CASE 6======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }

        Delo f=readDelo();
        cout<<brojPretstaviNaDelo(pole,n,f);
    }break;

    };


return 0;
}
