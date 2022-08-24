#include <iostream>
#include <cstring>
using namespace std;

class Lekar{
    protected:
        int faxDoktor;
        char ime[10],prezime[11];
        double Plata;
    public:
        Lekar(int _faxDoktor=0, char * _ime=" ", char * _prezime=" ", double _plata=0){
            faxDoktor=_faxDoktor;
            strcpy(ime,_ime);
            strcpy(prezime,_prezime);
            Plata=_plata;
        }
        Lekar(const Lekar &l){
            faxDoktor=l.faxDoktor;
            strcpy(ime,l.ime);
            strcpy(prezime,l.prezime);
            Plata=l.Plata;
        }

        void pecati(){
            cout<<faxDoktor<<": "<<ime<<" "<<prezime<<endl;
        }
        double plata(){
            return Plata;
        }
};
class MaticenLekar : public Lekar{
    private:
        int brPacienti;
        double *kotizacii;
    public:
        MaticenLekar(Lekar lekar=0,int brP=0,double * _kotizacii=0) : Lekar(lekar){
            brPacienti=brP;
            kotizacii= new double [brPacienti];
            for(int i=0;i<brPacienti;i++){
                kotizacii[i]=_kotizacii[i];
            }
        }
        double prosekKotizacii(){
            double pk=0;
            for(int i=0;i<brPacienti;i++){
                pk+=kotizacii[i];
            }
            return pk/brPacienti;
        }
        void pecati(){
            Lekar::pecati();
            cout<<"Prosek na kotizacii: "<<prosekKotizacii()<<endl;
        }
        double plata(){
            return (prosekKotizacii()*0.3)+(Lekar::plata());
        }
};

int main() {
	int n;
	cin>>n;
	int pacienti;
	double kotizacii[100];
	int faksimil;
	char ime [20];
	char prezime [20];
	double osnovnaPlata;

	Lekar * lekari = new Lekar [n];
	MaticenLekar * maticni = new MaticenLekar [n];

	for (int i=0;i<n;i++){
		cin >> faksimil >> ime >> prezime >> osnovnaPlata;
		lekari[i] = Lekar(faksimil,ime,prezime,osnovnaPlata);
	}

	for (int i=0;i<n;i++){
		cin >> pacienti;
		for (int j=0;j<pacienti;j++){
			cin >> kotizacii[j];
		}
		maticni[i]=MaticenLekar(lekari[i],pacienti,kotizacii);
	}

	int testCase;
	cin>>testCase;

	if (testCase==1){
		cout<<"===TESTIRANJE NA KLASATA LEKAR==="<<endl;
		for (int i=0;i<n;i++){
			lekari[i].pecati();
			cout<<"Osnovnata plata na gorenavedeniot lekar e: "<<lekari[i].plata()<<endl;
		}
	}
	else {
		cout<<"===TESTIRANJE NA KLASATA MATICENLEKAR==="<<endl;
		for (int i=0;i<n;i++){
			maticni[i].pecati();
			cout<<"Platata na gorenavedeniot maticen lekar e: "<<maticni[i].plata()<<endl;
		}
	}

	delete [] lekari;
	delete [] maticni;

	return 0;
}
