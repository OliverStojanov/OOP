#include <iostream>
#include <cstring>
using namespace std;
enum Tip {
    LINUX,
    UNIX,
    WINDOWS
};
class OperativenSistem{
    private:
         char * ime;
         float verzija, golemina;
         Tip tip;
    public:
        OperativenSistem(char *_ime="",float _verzija=0.0, Tip t=(Tip)-1, float _golemina=0.0){
            ime=new char[strlen(_ime)+1];
            strcpy(ime,_ime);
            verzija=_verzija;
            tip=t;
            golemina=_golemina;
        }
        OperativenSistem(const OperativenSistem & os){
            ime=new char[strlen(os.ime)+1];
            strcpy(ime,os.ime);
            verzija=os.verzija;
            tip=os.tip;
            golemina=os.golemina;
        }
        ~OperativenSistem(){
            delete [] ime;
        }
        OperativenSistem & operator=(const OperativenSistem & os){
            if(this!=&os){
                delete [] ime;
                ime=new char[strlen(os.ime)+1];
                strcpy(ime,os.ime);
                verzija=os.verzija;
                tip=os.tip;
                golemina=os.golemina;
            }
            return *this;
        }
        void pecati(){
            cout<<"Ime: "<<ime<<" Verzija: "<<verzija<<" Tip: "<<tip<<" Golemina:"<<golemina<<"GB"<<endl;
        }
        bool ednakviSe(const OperativenSistem &os){
            if(!strcmp(ime,os.ime)){
                if(verzija==os.verzija){
                    if(tip==os.tip){
                        if(golemina==os.golemina){
                            return true;
                        }
                    }
                }
            }return false;
        }
        int sporediVerzija(const OperativenSistem &os){
            if(verzija==os.verzija){
                return 0;
            }else if(verzija<os.verzija){
                return -1;
            }else return 1;
        }
        bool istaFamilija(const OperativenSistem &sporedba){
            if(!strcmp(ime,sporedba.ime)){
                if(tip==sporedba.tip){
                    return true;
                }
            }return false;
        }
};

class Repozitorium{
    private:
        char ime[20];
        OperativenSistem * os;
        int brOs;
    public:
        Repozitorium(const char * _ime){
            strcpy(ime,_ime);
            brOs=0;
            os=new OperativenSistem[0];
        }
        ~Repozitorium(){
            delete [] os;
        }
        void pecatiOperativniSistemi(){
            cout<<"Repozitorium: "<<ime<<endl;
            for(int i=0; i<brOs; i++){
                os[i].pecati();
            }
        }
        void izbrishi(const OperativenSistem &operativenSistem){
            for(int i=0; i<brOs; i++){
                if(os[i].ednakviSe(operativenSistem)){
                    for(int j = i; j < brOs - 1; j++){
                        os[j] = os[j+1];
                    }
                    brOs--;
                    i++;
                }
            }
        }
        void dodadi(const OperativenSistem &nov){
            for(int i=0;i<brOs;i++){
                if(os[i].istaFamilija(nov)&&(os[i].sporediVerzija(nov)==-1)){
                    os[i]=nov;
                    return;
                }
            }
            OperativenSistem *temp= new OperativenSistem[brOs+1];
            for (int i = 0; i < brOs; i++){
                temp[i]=os[i];
            }
            delete [] os;
            os=temp;
            os[brOs]=nov;
            brOs++;
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
