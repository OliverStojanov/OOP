#include <iostream>
#include <cstring>
using namespace std;

class FudbalskaEkipa{
    protected:
        char imeTrener[100];
        int brGolovi[10];
    public:
        FudbalskaEkipa(char * ime="", int *br=0){
            strcpy(imeTrener, ime);
            for(int i=0; i<10; i++){
                brGolovi[i]=br[i];
            }
        }
        virtual char * getIme() = 0;
        virtual double uspeh() = 0;
        friend ostream & operator<<(ostream &out, FudbalskaEkipa &k){
            out<<k.getIme()<<endl;
            out<<k.imeTrener<<endl;
            out<<k.uspeh()<<endl;
            return out;
        }
        bool operator>(FudbalskaEkipa &fe){
            return uspeh()>fe.uspeh();
        }
        FudbalskaEkipa & operator+=(int n){
            for(int i=0; i<9; i++){
                brGolovi[i]=brGolovi[i+1];
            }
            brGolovi[9]=n;
        }
};
class Klub : public FudbalskaEkipa{
    private:
        char imeKlub[20];
        int brTituli;
    public:
        Klub(char * ime="", int *br=0, char * ik="", int brt=0) :FudbalskaEkipa(ime, br){
            strcpy(imeKlub, ik);
            brTituli = brt;
        }
        char * getIme(){
            return imeKlub;
        }
        double uspeh(){
            double u=0;
            for(int i=0; i<10; i++){
                u+=brGolovi[i];
            }
            return u*3+brTituli*1000;
        }
};
class Reprezentacija : public FudbalskaEkipa{
    private:
        char imeDrzava[30];
        int brNastapi;
    public:
        Reprezentacija(char * ime="", int *br=0, char * id="", int brn=0) :FudbalskaEkipa(ime, br){
            strcpy(imeDrzava, id);
            brNastapi = brn;
        }
        char * getIme(){
            return imeDrzava;
        }
        double uspeh(){
            double u=0;
            for(int i=0; i<10; i++){
                u+=brGolovi[i];
            }
            return u*3+brNastapi*50;
        }
};

void najdobarTrener(FudbalskaEkipa **fe, int n){
    int najdobar=0;
    for(int i=1; i<n; i++){
        if(*fe[i]>*fe[najdobar]){
            najdobar=i;
        }
    }
    cout<<*fe[najdobar];
}

int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}
