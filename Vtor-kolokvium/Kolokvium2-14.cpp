#include <iostream>
#include <cstring>
using namespace std;

class SMS{
    protected:
        char broj[13];
        double oCena;
    public:
        SMS(char * br="", double oc=0){
            strcpy(broj,br);
            oCena=oc;
        }
        virtual double SMS_cena()=0;
        friend ostream &operator<<(ostream &o, SMS &s){
            return o << "Tel: " << s.broj << " - cena: " << s.SMS_cena() << "den." << endl;
        }
};
class RegularSMS : public SMS{
    private:
        char * text;
        bool roaming;
        static double r;
    public:
        RegularSMS(char * br="", double oc=0, char * txt="", bool roam=false) : SMS(br,oc){
            text = new char[strlen(txt)+1];
            strcpy(text,txt);
            roaming=roam;
        }
        double SMS_cena(){
            double c = oCena;
            if(roaming){
                c *= r + 1;
            }else{
                c *= 1.18;
            }
            c +=  (strlen(text)% 160 > 0 || (strlen(text) / 160) > 1 ? (strlen(text) / 160) * c : 0);
            return c;
        }
        static void set_rProcent(double d){
            r = d / 100;
        }
};

class SpecialSMS : public SMS{
    private:
        bool humanitarna;
        static double s;
    public:
        SpecialSMS(char * br="", double oc=0, bool human=false) : SMS(br,oc){
            humanitarna=human;
        }
        double SMS_cena(){
            double c = oCena;
            if(!humanitarna){
                c *= s + 1;
            }
            return c;
        }
        static void set_sProcent(double d){
            s = d / 100;
        }
};
void vkupno_SMS(SMS** poraka, int n){
    int specijalni=0, regularni=0;
    double specVk=0, regVk=0;
    for(int i=0; i<n; i++){
        RegularSMS *tmp = dynamic_cast <RegularSMS*> (poraka[i]);
        if(tmp!=0){
            regularni++;
            regVk+=poraka[i]->SMS_cena();
        }else{
            specijalni++;
            specVk+=poraka[i]->SMS_cena();
        }
    }
    cout << "Vkupno ima " << regularni << " regularni SMS poraki i nivnata cena e: " << regVk << endl;
    cout << "Vkupno ima " << specijalni << " specijalni SMS poraki i nivnata cena e: " << specVk << endl;

}


double SpecialSMS::s =1.5;
double RegularSMS::r = 3;
int main(){

	char tel[20], msg[1000];
	float cena;
	float price;
    int p;
	bool roam, hum;
	SMS  **sms;
	int n;
	int tip;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing RegularSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new RegularSMS(tel, cena, msg, roam);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 2){
		cout << "====== Testing SpecialSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
			cin >> hum;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new SpecialSMS(tel, cena, hum);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 3){
		cout << "====== Testing method vkupno_SMS() ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i<n; i++){

			cin >> tip;
			cin >> tel;
			cin >> cena;
			if (tip == 1) {

				cin.get();
				cin.getline(msg, 1000);
                cin >> roam;

				sms[i] = new RegularSMS(tel, cena, msg, roam);

			}
			else {
				cin >> hum;

				sms[i] = new SpecialSMS(tel, cena, hum);
			}
		}

		vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
    if (testCase == 4){
		cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        	cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			sms1 = new RegularSMS(tel, cena, msg, roam);
			cout << *sms1;

            cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
        	cin >> p;
        	RegularSMS::set_rProcent(p);
        	sms2 = new RegularSMS(tel, cena, msg, roam);
        	cout << *sms2;

        delete sms1, sms2;
	}
    if (testCase == 5){
		cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        	cin >> tel;
			cin >> cena;
			cin >> hum;
			sms1 = new SpecialSMS(tel, cena, hum);
			cout << *sms1;

            cin >> tel;
			cin >> cena;
			cin >> hum;
        	cin >> p;
        	SpecialSMS::set_sProcent(p);
        	sms2 = new SpecialSMS(tel, cena, hum);
        	cout << *sms2;

        delete sms1, sms2;
	}

	return 0;
}
