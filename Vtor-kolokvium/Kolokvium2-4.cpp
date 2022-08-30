#include <cstring>
#include <iostream>
using namespace std;
enum Size{ small, big , family};
class Pizza {
    protected:
        char ime[20],sostojki[100];
        double osnovnaCena;
    public:
        Pizza(const char * _ime="",const char * _sostojki="", double oc=0){
            strcpy(ime,_ime);
            strncpy(sostojki,_sostojki,49);
            osnovnaCena=oc;
        }
        virtual double price() = 0;
        bool operator<(Pizza & pi){
            return price()<pi.price();
        }

};
class FlatPizza : public Pizza{
    private:
        Size size;
    public:
        FlatPizza(const char * _ime="",const char * _sostojki="", double oc=0, Size s=(Size)0) : Pizza(_ime,_sostojki,oc){
            size=s;
        }
        double price(){
            if(size==0){
                return osnovnaCena*1.1;
            }else if(size==1){
                return osnovnaCena*1.3;
            }else if(size==2){
                return osnovnaCena*1.3;
            }
        }
        friend ostream & operator<<(ostream & out, FlatPizza & fp){
            out<<fp.ime<<": "<<fp.sostojki<<", ";
            if(fp.size==0){
                out<<"small";
            }else if(fp.size==1){
                out<<"big";
            }else if(fp.size==2){
                out<<"family";
            }
            out<<" - "<<fp.price()<<endl;
        }
};
class FoldedPizza : public Pizza{
    private:
        bool beloBrasno;
    public:
        FoldedPizza(const char * _ime="",const char * _sostojki="", double oc=0, bool bb=true) : Pizza(_ime,_sostojki,oc){
            beloBrasno=bb;
        }
        double price(){
            if(beloBrasno==true){
                return osnovnaCena*1.1;
            }return osnovnaCena*1.3;
        }
        void setWhiteFlour(bool b){
            beloBrasno=b;
        }
        friend ostream & operator<<(ostream & out, FoldedPizza & fp){
            return out<<fp.ime<<": "<<fp.sostojki<<", "<<(fp.beloBrasno ? "wf" : "nwf")<<" - "<<fp.price()<<endl;;

        }
};
void expensivePizza(Pizza **pica, int n){
    int najskapa=0;
    for(int i=1; i<n; i++){
        if(pica[i]->price()>pica[najskapa]->price()){
            najskapa=i;
        }
    }
    FlatPizza *tmp = dynamic_cast<FlatPizza*>(pica[najskapa]);
    if(tmp!=0){
        cout<<*tmp;
    }else{
        FoldedPizza *tmp1 = dynamic_cast<FoldedPizza*>(pica[najskapa]);
        cout<<*tmp1;
    }

}

int main() {
  int test_case;
  char name[20];
  char ingredients[100];
  float inPrice;
  Size size;
  bool whiteFlour;

  cin >> test_case;
  if (test_case == 1) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FlatPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 2) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    int s;
    cin>>s;
    FlatPizza fp(name, ingredients, inPrice, (Size)s);
    cout << fp;

  } else if (test_case == 3) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 4) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    fp.setWhiteFlour(false);
    cout << fp;

  } else if (test_case == 5) {
	// Test Cast - operator <, price
    int s;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp1;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp2;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
    cout << *fp3;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
    fp4->setWhiteFlour(false);
    cout << *fp4;

    cout<<"Lower price: "<<endl;
    if(*fp1<*fp2)
        cout<<fp1->price()<<endl;
    else cout<<fp2->price()<<endl;

    if(*fp1<*fp3)
        cout<<fp1->price()<<endl;
    else cout<<fp3->price()<<endl;

    if(*fp4<*fp2)
        cout<<fp4->price()<<endl;
    else cout<<fp2->price()<<endl;

    if(*fp3<*fp4)
        cout<<fp3->price()<<endl;
    else cout<<fp4->price()<<endl;

  } else if (test_case == 6) {
	// Test Cast - expensivePizza
    int num_p;
    int pizza_type;

    cin >> num_p;
    Pizza **pi = new Pizza *[num_p];
    for (int j = 0; j < num_p; ++j) {

      cin >> pizza_type;
      if (pizza_type == 1) {
        cin.get();
        cin.getline(name,20);

        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << (*fp);
        pi[j] = fp;
      }
      if (pizza_type == 2) {

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp =
            new FoldedPizza (name, ingredients, inPrice);
        if(j%2)
          (*fp).setWhiteFlour(false);
        cout << (*fp);
        pi[j] = fp;

      }
    }

    cout << endl;
    cout << "The most expensive pizza:\n";
    expensivePizza(pi,num_p);


  }
  return 0;
}
