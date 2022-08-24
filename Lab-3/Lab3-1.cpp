#include<iostream>
#include<cstring>
using namespace std;

class Person{
    private:
        char name[20],lastName[20];
    public:
        Person(char * _name="not specified", char *_lastName="not specified"){
            strcpy(name,_name);
            strcpy(lastName,_lastName);
        }
        ~Person(){}
        void print(){
            cout<<name<<" "<<lastName<<endl;
        }
};
class Date{
    private:
        int year,month,day;
    public:
        Date(int y=1990,int m=1,int d=1){
            year=y;
            month=m;
            day=d;
        }
        Date(const Date &date){
            year=date.year;
            month=date.month;
            day=date.day;
        }
        void print(){
            cout<<year<<"."<<month<<"."<<day<<endl;
        }
};

class Car{
private:
    Person sopstvenik;
    Date datumKupuvanje;
    float cena;
public:
    Car(){
        cena = 0;
    }
    Car(Person p, Date d, float c){
        cena = c;
        sopstvenik = p;
        datumKupuvanje = d;
    }
    float getPrice(){
        return cena;
    }
    void print(){
        sopstvenik.print();
        datumKupuvanje.print();
        cout << "Price: " << cena;
    }
};

void cheaperThan(Car *cars, int numCars, float price)
{
    for(int i = 0; i < numCars; i++)
    {
        if(cars[i].getPrice() < price)
        {
            cars[i].print();
        }
    }
}

int main() {
	char name[20];
	char lastName[20];
	int year;
	int month;
	int day;
	float price;

	int testCase;
	cin >> testCase;

	if (testCase == 1) {
		cin >> name;
		cin >> lastName;
		Person lik(name, lastName);

		cin >> year;
		cin >> month;
		cin >> day;
		Date date(year, month, day);

		cin >> price;
		Car car(lik, date,  price);

		car.print();
	}
	else if (testCase == 2) {
		cin >> name;
		cin >> lastName;
		Person lik(name, lastName);

		cin >> year;
		cin >> month;
		cin >> day;
		Date date(Date(year, month, day));

		cin >> price;
		Car car(lik, date,  price);
		car.print();
	}
	else {
		int numCars;
		cin >> numCars;

		Car cars[10];
		for (int i = 0; i < numCars; i++) {
			cin >> name;
			cin >> lastName;
			Person lik(name, lastName);

			cin >> year;
			cin >> month;
			cin >> day;
			Date date(year, month, day);

			cin >> price;
			cars[i] = Car(lik, date,  price);
		}
        float priceLimit;
        cin >> priceLimit;
		cheaperThan(cars, numCars, priceLimit);
	}


	return 0;
}
