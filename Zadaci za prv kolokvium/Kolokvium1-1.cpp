#include <iostream>
#include <string.h>
using namespace std;
enum tip{pop,rap,rok};
class Pesna{
    private:
    char *ime;
    int vreme;
    tip tipp;
    public:
    Pesna(){}
    Pesna(char *i, int v, tip ti){
        ime = new char [strlen(i) + 1];
        strcpy(ime, i);
        vreme = v;
        tipp = ti;
    }
    int getVreme(){
        return vreme;
    }
    tip getTip(){
        return tipp;
    }
    void pecati(){
        cout << '"' << ime << '"' << "-" << vreme << "min" << endl;
    }};
class CD{
    private:
    Pesna pesni[10];
    int brPesni, maxVreme;
    public:
    CD(int maks = 0, int br = 0){
        maxVreme = maks;
        brPesni = br;
    }
    CD(Pesna p[], int br, int maks){
        for(int i = 0; i < br; i++){
            pesni[i] = p[i];
        }
        brPesni = br;
        maxVreme = maks;
    }
    void dodadiPesna(Pesna p){
        if(brPesni < 10){
            int vkpVreme = 0;
            for(int i = 0; i < brPesni; i++){
                vkpVreme += pesni[i].getVreme();
            }
            if(vkpVreme + p.getVreme() < maxVreme){
                pesni[brPesni] = p;
                brPesni++;
            }}}
    void pecatiPesniPoTip(tip t){
        for(int i = 0; i < brPesni; i++){
            if(pesni[i].getTip() == t){
                pesni[i].pecati();
            }}}
    Pesna getPesna(int i){
        return pesni[i];
    }
    int getBroj(){
        return brPesni;
    }};
int main() {
	// se testira zadacata modularno
    int testCase;
    cin >> testCase;

	int n, minuti, kojtip;
	char ime[50];

	if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
		p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<n; i++)
				(omileno.getPesna(i)).pecati();
	}
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<omileno.getBroj(); i++)
				(omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

return 0;
}
