#include <iostream>
using namespace std;

struct Laptop{
	char firma[100];
    float golemina;
    bool touch;
    int cena;

    void print();

};

void Laptop::print(){
	cout << firma << " " << golemina << " " << cena << endl;

}

struct ITStore{
	char ime[100];
    char lokacija[100];
    Laptop lp[100];
    int n;

    void print();
};

void ITStore::print() {
	cout << ime << " " << lokacija << endl;
    for(int i = 0; i < n; i++){
    	lp[i].print();
    }
}

int najmalaCena(ITStore its){
	int min, f = 0;
    for(int i = 0; i<its.n; i++){
        if(its.lp[i].touch){
            if(!f){
            	min = its.lp[i].cena;
                f=1;
            }
            else if(its.lp[i].cena<min)
                min = its.lp[i].cena;
        }
    }

    return min;

}

void najeftina_ponuda(ITStore its[], int n){
	int min = najmalaCena(its[0]);
    int minI = 0;
    for(int i = 0; i<n; i++){
        if(najmalaCena(its[i]) < min){
            min = najmalaCena(its[i]);
            minI = i;
        }
    }

    cout << "Najeftina ponuda ima prodavnicata: " << endl;
    cout << its[minI].ime << " " << its[minI].lokacija << endl;
    cout << "Najniskata cena iznesuva: " << najmalaCena(its[minI]) << endl;
}


int main() {
    ITStore s[100];
    int n;
    cin >> n; //broj na IT prodavnici

    //vnesuvanje na prodavnicite edna po edna, zaedno so raspolozlivite laptopvi vo niv
    for(int i = 0; i < n; i++){
    	cin >> s[i].ime;
        cin >> s[i].lokacija;
        cin >> s[i].n;
            for(int j = 0; j < s[i].n; j++){
        		cin >> s[i].lp[j].firma;
            	cin >> s[i].lp[j].golemina;
            	cin >> s[i].lp[j].touch;
            	cin >> s[i].lp[j].cena;
        }

    }


    //pecatenje na site prodavnici

    for(int i = 0; i<n; i++){
    	s[i].print();
    }


    //povik na glavnata metoda

    najeftina_ponuda(s,n);

    return 0;
}
