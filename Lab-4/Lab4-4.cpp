#include <iostream>
#include <cstring>
using namespace std;

enum zanr{akcija,komedija,drama};
class Film{
    private:
    char *ime;
    float gol;
    zanr zanrr;
    public:
    Film(char *i = "", float g = 0, zanr z = (zanr)-1){
        ime = new char[strlen(i) + 1];
        strcpy(ime, i);
        gol = g;
        zanrr = z;
    }
    Film(const Film &f1){
        ime = new char[strlen(f1.ime) + 1];
        strcpy(ime, f1.ime);
        gol = f1.gol;
        zanrr = f1.zanrr;
    }
    ~Film(){
        delete [] ime;
    }
    Film& operator=(const Film &f1){
        if(this != &f1){
            delete [] ime;
            ime = new char[strlen(f1.ime) + 1];
            strcpy(ime, f1.ime);
            gol = f1.gol;
            zanrr = f1.zanrr;
        }
        return *this;
    }
    void pecati(){
        cout << gol << "MB" << "-" << '"' << ime << '"' << endl;
    }
    friend class DVD;
};

class DVD{
    private:
    Film filmovi[5];
    int brFilmovi, gol;
    public:
    DVD(Film f[] = 0, int br = 0, int g = 0){
        for(int i = 0; i < br; i++){
            filmovi[i] = f[i];
        }
        brFilmovi = br;
        gol = g;
    }
    DVD(int g = 0){
        brFilmovi = 0;
        gol = g;
    }
    DVD(const DVD &dvd){
        for(int i = 0; i < dvd.brFilmovi; i++){
            filmovi[i] = dvd.filmovi[i];
        }
        brFilmovi = dvd.brFilmovi;
        gol = dvd.gol;
    }
    int getBroj(){
        return brFilmovi;
    }
    Film getFilm(int i){
        return filmovi[i];
    }
    double getSuma(){
        double globSum = 0;
        for(int i = 0; i < brFilmovi; i++){
            globSum += filmovi[i].gol;
        }
        return globSum;
    }
    void dodadiFilm (Film f){
        if(getSuma() + f.gol <= gol && brFilmovi < 5){
            filmovi[brFilmovi] = f;
            brFilmovi++;
        }
    }
    void pecatiFilmoviDrugZanr(zanr z){
        for(int i = 0; i < brFilmovi; i++){
            if(filmovi[i].zanrr != z){
                filmovi[i].pecati();
            }
        }
    }
    float procentNaMemorijaOdZanr (zanr z){
        int zanrSum = 0;
        for(int i = 0; i < brFilmovi; i++){
            if(filmovi[i].zanrr == z){
                zanrSum += filmovi[i].gol;
            }
        }
        return zanrSum/getSuma() * 100;
    }
};
int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, memorija, kojzanr;
    char ime[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Film ======" << endl;
        cin >> ime;
        cin >> memorija;
        cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
        Film f(ime, memorija, (zanr) kojzanr);
        f.pecati();
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < n; i++)
            (omileno.getFilm(i)).pecati();
    } else if (testCase == 3) {
        cout << "===== Testiranje na metodot dodadiFilm() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < omileno.getBroj(); i++)
            (omileno.getFilm(i)).pecati();
    } else if (testCase == 4) {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    } else if (testCase == 5) {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    } else if (testCase == 6){
		cout<<"===== Testiranje na metodot procentNaMemorijaOdZanr() od klasata DVD =====" <<endl;
		DVD omileno(40);
		cin >> n;
		for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        cout<<"Procent na filmovi od dadeniot zanr iznesuva: "<<omileno.procentNaMemorijaOdZanr((zanr) kojzanr)<<"%\n";

	}

    return 0;
}
