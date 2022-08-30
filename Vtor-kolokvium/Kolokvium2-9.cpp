#include <iostream>
#include <cstring>
using namespace std;

class Exception{
    public:
        void poraka(){
            cout<<"Ne moze da se vnese dadeniot trud"<<endl;
        }
};

class IndeksException{
    private:
        int ind;
    public:
        IndeksException(int i){
            ind=i;
        }
        void poraka(){
            cout<<"Ne postoi PhD student so indeks "<<ind<<endl;
        }
};

class Trud{
    private:
        char vidTrud;
        int godIzdavanje;
    public:
        Trud(const char vt='0', int gi=1900){
            godIzdavanje=gi;
            vidTrud=vt;
        }
        char getVid() const{
            return vidTrud;
        }
        int getGodIzdavanje()const{
            return godIzdavanje;
        }
        friend istream & operator>>(istream &in, Trud & t){
            return in>>t.vidTrud>>t.godIzdavanje;
        }
};

class Student{
    private:
        char ime[30];
        int indeks, godUpis;
        int *polozeniPredmeti, brPolozeni;
    public:
        Student(char *i="", int _indeks=0, int gu=2000, int *pp=0, int br=0){
            strcpy(ime,i);
            indeks=_indeks;
            godUpis=gu;
            brPolozeni=br;
            polozeniPredmeti = new int[br];
            for(int i=0; i<br; i++){
                polozeniPredmeti[i]=pp[i];
            }
        }
        ~Student(){
            delete [] polozeniPredmeti;
        }
        int getIndeks(){
            return indeks;
        }
        int getGodUpis(){
            return godUpis;
        }
        virtual double rang(){
            double vkupno=0;
            for(int i=0; i<brPolozeni; i++){
                vkupno+=polozeniPredmeti[i];
            }
            return vkupno/brPolozeni;
        }
        friend ostream &operator<<(ostream & out, Student & s){
            return out<<s.indeks<<" "<<s.ime<<" "<<s.godUpis<<" "<<s.rang()<<endl;
        }
};
class PhDStudent : public Student{
    private:
        Trud * trudovi;
        int brTrudovi;
        static int konf,spisanie;
    public:
        PhDStudent(char *i="", int _indeks=0, int gu=2000, int *pp=0, int br=0, Trud * _trudovi=0, int brt=0) : Student (i,_indeks,gu,pp,br){
            brTrudovi=brt;
            trudovi=new Trud[brt];
            if(brt > 0){
                for(int i = 0; i < brt; i++){
                    //trudovi[i] = t[i];
                    try{
                        *this += _trudovi[i];
                    }
                    catch(Exception &e){
                        e.poraka();
                    }
                }
            }
        }
        static int setKonf(int n){
            konf=n;
        }
        static int setSpisanie(int n){
            spisanie=n;
        }
        double rang(){
            int c=0, j=0;
            for(int i=0; i<brTrudovi; i++){
                if(toupper(trudovi[i].getVid())=='C'){
                    c++;
                }else if(toupper(trudovi[i].getVid())=='J'){
                    j++;
                }
            }
            return Student::rang()+c*konf+j*spisanie;
        }
        PhDStudent & operator+=(Trud &t){
            if(t.getGodIzdavanje()<this->getGodUpis()){
                throw Exception();
            }else{
                Trud * tmp= new Trud [brTrudovi+1];
                for(int i=0; i<brTrudovi; i++){
                    tmp[i]=trudovi[i];
                }
                delete [] trudovi;
                trudovi=tmp;
                trudovi[brTrudovi]=t;
                brTrudovi++;
                return *this;
            }
        }
};
PhDStudent* getStudentPok(Student **studenti, int n, int ind)
{
    for(int i = 0; i < n; i++)
    {
        if(studenti[i]->getIndeks() == ind)
        {
            PhDStudent *temp = dynamic_cast<PhDStudent*> (studenti[i]);
            if(temp)
            {
                return temp;
            }
        }
    }
    throw IndeksException(ind);
}
int PhDStudent::konf=1;
int PhDStudent::spisanie=3;

int main(){
	int testCase;
	cin >> testCase;

	int god, indeks, n, god_tr, m, n_tr;
	int izbor; //0 za Student, 1 za PhDStudent
	char ime[30];
	int oceni[50];
	char tip;
	Trud trud[50];

	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		Student s(ime, indeks, god, oceni, n);
		cout << s;

		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		cin >> n_tr;
		for (int j = 0; j < n_tr; j++){
			cin >> tip;
			cin >> god_tr;
			Trud t(tip, god_tr);
			trud[j] = t;
		}
		PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
		cout << phd;
	}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;
        try{
            *(getStudentPok(niza, n, indeks))+=t;
        }
        catch (Exception &e){
            e.poraka();
        }
        catch(IndeksException &ie){
            ie.poraka();
        }
		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 3){
		cout << "===== Testiranje na operatorot += ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;

        try{
            *(getStudentPok(niza, n, indeks))+=t;
        }
        catch (Exception &e){
            e.poraka();
        }
        catch(IndeksException &ie){
            ie.poraka();
        }
		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2


		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 4){
		cout << "===== Testiranje na isklucoci ======" << endl;
		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		cin >> n_tr;
		for (int j = 0; j < n_tr; j++){
			cin >> tip;
			cin >> god_tr;
			Trud t(tip, god_tr);
			trud[j] = t;
		}
		PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
		cout << phd;
	}
	if (testCase == 5){
		cout << "===== Testiranje na isklucoci ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;
        try{
            *(getStudentPok(niza, n, indeks))+=t;
        }
        catch (Exception &e){
            e.poraka();
        }
        catch(IndeksException &ie){
            ie.poraka();
        }
		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 6){
		cout << "===== Testiranje na static clenovi ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		int conf, journal;
		cin >> conf;
		cin >> journal;

		PhDStudent::setKonf(conf);
        PhDStudent::setSpisanie(journal);
        //postavete gi soodvetnite vrednosti za statickite promenlivi

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}

	return 0;
}
