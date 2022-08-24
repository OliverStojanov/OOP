#include <iostream>
#include <cstring>
using namespace std;

class Employee{
    protected:
        char ime[50];
        int god, rabIskustvo;
        Employee(char * _ime="", int _god=0, int _rabIskustvo=0){
            strcpy(ime,_ime);
            god=_god;
            rabIskustvo=_rabIskustvo;
        }
    public:

        virtual double plata()=0;
        virtual double bonus()=0;
        bool operator==(const Employee &emp){
            if(god==emp.god){
                return true;
            }
            return false;
        }
        virtual int tip() = 0;
};
class SalaryEmployee : public Employee{
    private:
        int osnovnaPlata;
    public:
        SalaryEmployee(char * _ime="", int _god=0, int _rabIskustvo=0, int oPlata=0) : Employee(_ime,_god,_rabIskustvo){
            osnovnaPlata=oPlata;
        }
        double bonus(){
            return osnovnaPlata/100*rabIskustvo;
        }
        double plata(){
            return osnovnaPlata + bonus();
        }
        int tip(){
            return 1;
        }
};
class HourlyEmployee : public Employee{
    private:
        int vkCasovi,plataCas;
    public:
        HourlyEmployee(char * _ime="", int _god=0, int _rabIskustvo=0, int c=0, int pc=0) : Employee(_ime,_god,_rabIskustvo){
            vkCasovi=c;
            plataCas=pc;
        }
        double bonus(){
            if(vkCasovi>320){
                return (vkCasovi-320)*plataCas/2;
            }else return 0;
        }
        double plata(){
            return vkCasovi*plataCas + bonus();
        }
        int tip(){
            return 2;
        }
};

class Freelancer : public Employee{
    private:
        int brProekti;
        double * suma;
    public:
        Freelancer(char * _ime="", int _god=0, int _rabIskustvo=0, int p=0, double * _suma=0) : Employee(_ime,_god,_rabIskustvo){
            brProekti=p;
            suma=new double[brProekti];
            for(int i=0; i<brProekti; i++){
                suma[i]=_suma[i];
            }
        }
        double bonus(){
            if(brProekti>5){
                return (brProekti-5)*1000;
            }else return 0;
        }
        double plata(){
            int sum=0;
            for(int i=0; i<brProekti; i++){
                sum+=suma[i];
            }
            return sum + bonus();
        }
        int tip(){
            return 3;
        }
};
class Company{
    private:
        char imeKompanija[100];
        int vraboteni;
        Employee ** emp;
    public:
        Company(char * ime){
            strcpy(imeKompanija,ime);
            vraboteni=0;
            emp= new Employee*[0];
        }
        Company & operator+=(Employee * empl){
            Employee ** tmp=new Employee*[vraboteni+1];
            for(int i=0; i<vraboteni; i++){
                tmp[i]=emp[i];
            }
            delete [] emp;
            emp=tmp;
            emp[vraboteni]=empl;
            vraboteni++;
        }
        double vkupnaPlata(){
            double vkupno=0;
            for(int i=0; i<vraboteni; i++){
                vkupno+=emp[i]->plata();
            }
            return vkupno;
        }
        double filtriranaPlata(Employee * empl){
            double vkupno=0;
            for(int i=0; i<vraboteni; i++){
                if(*empl==*emp[i])
                vkupno+=emp[i]->plata();
            }
            return vkupno;
        }
        void pecatiRabotnici(){
            cout<<"Vo kompanijata "<<imeKompanija<<" rabotat:"<<endl;
            int sal = 0, hou = 0, fre = 0;
            for(int i = 0; i < vraboteni; i++){
                switch (emp[i]->tip())
                {
                    case 1:
                        sal++;
                        break;
                    case 2:
                        hou++;
                        break;
                    case 3:
                        fre++;
                        break;
                    default:
                        break;
                }
            }
            cout<< "Salary employees: " << sal << endl;
            cout<< "Hourly employees: " << hou << endl;
            cout<< "Freelancers: " << fre << endl;
        }
};

int main() {

char name[50];
cin >> name;
Company c(name);

int n;
cin >> n;

char employeeName[50];
int age;
int experience;
int type;

for (int i=0; i <n; ++i) {
  cin >> type;
  cin >> employeeName >> age >> experience;

  if (type == 1) {
    int basicSalary;
    cin >> basicSalary;
    c += new SalaryEmployee(employeeName, age, experience, basicSalary);
  }

  else if (type == 2) {
    int hoursWorked;
    int hourlyPay;
    cin >> hoursWorked >> hourlyPay;
    c += new HourlyEmployee(employeeName, age, experience, hoursWorked, hourlyPay);
  }

  else {
    int numProjects;
    cin >> numProjects;
    double projects[10];
    for (int i=0; i < numProjects; ++i) {
      cin >> projects[i];
    }
    c += new Freelancer(employeeName, age, experience, numProjects, projects);
  }
}

c.pecatiRabotnici();
cout << "Vkupnata plata e: " << c.vkupnaPlata() << endl;
Employee * emp = new HourlyEmployee("Petre_Petrov",31,6,340,80);
cout << "Filtriranata plata e: " << c.filtriranaPlata(emp);

delete emp;
}
