#include<iostream>
#include<string.h>
using namespace std;

class BadInputException{
    public:
        BadInputException(){}
        void message(){
            cout<<"Greshna opisna ocenka"<<endl;
        }
};

class StudentKurs{
   protected:
       char ime[30];
       int ocenka;
       bool daliUsno;
       static int MAX;

   public:
    StudentKurs(char* ime,int finalenIspit){
       strcpy(this->ime,ime);
       this->ocenka=finalenIspit;
       this->daliUsno=false;
    }
    static void setMAX(int n){
        MAX=n;
    }
    friend ostream & operator<<(ostream &out, StudentKurs & sk){
        out<<sk.ime<<" --- ";
        if(sk.Ocenka()>MAX){
            out<<MAX<<endl;
        }else out<<sk.Ocenka()<<endl;
        return out;
    }
    virtual int Ocenka(){
        return ocenka;
    }
    char *getIme(){
        return ime;
    }
    bool getDaliUsno(){
        return daliUsno;
    }
     //дополни ја класата
};


class StudentKursUsno : public StudentKurs{
    private:
        char * usno;
    public:
        StudentKursUsno(char* ime,int finalenIspit) : StudentKurs(ime,finalenIspit){
            usno = new char[0];
            daliUsno = true;
        }
        StudentKursUsno & operator+=(char *opisna){
            for(int i=0; i<strlen(opisna); i++){
                if(isdigit(opisna[i])){
                    throw BadInputException();
                }
            }
            delete [] usno;
            usno = new char [strlen(opisna)+1];
            strcpy(usno,opisna);
        }
        void setOpisna(char *o){
            strcpy(usno,o);
        }
        int Ocenka(){
            if(!strcmp(usno, "odlicen")){
                return ocenka + 2;
            }else if(!strcmp(usno, "dobro")){
                return ocenka + 1;
            }else if(!strcmp(usno, "losho")){
                return ocenka - 1;
            }
            return ocenka;
        }
};


class KursFakultet{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;
    static const int MINOCENKA = 6;
public:
    KursFakultet(char *naziv, StudentKurs** studenti,int broj ){
      strcpy(this->naziv,naziv);
      for (int i=0;i<broj;i++){
        //ako studentot ima usno isprashuvanje
        if (studenti[i]->getDaliUsno()){
            this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
        }
        else this->studenti[i]=new StudentKurs(*studenti[i]);
      }
      this->broj=broj;
    }
    ~KursFakultet(){
    for (int i=0;i<broj;i++) delete studenti[i];
    }
    void pecatiStudenti(){
        cout<<"Kursot "<<naziv<<" go polozile:"<<endl;
        for(int i=0; i<broj; i++){
            if(studenti[i]->Ocenka()>=MINOCENKA){
                cout<<*studenti[i];
            }
        }
    }
    void postaviOpisnaOcenka(char * im, char* opisnaOcenka){
        for(int i=0; i<broj; i++){
            if(!strcmp(studenti[i]->getIme(), im)){
                StudentKursUsno *tmp= dynamic_cast<StudentKursUsno*>(studenti[i]);
                if(tmp)
                *tmp+=opisnaOcenka;

            }
        }
    }

};

char * iscistiOcenka(char *c){
    int j=0;
    char *tmp = new char [strlen(c)+1];
    for(int i=0; i<strlen(c); i++){
        if(isalpha(c[i])){
            tmp[j]=c[i];
            j++;
        }
    }
    tmp[j]='\0';
    return tmp;
}

int StudentKurs::MAX = 10;

int main(){

StudentKurs **niza;
int n,m,ocenka;
char ime[30],opisna[10];
bool daliUsno;
cin>>n;
niza=new StudentKurs*[n];
for (int i=0;i<n;i++){
   cin>>ime;
   cin>>ocenka;
   cin>>daliUsno;
   if (!daliUsno)
    niza[i]=new StudentKurs(ime,ocenka);
   else
    niza[i]=new StudentKursUsno(ime,ocenka);
}

KursFakultet programiranje("OOP",niza,n);
for (int i=0;i<n;i++) delete niza[i];
delete [] niza;
cin>>m;

for (int i=0;i<m;i++){
   cin>>ime>>opisna;
    try{
        programiranje.postaviOpisnaOcenka(ime,opisna);
    }
    catch (BadInputException & be){
        be.message();
        programiranje.postaviOpisnaOcenka(ime,iscistiOcenka(opisna));
    }
}

StudentKurs::setMAX(9);

programiranje.pecatiStudenti();

}
