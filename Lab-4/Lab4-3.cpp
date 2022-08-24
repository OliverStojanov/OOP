#include<iostream>
#include <cstring>
using namespace std;
class Avtomobil{
    private:
        char boja[20],brend[20],model[20];
    public:
        Avtomobil(char *_boja="", char *_brend="", char *_model=""){
            strcpy(boja,_boja);
            strcpy(brend,_brend);
            strcpy(model,_model);
        }
        Avtomobil & operator=(const Avtomobil & avto){
            if(this!=&avto){
                strcpy(boja,avto.boja);
                strcpy(brend,avto.brend);
                strcpy(model,avto.model);
            }
        }
        char * getBoja(){
            return boja;
        }
        char * getBrend(){
            return brend;
        }
        char * getModel(){
            return model;
        }
};
class ParkingPlac{
    private:
        char adresaPlac[20], *id;
        int cena, zarabotka, brParkirani;
        Avtomobil *car;
    public:
        ParkingPlac(){
            strcpy(adresaPlac,"");
            id=new char[0];
            cena=0;
            brParkirani=0;
            car= new Avtomobil[0];
        }
        ParkingPlac(char *adresa,char * i,int _cena){
            strcpy(adresaPlac,adresa);
            cena=_cena;
            id=new char[strlen(i)+1];
            strcpy(id,i);
        }
        ParkingPlac(const ParkingPlac & pp){
            strcpy(adresaPlac,pp.adresaPlac);
            cena=pp.cena;
            id=new char[strlen(pp.id)+1];
            strcpy(id,pp.id);
            brParkirani=pp.brParkirani;
            car=new Avtomobil[brParkirani];
            for(int i=0;i<brParkirani;i++){
                car[i]=pp.car[i];
            }
        }
        ~ParkingPlac(){
            delete [] id;
            delete [] car;
        }
        ParkingPlac & operator=(ParkingPlac & pp){
            if(this!=&pp){
                delete [] id;
                delete [] car;
                strcpy(adresaPlac,pp.adresaPlac);
                cena=pp.cena;
                id=new char[strlen(pp.id)+1];
                strcpy(id,pp.id);
                brParkirani=pp.brParkirani;
                car=new Avtomobil[brParkirani];
                for(int i=0;i<brParkirani;i++){
                    car[i]=pp.car[i];
                }
            }
        }
        char * getId(){
            return id;
        }
        void pecati(){
            if(zarabotka!=0){
                cout<<id<<" "<<adresaPlac<<" - "<<zarabotka<<" denari"<<endl;
            }
            else{
                cout<<id<<" "<<adresaPlac<<endl;
            }
        }
        int platiCasovi(int casovi){
            zarabotka+=casovi*cena;
        }
        bool daliIstaAdresa(ParkingPlac p){
            if(!strcmp(adresaPlac,p.adresaPlac)){
                return true;
            }else return false;
        }
        void parkirajVozilo(Avtomobil & novoVozilo){
        Avtomobil *temp = new Avtomobil[brParkirani + 1];
        for (int i = 0; i < brParkirani; i++)
        {
            temp[i] = car[i];
        }
        delete [] car;
        car = temp;
        car[brParkirani] = novoVozilo;
        brParkirani++;
        }
        void pecatiParkiraniVozila(){
            cout<<"Vo parkingot se parkirani slednite vozila:"<<endl;
            for(int i=0;i<brParkirani;i++){
                cout<<i+1<<"."<<car[i].getBoja()<<" "<<car[i].getBrend()<<" "<<car[i].getModel()<<endl;
            }
        }
};

int main(){

	ParkingPlac p[100];
	int n,m;
	char adresa[50],id[50];
	int brojcasovi,cenacas;
	cin>>n;
	if(n > 0){


		for (int i=0;i<n;i++){
	        cin.get();
			cin.getline(adresa,50);
			cin>>id>>cenacas;

			ParkingPlac edna(adresa,id,cenacas);

	        p[i]=edna;
		}

		//plakjanje
		cin>>m;
		for (int i=0;i<m;i++){

			cin>>id>>brojcasovi;

	        int findId=false;
	        for (int j=0;j<m;j++){
	            if (strcmp(p[j].getId(),id)==0){
	                p[j].platiCasovi(brojcasovi);
	                findId=true;
	            }
	        }
			if (!findId)
	        cout<<"Ne e platen parking. Greshen ID."<<endl;
		}

	    cout<<"========="<<endl;
	    ParkingPlac pCentar("Cvetan Dimov","C10",80);
		for (int i=0;i<n;i++)
	        if (p[i].daliIstaAdresa(pCentar))
	            p[i].pecati();
	} else {

		ParkingPlac najdobarPlac("Mars", "1337", 1);
	    int brVozila;
	    cin >> brVozila;
	    for(int i = 0; i < brVozila; ++i){

	    	char boja[20];
	    	char brend[20];
	    	char model[20];

	    	cin >> boja >> brend >> model;
	    	Avtomobil novAvtomobil(boja, brend, model);
	    	najdobarPlac.parkirajVozilo(novAvtomobil);
	    }
	    if(brVozila != 0)
	    najdobarPlac.pecatiParkiraniVozila();

	}
}
