#include <iostream>
#include <cstring>
using namespace std;

class Koncert{
    private:
        char naziv[20], lokacija[20];
        static double popust;
        double cenaBilet;
    public:
        Koncert(char * n="" , char * l="" , double cb=0){
            strcpy(naziv,n);
            strcpy(lokacija,l);
            cenaBilet=cb;
        }
        static double setSezonskiPopust(double sp){
            popust=sp;
        }
        char * getNaziv(){
            return naziv;
        }
        char * getLokacija(){
            return lokacija;
        }
        static double getSezonskiPopust(){
            return popust;
        }
        virtual double cena() const{
            return cenaBilet - cenaBilet * popust;
        }
};

class ElektronskiKoncert : public Koncert{
    private:
        char * imeDJ;
        double vremetraenje;
        bool dnevna;
    public:
        ElektronskiKoncert(char * n="" , char * l="" , double cb=0 , char *dj=0 , double v=0, bool d=true) : Koncert (n,l,cb){
            imeDJ = new char[strlen(dj)+1];
            strcpy(imeDJ,dj);
            vremetraenje=v;
            dnevna=d;
        }
        ~ElektronskiKoncert(){
            delete [] imeDJ;
        }
        double cena() const {
            if(vremetraenje>7){
                if(dnevna){
                    return Koncert::cena()+310;
                }else return Koncert::cena()+460;
            }else if (vremetraenje>5){
                if(dnevna){
                    return Koncert::cena()+100;
                }else return Koncert::cena()+250;
            }else{
                if(dnevna){
                    return Koncert::cena()-50;
                }else return Koncert::cena()+100;
            }
        }

};
void najskapKoncert(Koncert ** koncerti, int n) {
    int max=0;
    int brEl=0;
    for(int i=1; i<n; i++){
        if(koncerti[i]->cena()>koncerti[max]->cena()){
            max=i;
        }
        ElektronskiKoncert *tmp= dynamic_cast<ElektronskiKoncert*>(koncerti[i]);
        if(tmp!=0){
            brEl++;
        }
    }
    cout<<"Najskap koncert: "<<koncerti[max]->getNaziv()<<" "<<koncerti[max]->cena()<<endl;
    cout<<"Elektronski koncerti: "<<brEl<<" od vkupno "<<n<<endl;
}
bool prebarajKoncert(Koncert ** koncerti, int n, char * naziv, bool elektronski) {
    int ima = false;
    for(int i = 0; i < n; i++){
        ElektronskiKoncert *tmp= dynamic_cast<ElektronskiKoncert*>(koncerti[i]);
        if(elektronski && !tmp){
            continue;
        }
        if(!strcmp(koncerti[i]->getNaziv(), naziv)){
            cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena()<<endl;
            ima = true;
        }
    }
    return ima;
}
double Koncert::popust=0.2;
int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

        cin>>tip;
        if (tip==1){//Koncert
        	cin>>naziv>>lokacija>>cenaBilet;
        	Koncert k1(naziv,lokacija,cenaBilet);
        	cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
        }
        else if (tip==2){//cena - Koncert
            cin>>naziv>>lokacija>>cenaBilet;
        	Koncert k1(naziv,lokacija,cenaBilet);
        	cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
        }
        else if (tip==3){//ElektronskiKoncert
            cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
            ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
            cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
        }
        else if (tip==4){//cena - ElektronskiKoncert
             cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
             ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
             cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
        }
        else if (tip==5) {//najskapKoncert

        }
        else if (tip==6) {//prebarajKoncert
            Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
            char naziv[100];
        	najskapKoncert(koncerti,5);
        }
        else if (tip==7){//prebaraj
        	  Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
            char naziv[100];
            bool elektronski;
        	cin>>elektronski;
        	if(prebarajKoncert(koncerti,5, "Area",elektronski))
                cout<<"Pronajden"<<endl;
            else cout<<"Ne e pronajden"<<endl;

            if(prebarajKoncert(koncerti,5, "Area",!elektronski))
                cout<<"Pronajden"<<endl;
            else cout<<"Ne e pronajden"<<endl;

        }
        else if (tip==8){//smeni cena
        	  Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[2] -> setSezonskiPopust(0.9);
        	najskapKoncert(koncerti,4);
        }

    return 0;
}
