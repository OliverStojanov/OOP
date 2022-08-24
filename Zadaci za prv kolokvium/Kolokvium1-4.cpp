#include<iostream>
#include<cstring>
using namespace std;

class Patnik{
    private:
	    char ime[100];
	    int klasa;
    	bool velosiped;
    public:
	    Patnik(char * _ime="", int _klasa=1, bool _velosiped=false){
	        strcpy(ime,_ime);
	        klasa=_klasa;
	        velosiped=_velosiped;
	    }
	    int getKlasa(){
	        return klasa;
	    }
	    bool getVelosiped(){
	        return velosiped;
	    }
	    friend ostream & operator<<(ostream &out, Patnik & p){
	        return out<<p.ime<<endl<<p.klasa<<endl<<p.velosiped<<endl;
	    }
};

class Voz{
    private:
	    char destinacija[100];
	    Patnik * p;
	    int brEl, brVel;
    public:
	    Voz(char * _destinacija="", int _brVel=0, Patnik pa[]=0, int _brEl=0){
	        strcpy(destinacija, _destinacija);
	        brEl=_brEl;
	        brVel=_brVel;
	        p= new Patnik[brEl];
	        for(int i=0; i<brEl; i++){
	            p[i]=pa[i];
	        }
	    }
	    Voz & operator+=(Patnik & pa){
	        if(pa.getVelosiped() && brVel || !pa.getVelosiped()){
    	        Patnik *tmp=new Patnik[brEl+1];
	            for(int i=0; i<brEl; i++){
	                tmp[i]=p[i];
	            }
    	        delete [] p;
	            p=tmp;
	            p[brEl]=pa;
	            brEl++;
	        }
	        return * this;
	    }
	    friend ostream & operator<<(ostream &out, Voz & v){
	        out<<v.destinacija<<endl;
	        for(int i=0; i<v.brEl; i++){
	            out<<v.p[i]<<endl;
	        }
	        return out;
	    }
	    void patniciNemaMesto(){
	        int klasa1=0, klasa2=0;
	        for(int i=0; i<brEl; i++){
	            if(p[i].getKlasa()==1 && p[i].getVelosiped()){
	                klasa1++;
	            }else if(p[i].getKlasa()==2 && p[i].getVelosiped()){
	                klasa2++;
	            }
	        }
	        if(brVel>=klasa1){
	            cout<<"Brojot na patnici od 1-va klasa koi ostanale bez mesto e: 0"<<endl;
	            if(brVel-klasa1>=klasa2){
	                cout<<"Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: 0"<<endl;
	            }else{
	                cout<<"Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: "<<klasa2-(brVel-klasa1)<<endl;
	            }
	        }else{
	            cout<<"Brojot na patnici od 1-va klasa koi ostanale bez mesto e: "<<klasa1-brVel<<endl;
	            cout<<"Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: "<<klasa2<<endl;
	        }
	    }
};


int main()
{
	Patnik p;
	char ime[100], destinacija[100];
	int n;
	bool velosiped;
	int klasa;
	int maxv;
	cin >> destinacija >> maxv;
	cin >> n;
	Voz v(destinacija, maxv);
	//cout<<v<<endl;
	for (int i = 0; i < n; i++){
		cin >> ime >> klasa >> velosiped;
		Patnik p(ime, klasa, velosiped);
		//cout<<p<<endl;
		v += p;
	}
	cout << v;
	v.patniciNemaMesto();

	return 0;
}
