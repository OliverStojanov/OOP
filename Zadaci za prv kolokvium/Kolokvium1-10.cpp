#include<iostream>
using namespace std;
struct Igrac {
    char korisnickoIme[15];
    int nivo;
    int poeni;

};
struct KompjuterskaIgra {
    char ime[20];
    Igrac lista[30];
    int n;
};
void najdobarIgrac(KompjuterskaIgra *igri,int n) {
    int indeksNajmnoguIgraci=0;
    for (int i=1; i<n; i++) {
        if (igri[i].n>igri[indeksNajmnoguIgraci].n)
            indeksNajmnoguIgraci=i;
    }

    KompjuterskaIgra najpopularna=igri[indeksNajmnoguIgraci];
    int indeksmax=0;
    for (int i=1; i<najpopularna.n; i++) {
        if (najpopularna.lista[i].poeni>najpopularna.lista[indeksmax].poeni)
            indeksmax=i;
        else if (najpopularna.lista[i].poeni==najpopularna.lista[indeksmax].poeni) {
            if (najpopularna.lista[i].nivo>najpopularna.lista[indeksmax].nivo)
                indeksmax=i;
        }
    }
    cout<<"Najdobar igrac e igracot so korisnicko ime ";
    cout<<najpopularna.lista[indeksmax].korisnickoIme;
    cout<<" koj ja igra igrata ";
    cout<<najpopularna.ime;
}
int main() {
    int n,m;
    char ime[20];
    cin>>n;
    KompjuterskaIgra poleigri[100];
    for (int i=0; i<n; i++) {
        KompjuterskaIgra nova;
        cin>>nova.ime>>nova.n;
        Igrac pole[30];
        for (int j=0; j<nova.n; j++) {
            Igrac nov;
            cin>>nov.korisnickoIme>>nov.nivo>>nov.poeni;
            nova.lista[j]=nov;
        }
        poleigri[i]=nova;
    }

    najdobarIgrac(poleigri,n);
    return 0;
}
