#include<iostream>
using namespace std;

class Number {
    public:
        virtual double doubleValue()=0;
        virtual int intValue()=0;
        virtual void print()=0;
};
bool operator==(Number &n,Number &m){
    return (n.doubleValue()==m.doubleValue() && n.intValue()==m.intValue());
}
class Integer : public Number{
    private:
         int n;
    public:
        Integer(int broj){
            n=broj;
        }
        double doubleValue(){
            return 0;
        }
        int intValue(){
            return n;
        }
        void print(){
            cout<<"Integer: "<<n<<endl;
        }
};

class Double : public Number{
    private:
         double n;
    public:
    Double(double broj){
            n=broj;
        }
        double doubleValue(){
            return n - (int)n;
        }
        int intValue(){
            return (int)n;
        }
        void print(){
            cout<<"Double: "<<n<<endl;
        }
};

class Numbers{
    private:
        Number ** br;
        int brElementi;
    public:
    Numbers(){
        br=new Number*[0];
        brElementi=0;
    }
    Numbers(const Numbers & n){
        brElementi=n.brElementi;
        br= new Number*[brElementi+1];
        br=n.br;
    }
    Numbers &operator=(Numbers & n){
        if(this!=&n){
            delete [] br;
            brElementi=n.brElementi;
            br= new Number*[brElementi+1];
            br=n.br;
        }
        return *this;
    }
    ~Numbers(){
        delete [] br;
    }
    Numbers & operator+=(Number *n){
        Number **tmp=new Number*[brElementi+1];
        for(int i=0; i<brElementi; i++){
            if(*br[i]==*n){
                delete [] tmp;
                return *this;
            }
            tmp[i]=br[i];
        }
        delete [] br;
        br=tmp;
        br[brElementi]=n;
        brElementi++;
        return *this;
    }
    double sumOfAll(){
        double sum=0;
        for(int i=0; i<brElementi; i++){
            sum+=br[i]->doubleValue() + br[i]->intValue();
        }
        return sum;
    }
    int intNum(){
        int c=0;
        for(int i=0; i<brElementi; i++){
            if(br[i]->doubleValue()==0){
                c++;
            }
        }
        return c;
    }
    int sumIntNum(){
        int c=0;
        for(int i=0; i<brElementi; i++){
            if(br[i]->doubleValue()==0){
                c+=br[i]->intValue();
            }
        }
        return c;
    }
    int doubleNum(){
        int c=0;
        for(int i=0; i<brElementi; i++){
            if(br[i]->doubleValue()!=0){
                c++;
            }
        }
        return c;
    }
    double sumDoubleNum(){
        double c=0;
        for(int i=0; i<brElementi; i++){
            if(br[i]->doubleValue()!=0){
                c+=br[i]->doubleValue()+br[i]->intValue();
            }
        }
        return c;
    }
    void statistics(){
        cout<<"Count of numbers: "<<brElementi<<endl;
        cout<<"Sum of all numbers: "<<sumOfAll()<<endl;
        cout<<"Count of integer numbers: "<<intNum()<<endl;
        cout<<"Sum of integer numbers: "<<sumIntNum()<<endl;
        cout<<"Count of double numbers: "<<doubleNum()<<endl;
        cout<<"Sum of double numbers: "<<sumDoubleNum()<<endl;
    }

    void integersLessThan (Integer n){
        int c=0;
        for(int i=0; i<brElementi; i++){
            if(br[i]->intValue()<n.intValue() && br[i]->doubleValue()==0){
                br[i]->print();
                c++;
            }
        }
        if(c==0){
            cout<<"None"<<endl;
        }
    }

    void doublesBiggerThan (Double n){
        int c=0;
        for(int i=0; i<brElementi; i++){
            if(br[i]->intValue()+br[i]->doubleValue()>n.intValue()+n.doubleValue()&&br[i]->doubleValue() != 0){
                br[i]->print();
                c++;
            }
        }
        if(c==0){
            cout<<"None"<<endl;
        }
    }
};

int main() {

	int n;
	cin>>n;
	Numbers numbers;
	for (int i=0;i<n;i++){
		int type;
		double number;
		cin>>type>>number;
		if (type==0){//Integer object
			Integer * integer = new Integer((int) number);
			numbers+=integer;
		}
		else {
			Double * doublee = new Double(number);
			numbers+=doublee;
		}
	}

	int lessThan;
	double biggerThan;

	cin>>lessThan;
	cin>>biggerThan;

	cout<<"STATISTICS FOR THE NUMBERS\n";
	numbers.statistics();
	cout<<"INTEGER NUMBERS LESS THAN "<<lessThan<<endl;
	numbers.integersLessThan(Integer(lessThan));
	cout<<"DOUBLE NUMBERS BIGGER THAN "<<biggerThan<<endl;
	numbers.doublesBiggerThan(Double(biggerThan));

	return 0;
}
