#include <iostream>
#include <cstring>
using namespace std;

class Book{
    protected:
        char ISBN[21], naslov[51], avtor[31];
        double cena;
    public:
        Book(char *i="", char * n="", char * a="", double c=0){
            strcpy(ISBN,i);
            strcpy(naslov,n);
            strcpy(avtor,a);
            cena=c;
        }
        virtual double bookPrice() = 0;
        void *setISBN(char *i){
            strcpy(ISBN,i);
        }
        bool operator>(Book &b){
            return bookPrice()>b.bookPrice();
        }
        friend ostream & operator<<(ostream &out, Book & bb){
            return out<<bb.ISBN<<": "<<bb.naslov<<", "<<bb.avtor<<" "<<bb.bookPrice()<<endl;
        }
};

class OnlineBook : public Book{
    private:
        char *URL;
        int golemina;
    public:
        OnlineBook(char *i="", char * n="", char * a="", double c=0, char *u="", int g=0) : Book(i,n,a,c){
            URL= new char[strlen(u)+1];
            strcpy(URL,u);
            golemina=g;
        }
        OnlineBook(const OnlineBook &ob){
            strcpy(ISBN,ob.ISBN);
            strcpy(naslov,ob.naslov);
            strcpy(avtor,ob.avtor);
            cena=ob.cena;
            URL= new char[strlen(ob.URL)+1];
            strcpy(URL,ob.URL);
            golemina=ob.golemina;
        }
        OnlineBook & operator=(const OnlineBook &ob){
            if(this!=&ob){
                delete [] URL;
                strcpy(ISBN,ob.ISBN);
                strcpy(naslov,ob.naslov);
                strcpy(avtor,ob.avtor);
                cena=ob.cena;
                URL= new char[strlen(ob.URL)+1];
                strcpy(URL,ob.URL);
                golemina=ob.golemina;
            }return *this;
        }
        double bookPrice(){
            if(golemina>20){
                return cena*1.2;
            }else return cena;
        }

};

class PrintBook : public Book{
    private:
        double masa;
        bool zaliha;
    public:
        PrintBook(char *i="", char * n="", char * a="", double c=0, double m=0, bool z=false) : Book(i,n,a,c){
            masa=m;
            zaliha=z;
        }
        double bookPrice(){
            if(masa>0.7){
                return cena*1.15;
            }return cena;
        }
};
void mostExpensiveBook (Book** books, int n){
    int max=0;
    int brOnline=0,brPrint=0;
    for(int i=0; i<n; i++){
            OnlineBook *tmp= dynamic_cast<OnlineBook*>(books[i]);
            if(tmp!=0){
                brOnline++;
            }else{
                brPrint++;
            }
            if(*books[i]>*books[max]){
                max=i;
            }
    }
    cout << "FINKI-Education"<<endl;
    cout << "Total number of online books: "<<brOnline << endl;
    cout << "Total number of print books: " <<brPrint << endl;
    cout<<"The most expensive book is:"<<endl;
    cout<<*books[max]<<endl;
}
int main(){

	char isbn[20], title[50], author[30], url[100];
	int size, tip;
	float price, weight;
	bool inStock;
	Book  **books;
	int n;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing OnlineBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> url;
			cin >> size;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new OnlineBook(isbn, title, author, price, url, size);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 2){
		cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
		cin >> isbn;
		cin.get();
		cin.getline(title, 50);
		cin.getline(author, 30);
		cin >> price;
		cin >> url;
		cin >> size;
		cout << "CONSTRUCTOR" << endl;
		OnlineBook ob1(isbn, title, author, price, url, size);
		cout << ob1 << endl;
		cout << "COPY CONSTRUCTOR" << endl;
		OnlineBook ob2(ob1);
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
		cout << "OPERATOR =" << endl;
		ob1 = ob2;
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
	}
	if (testCase == 3){
		cout << "====== Testing PrintBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> weight;
			cin >> inStock;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 4){
		cout << "====== Testing method mostExpensiveBook() ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i<n; i++){

			cin >> tip >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			if (tip == 1) {

				cin >> url;
				cin >> size;

				books[i] = new OnlineBook(isbn, title, author, price, url, size);

			}
			else {
				cin >> weight;
				cin >> inStock;

				books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			}
		}

		mostExpensiveBook(books, n);
	}

	for (int i = 0; i<n; i++) delete books[i];
		delete[] books;
	return 0;
}
