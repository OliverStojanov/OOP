#include <iostream>
#include <cstring>
using namespace std;
#define MAX 100
enum typeC{ standardni , lojalni , vip};
class UserExistsException{
    public:
        UserExistsException(){}
        void print(){
            cout<<"The user already exists in the list!"<<endl;
        }
};
class Customer{
    protected:
        char ime[50],eAdresa[50];
        typeC tip;
        static int popust;
        static const int dopPopust=20;
        int kupeniProizvodi;
    public:
        Customer(const char * i="", const char * a="", typeC t=(typeC)0, int kp=0){
            strcpy(ime,i);
            strcpy(eAdresa,a);
            tip=t;
            kupeniProizvodi=kp;
        }
        friend ostream &operator<<(ostream &out, Customer & c){
            out<<c.ime<<endl<<c.eAdresa<<endl<<c.kupeniProizvodi<<endl;
            if(c.tip==0){
                out<<"standard "<<0<<endl;
            }else if(c.tip==1){
                out<<"loyal "<<c.popust<<endl;
            }else if(c.tip==2){
                out<<"vip "<<c.popust+c.dopPopust<<endl;
            }
            return out;
        }
        char * getEAdresa(){
            return eAdresa;
        }
        void setDiscount1(int n){
            popust=n;
        }
        int getKupeniProizvodi(){
            return kupeniProizvodi;
        }
        typeC getTip(){
            return tip;
        }
        void setTip(typeC n){
            tip=n;
        }
};

class FINKI_bookstore{
    private:
        Customer * kupuvaci;
        int brKupuvaci;
    public:
        FINKI_bookstore(){}
        FINKI_bookstore(Customer * c, int br){
            kupuvaci= new Customer[br];
            brKupuvaci=br;
            for(int i=0; i<br; i++){
                kupuvaci[i]=c[i];
            }
        }
        ~FINKI_bookstore(){
            delete [] kupuvaci;
        }
        void setCustomers(Customer * c, int br){
            delete [] kupuvaci;
            kupuvaci= new Customer[br];
            brKupuvaci=br;
            for(int i=0; i<br; i++){
                kupuvaci[i]=c[i];
            }
        }
        FINKI_bookstore &operator+=(Customer & c){
            Customer *tmp = new Customer[brKupuvaci+1];
            for(int i=0; i<brKupuvaci; i++){
                if(!strcmp(kupuvaci[i].getEAdresa(),c.getEAdresa())){
                    throw UserExistsException();
                }
            }
            for(int i=0; i<brKupuvaci; i++){
                tmp[i]=kupuvaci[i];
            }
            delete [] kupuvaci;
            kupuvaci = tmp;
            kupuvaci[brKupuvaci]=c;
            brKupuvaci++;
            return *this;
        }
        void update(){
            for(int i=0; i<brKupuvaci; i++){
                if(kupuvaci[i].getTip()==standardni && kupuvaci[i].getKupeniProizvodi()>5){
                    kupuvaci[i].setTip(lojalni);
                }else if(kupuvaci[i].getTip()==lojalni && kupuvaci[i].getKupeniProizvodi()>10){
                    kupuvaci[i].setTip(vip);
                }

            }
        }
        friend ostream & operator<<(ostream &out, FINKI_bookstore &bs){
            for(int i=0; i<bs.brKupuvaci; i++){
                out<<bs.kupuvaci[i];
            }
            return out;
        }
};

int Customer::popust = 10;

int main(){
  int testCase;
  cin >> testCase;

  char name[MAX];
  char email[MAX];
  int tC;
  int discount;
  int numProducts;


  if (testCase == 1){
    cout << "===== Test Case - Customer Class ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

  }

  if (testCase == 2){
    cout << "===== Test Case - Static Members ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

    c.setDiscount1(5);

    cout << c;
  }

  if (testCase == 3){
    cout << "===== Test Case - FINKI-bookstore ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << fc <<endl;
  }

  if (testCase == 4){
    cout << "===== Test Case - operator+= ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (typeC) tC, numProducts);
    fc+=c;

    cout << fc;
  }

  if (testCase == 5){
    cout << "===== Test Case - operator+= (exception) ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer kk;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
      kk=c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    try{
        fc+=kk;
    }
    catch(UserExistsException &user){
        user.print();
    }

    cout << fc;
  }

  if (testCase == 6){
    cout << "===== Test Case - update method  ======" << endl << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << "Update:" << endl;
    fc.update();
    cout << fc;
  }
  return 0;

}
