#include<iostream>
#include<string.h>
using namespace std;
typedef struct tanc{
    char ime[15];
    char zemja[15];
}tanc;
typedef struct tancer{
    char ime[20];
    char prezime[20];
    tanc niza[5];
}Tancer;
void tancuvanje(Tancer *t, int n, char *zemja){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(strcmp(t[i].niza[j].zemja,zemja)==0){
            cout<<t[i].ime<<" "<<t[i].prezime<<", "<<t[i].niza[j].ime<<endl;break;}
        }
    }
}

int main()
{
    int i, j, n;
    char zemja[15];
	Tancer tanceri[5];
    cin >> n;
    for(i = 0; i < n; i++){
        cin >> tanceri[i].ime;
        cin >> tanceri[i].prezime;
        for(j = 0; j < 3; j++){
        	cin >> tanceri[i].niza[j].ime;
            cin >> tanceri[i].niza[j].zemja;
        }
    }
    cin >> zemja;
    tancuvanje(tanceri, n, zemja);
	return 0;
}
