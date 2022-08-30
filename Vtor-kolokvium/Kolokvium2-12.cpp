#include <iostream>
#include <cstring>

using namespace std;
enum tip{ smartphone , computer };

class InvalidProductionDate{
    public:
        InvalidProductionDate(){}
        void message(){
            cout<<"Невалидна година на производство"<<endl;
        }
};

class Device{
    private:
        char model[100];
        tip tipp;
        static double potrebniCasovi;
        int godProizvodstvo;
    public:
        Device(char *m="",tip t=smartphone,int gp=0){
            strcpy(model,m);
            tipp=t;
            godProizvodstvo=gp;
        }
        static void setPocetniCasovi(double pc){
            potrebniCasovi=pc;
        }
        double vremeProverka(){
            double dopolnitelno=0;
            if(godProizvodstvo>2015){
                dopolnitelno += 2;
            }
            if(tipp==1){
                dopolnitelno += 2;
            }
            return dopolnitelno;
        }
        friend ostream & operator<<(ostream & out, Device & d){
            out<<d.model<<endl;
            if(d.tipp==0){
                out<<"Mobilen ";
            }else{
                out<<"Laptop ";
            }
            out<<d.potrebniCasovi+d.vremeProverka()<<endl;
        }
        int getGod() const{
            return godProizvodstvo;
        }
};

class MobileServis{
    private:
        char adresa[100];
        Device * uredi;
        int brUredi;
    public:
        MobileServis(char * a=""){
            strcpy(adresa,a);
            uredi= new Device[0];
            brUredi=0;
        }
        MobileServis(const MobileServis &ms){
            brUredi=ms.brUredi;
            uredi=new Device[brUredi];
            for(int i=0; i<brUredi; i++){
                uredi[i]=ms.uredi[i];
            }
            strcpy(adresa,ms.adresa);
        }
        MobileServis &operator+=(const Device & d){
            if(d.getGod()>2019 || d.getGod()<2000){
                throw InvalidProductionDate();
            }else{
                Device *tmp = new Device[brUredi+1];
                for(int i=0; i<brUredi; i++){
                    tmp[i]=uredi[i];
                }
                delete [] uredi;
                uredi=tmp;
                uredi[brUredi]=d;
                brUredi++;
                return *this;
            }
        }
        void pecatiCasovi(){
            cout<<"Ime: "<<adresa<<endl;
            for(int i=0; i<brUredi; i++){
                cout<<uredi[i];
            }
        }
};

double Device::potrebniCasovi = 1;

int main()
{
	int testCase;
	cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> tipDevice;
		cin >> godina;
		Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
		MobileServis t(ime);
        cout<<ig;
		}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &ipd){
                ipd.message();
            }
        }
        t.pecatiCasovi();
	}
	if (testCase == 3){
		cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &ipd){
                ipd.message();
            }
        }
        t.pecatiCasovi();
	}
	if (testCase == 4){
		cout <<"===== Testiranje na konstruktori ======"<<endl;
		 cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &ipd){
                ipd.message();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}
	if (testCase == 5){
		cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &ipd){
                ipd.message();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
		Device::setPocetniCasovi(2);
        t.pecatiCasovi();
	}

		if (testCase == 6){
		cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
		cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &ipd){
                ipd.message();
            }
        }
		Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}

	return 0;

}

