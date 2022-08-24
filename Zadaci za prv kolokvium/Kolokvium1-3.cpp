#include<iostream>
#include<cstring>
using namespace std;
class StockRecord{
    private:
        char id[12], ime[50];
        double cenaKupeni, momentalnaCena;
        int brAkcii;
    public:
        StockRecord(char * _id="", char *_ime="", double ck=0, int ba=0, double mc=0){
            strcpy(id,_id);
            strcpy(ime,_ime);
            cenaKupeni=ck;
            momentalnaCena=mc;
            brAkcii=ba;
        }
        StockRecord(const StockRecord &sr){
            strcpy(id,sr.id);
            strcpy(ime,sr.ime);
            cenaKupeni=sr.cenaKupeni;
            momentalnaCena=sr.momentalnaCena;
            brAkcii=sr.brAkcii;
        }
        ~StockRecord(){}
        void setNewPrice(double c){
            momentalnaCena=c;
        }
        double Value(){
            return brAkcii*momentalnaCena;
        }
        double Profit(){
            return brAkcii*(momentalnaCena-cenaKupeni);
        }
        friend ostream & operator<<(ostream &out,StockRecord & sr){
            return out<<sr.ime<<" "<<sr.brAkcii<<" "<<sr.cenaKupeni<<" "<<sr.momentalnaCena<<" "<<sr.Profit()<<endl;
        }
};
class Client{
    private:
        char ime[60];
        int id;
        StockRecord * sr;
        int brObjekti;
    public:
        Client(char * _ime="", int _id=0, StockRecord s[]=0, int brO=0){
            strcpy(ime,_ime);
            id=_id;
            sr=new StockRecord[0];
            brObjekti=brO;
            for(int i=0; i<brO; i++){
                sr[i]=s[i];
            }
        }
        Client(const Client &c){
            strcpy(ime,c.ime);
            id=c.id;
            sr=new StockRecord[0];
            brObjekti=c.brObjekti;
            for(int i=0; i<c.brObjekti; i++){
                sr[i]=c.sr[i];
            }
        }
        ~Client(){
            delete [] sr;
        }
        double totalValue(){
            double tv=0;
            for(int i=0; i<brObjekti; i++){
                tv+=sr[i].Value();
            }
            return tv;
        }
        Client &operator+=(const StockRecord & str){
            StockRecord *tmp=new StockRecord[brObjekti+1];
            for(int i=0; i<brObjekti; i++){
                tmp[i]=sr[i];
            }
            delete [] sr;
            sr=tmp;
            sr[brObjekti]=str;
            brObjekti++;
            return *this;
        }
        friend ostream & operator<<(ostream & out, Client &c){
            out<<c.id<<" "<<c.totalValue()<<endl;
            for(int i=0; i<c.brObjekti; i++){
                out<<c.sr[i];
            }
            return out;
        }
};


int main(){

    int test;
    cin >> test;

    if(test == 1){
    	double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
    	char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
        	cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.Value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
    	cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
        	StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
            	cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}
