#include <iostream>
#include <cstring>

using namespace std;
class Dogovor;
class Potpisuvac{
    private:
    	char Ime[20], Prezime[20];
	    char Embg[14];
	public:
	    Potpisuvac(){};
	    Potpisuvac(char * _Ime,char * _Prezime,char * _Embg){
	        strcpy(Ime,_Ime);
	        strcpy(Prezime,_Prezime);
	        strcpy(Embg,_Embg);
	    }
	    Potpisuvac(const Potpisuvac &p){
	        strcpy(Ime,p.Ime);
	        strcpy(Prezime,p.Prezime);
	        strcpy(Embg,p.Embg);
	    }
	    friend Dogovor;
};
class Dogovor{
    private:
        int brDogovor;
        char kategorija[50];
        Potpisuvac potpisuvaci[3];
    public:
        Dogovor(){}
        Dogovor(int br,char * _kategorija, Potpisuvac p[]){
            brDogovor=br;
            strcpy(kategorija,_kategorija);
            for(int i=0;i<3;i++){
            potpisuvaci[i]=p[i];
            }
        }

        ~Dogovor(){}
        bool proverka(){
            for(int i=0;i<3;i++){
                for(int j=i+1;j<3;j++){
                    if(strcmp(potpisuvaci[i].Embg,potpisuvaci[j].Embg)==0)
                    return true;
                }
            }return false;
        }
};



//ne smee da se menuva main funkcijata
int main()
{
    char embg[14], ime[20], prezime[20], kategorija[20];
    int broj, n;
    cin >> n;
    for(int i = 0; i < n; i++){
    	cin >> embg >> ime >> prezime;
    	Potpisuvac p1(ime, prezime, embg);
    	cin >> embg >> ime >> prezime;
    	Potpisuvac p2(ime, prezime, embg);
    	cin >> embg >> ime >> prezime;
    	Potpisuvac p3(ime, prezime, embg);
    	cin >> broj >> kategorija;
    	Potpisuvac p[3];
    	p[0] = p1; p[1] = p2; p[2] = p3;
    	Dogovor d(broj, kategorija, p);
        cout << "Dogovor " << broj << ":" << endl;
    	if(d.proverka() == true)
    	    cout << "Postojat potpishuvaci so ist EMBG" << endl;
    	else
    	    cout << "Ne postojat potpishuvaci so ist EMBG" << endl;
    }
    return 0;
}
