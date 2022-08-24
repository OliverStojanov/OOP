#include <iostream>
#include <cstring>
using namespace std;
enum Tip{LINUX, UNIX, WINDOWS};
class OperativenSistem{
    private:
        char * imeOS;
        double golemina,verzija;
        Tip tip;
    public:
        OperativenSistem(char * ime="", double ver=0, Tip t=(Tip)-1, double gol=0){
            imeOS= new char[strlen(ime)+1];
            strcpy(imeOS,ime);
            verzija=ver;
            tip=t;
            golemina=gol;
        }
        OperativenSistem(const OperativenSistem & os){
            imeOS= new char[strlen(os.imeOS)+1];
            strcpy(imeOS,os.imeOS);
            verzija=os.verzija;
            tip=os.tip;
            golemina=os.golemina;
        }
        ~OperativenSistem(){
            delete [] imeOS;
        }
        OperativenSistem & operator=(const OperativenSistem & os){
            if(this!=&os){
                delete [] imeOS;
                imeOS= new char[strlen(os.imeOS)+1];
                strcpy(imeOS,os.imeOS);
                verzija=os.verzija;
                tip=os.tip;
                golemina=os.golemina;
            }
            return *this;
        }
        void pecati(){
            cout<<"Ime: "<<imeOS<<" Verzija: "<<verzija<<" Tip: "<<tip<<" Golemina:"<<golemina<<"GB"<<endl;
        }
        bool ednakviSe(const OperativenSistem &os){
            if(!strcmp(imeOS,os.imeOS) && verzija==os.verzija && tip==os.tip && golemina==os.golemina){
                return true;
            }else return false;
        }
        int sporediVerzija(const OperativenSistem &os){
            if(verzija==os.verzija){
                return 0;
            }else if (verzija<os.verzija){
                return -1;
            }else return 1;
        }
        bool istaFamilija(const OperativenSistem &os){
            if(!strcmp(imeOS,os.imeOS)){
                if(tip==os.tip){
                    return true;
                }
            }
            return false;
        }

};

class Repozitorium{
    private:
        char imeRep[20];
        OperativenSistem * osi;
        int brOS;
    public:
        Repozitorium(const char *ime){
            strcpy(imeRep,ime);
            osi= new OperativenSistem[0];
            brOS=0;
        }
        ~Repozitorium(){
            delete [] osi;
        }
        void pecatiOperativniSistemi(){
            cout<<"Repozitorium: "<<imeRep<<endl;
            for(int i=0; i<brOS; i++){
                osi[i].pecati();
            }
        }
        void izbrishi(const OperativenSistem &opSi){
            for(int i=0; i<brOS; i++){
                if(osi[i].ednakviSe(opSi)){
                    for(int j=i; j<brOS-1; j++){
                        osi[j]=osi[j+1];
                    }
                    brOS--;
                    i++;
                }
            }
        }
        void dodadi(const OperativenSistem &nov){
            OperativenSistem *tmp=new OperativenSistem[brOS+1];
            for(int i=0; i<brOS; i++){
                if(osi[i].istaFamilija(nov) && osi[i].sporediVerzija(nov)==-1){
                    osi[i]=nov;
                    return;
                }
            }
            for(int i=0; i<brOS; i++){
                tmp[i]=osi[i];
            }
            delete [] osi;
            osi=tmp;
            osi[brOS]=nov;
            brOS++;
        }
};

int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
     cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}
