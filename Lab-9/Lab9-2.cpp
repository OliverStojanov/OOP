#include <iostream>
#include <cstring>
using namespace std;

class ArithmeticException{
    public:
        void message(){
            cout<<"Division by zero is not allowed"<<endl;
        }
};
class NumbersNotDivisibleException{
    private:
        int num;
    public:
        NumbersNotDivisibleException(int n){
            num=n;
        }
        void message(){
            cout<<"Division by "<<num<<" is not supported"<<endl;
        }
};
class ArrayFullException{
    public:
        void message(){
            cout<<"The array is full. Increase the capacity"<<endl;
        }
};
class IndexOutOfBoundsException{
    private:
        int num;
    public:
        IndexOutOfBoundsException(int n){
            num=n;
        }
        void message(){
            cout<<"Index "<<num<<" is out of bounds"<<endl;
        }
};
class NumberIsNotPositiveException{
    private:
        int num;
    public:
        NumberIsNotPositiveException(int n){
            num=n;
        }
        void message(){
            cout<<"Number "<<num<<" is not positive integer"<<endl;
        }
};

class PositiveIntegers{
    private:
        int *nizaBr;
        int brEl, kapacitet;
    public:
        PositiveIntegers(int Kap=0){
            kapacitet=Kap;
            nizaBr= new int[0];
            brEl=0;
        }
        PositiveIntegers(const PositiveIntegers &pi){
            kapacitet=pi.kapacitet;
            brEl=pi.brEl;
            nizaBr= new int[brEl];
            for(int i=0; i<brEl; i++){
                nizaBr[i]=pi.nizaBr[i];
            }
        }
        ~PositiveIntegers(){
            delete [] nizaBr;
        }
        void increaseCapacity(int c){
            kapacitet+=c;
        }
        PositiveIntegers & operator=(const PositiveIntegers & pi){
            if(this!=&pi){
                delete [] nizaBr;
                kapacitet=pi.kapacitet;
                brEl=pi.brEl;
                nizaBr= new int[brEl];
                for(int i=0; i<brEl; i++){
                    nizaBr[i]=pi.nizaBr[i];
                }
            }
            return *this;
        }
        PositiveIntegers &operator+=(int n){
            if(brEl+1<=kapacitet){
                if(n>0){
                    int *tmp = new int[brEl+1];
                    for(int i=0;i<brEl;i++){
                        tmp[i]=nizaBr[i];
                    }
                    delete [] nizaBr;
                    nizaBr=tmp;
                    nizaBr[brEl]=n;
                    brEl++;
                }
                else{
                    throw NumberIsNotPositiveException(n);
                }
            }else{
                throw ArrayFullException();
            }
            return *this;
        }
        PositiveIntegers operator*(int n){
            PositiveIntegers tmp = *this;
            for(int i=0; i<brEl; i++){
                tmp.nizaBr[i]*=n;
            }
            return tmp;
        }
        PositiveIntegers operator/(int n){
            if(n!=0){
                PositiveIntegers tmp = *this;
                for(int i=0; i<brEl; i++){
                    if(nizaBr[i]%n!=0){
                        throw NumbersNotDivisibleException(n);
                    }else{
                        tmp.nizaBr[i]/=n;
                    }
                }
                return tmp;
            }else{
                throw ArithmeticException();
            }
        }
        int &operator[](int n){
            if(n<0||n>=brEl){
                throw IndexOutOfBoundsException(n);
            }else{
                return nizaBr[n];
            }
        }
        void print(){
            cout<<"Size: "<<brEl<<" Capacity: "<<kapacitet<<" Numbers: ";
            for(int i=0; i<brEl; i++){
                cout<<nizaBr[i]<<" ";
            }
            cout<<endl;
        }
};

int main() {

	int n,capacity;
	cin >> n >> capacity;
	PositiveIntegers pi (capacity);
	for (int i=0;i<n;i++){
		int number;
		cin>>number;
		try{
		    pi+=number;
		}
		catch (ArrayFullException &polno){
            polno.message();
        }
        catch (NumberIsNotPositiveException &nepoz){
            nepoz.message();
        }
	}
	cout<<"===FIRST ATTEMPT TO ADD NUMBERS==="<<endl;
	pi.print();
	int incCapacity;
	cin>>incCapacity;
	pi.increaseCapacity(incCapacity);
	cout<<"===INCREASING CAPACITY==="<<endl;
	pi.print();

	int n1;
	cin>>n1;
	for (int i=0;i<n1;i++){
		int number;
		cin>>number;
		try{
		    pi+=number;
		}
		catch (ArrayFullException &polno){
            polno.message();
        }
        catch (NumberIsNotPositiveException &nepoz){
            nepoz.message();
        }
	}
	cout<<"===SECOND ATTEMPT TO ADD NUMBERS==="<<endl;

    pi.print();
	PositiveIntegers pi1;

	cout<<"===TESTING DIVISION==="<<endl;
	try{
    	pi1 = pi/0;
	    pi1.print();
	}
	catch(NumbersNotDivisibleException &nedeli){
        nedeli.message();
    }
    catch(ArithmeticException &arit){
        arit.message();
    }
	try{
	pi1 = pi/1;
	pi1.print();
	}
	catch(NumbersNotDivisibleException &nedeli){
        nedeli.message();
    }
    catch(ArithmeticException &arit){
        arit.message();
    }
	try{
	pi1 = pi/2;
	pi1.print();
    }
    catch(NumbersNotDivisibleException &nedeli){
        nedeli.message();
    }
    catch(ArithmeticException &arit){
        arit.message();
    }
	cout<<"===TESTING MULTIPLICATION==="<<endl;
	pi1 = pi*3;
	pi1.print();
	cout<<"===TESTING [] ==="<<endl;
	try{
        cout<<"PositiveIntegers[-1] = "<<pi[-1]<<endl;
    }
    catch(IndexOutOfBoundsException &indeks){
        indeks.message();
    }
    try{
        cout<<"PositiveIntegers[2] = "<<pi[2]<<endl;
    }
    catch(IndexOutOfBoundsException &indeks){
        indeks.message();
    }
    try{
        cout<<"PositiveIntegers[3] = "<<pi[3]<<endl;
    }
    catch(IndexOutOfBoundsException &indeks){
        indeks.message();
    }
    try{
        cout<<"PositiveIntegers[12] = "<<pi[12]<<endl;
    }
    catch(IndexOutOfBoundsException &indeks){
        indeks.message();
    }
	return 0;
}
