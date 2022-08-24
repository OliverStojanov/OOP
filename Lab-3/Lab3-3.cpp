#include<iostream>
#include<cstring>
using namespace std;

class Category{
    private:
        char name[20];
    public:
        Category(){
            strcpy(name,"unnamed");
        }
        Category(char * _name){
            strcpy(name,_name);
        }
        void print(){
            cout<<"Category: "<<name<<endl;
        }
};
class NewsArticle{
    private:
        Category kategorija;
        char title[30];
    public:
        NewsArticle(){
            strcpy(title,"untitled");
        }
        NewsArticle(Category k,char * _title="untitled"){
            kategorija=k;
            strcpy(title,_title);
        }
        void print(){
            cout<<"Article title: "<<title<<endl;
            kategorija.print();
        }
};


class FrontPage{
    private:
        NewsArticle naslovnaVest;
        float price;
        int editionNumber;
    public:
        FrontPage(){
            price=0;
            editionNumber=0;
        }
        FrontPage(NewsArticle _naslovnaVest,float _price=0, int _editionNumber=0){
            naslovnaVest=_naslovnaVest;
            price=_price;
            editionNumber=_editionNumber;
        }
        void print(){
            cout<<"Price: "<<price<<", Edition number: "<<editionNumber<<endl;
            naslovnaVest.print();
        }
};

int main() {
	char categoryName[20];
	char articleTitle[30];
	float price;
	int editionNumber;

	int testCase;
	cin >> testCase;


	if (testCase == 1) {
		int iter;
		cin >> iter;
		while (iter > 0) {
			cin >> categoryName;
			cin >> articleTitle;
			cin >> price;
			cin >> editionNumber;
			Category category(categoryName);
			NewsArticle article(category, articleTitle);
			FrontPage frontPage(article, price, editionNumber);
			frontPage.print();
			iter--;
		}
	}
	else if (testCase == 2) {
		cin >> categoryName;
		cin >> price;
		cin >> editionNumber;
		Category category(categoryName);
		NewsArticle article(category);
		FrontPage frontPage(article, price, editionNumber);
		frontPage.print();
	}// test case 3
	else if (testCase == 3) {
		cin >> categoryName;
		cin >> articleTitle;
		cin >> price;
		Category category(categoryName);
		NewsArticle article(category, articleTitle);
		FrontPage frontPage(article, price);
		frontPage.print();
	}
    else {
    	FrontPage frontPage = FrontPage();
        frontPage.print();
    }
	return 0;
}
