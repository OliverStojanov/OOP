#include<iostream>
#include<cmath>
using namespace std;

class ComplexNumber{
    private:
        double real,imaginary;
    public:
        ComplexNumber(double _real=0, double _imaginary=0){
            real=_real;
            imaginary=_imaginary;
        }
        double module(){
            return sqrt(pow(real,2)+pow(imaginary,2));
        }
        ComplexNumber & operator=(const ComplexNumber & cn){
            if(this!=&cn){
                real=cn.real;
                imaginary=cn.imaginary;
            }
            return *this;
        }
        friend ostream & operator<<(ostream & out, const ComplexNumber & cn){
            if(cn.real==0){
                out<<cn.imaginary<<"i"<<endl;
            }else if(cn.imaginary==0){
                out<<cn.real<<endl;
            }else
            out<<cn.real<<"+"<<cn.imaginary<<"i"<<endl;
        }
        ComplexNumber operator+(const ComplexNumber & cn){
            return ComplexNumber(real + cn.real, imaginary + cn.imaginary);
        }
        ComplexNumber operator-(const ComplexNumber & cn){
            return ComplexNumber(real - cn.real, imaginary - cn.imaginary);
        }
        ComplexNumber operator*(const ComplexNumber & cn){
            return ComplexNumber(real * cn.real, imaginary * cn.imaginary);
        }
        ComplexNumber operator/(const ComplexNumber & cn){
            if(cn.real!=0 && cn.imaginary!=0){
                return ComplexNumber(real / cn.real, imaginary / cn.imaginary);
            }
        }
        bool operator==(ComplexNumber & cn){
            if(real==cn.real){
                if(imaginary==cn.imaginary){
                    return true;
                }
            }
            return false;
        }
        bool operator>(const ComplexNumber &cn){
            if(real > cn.real){
            return true;
        }else if(cn.real > real){
            return false;
        }else if(real == cn.real){
            if(imaginary > cn.imaginary){
                return true;
            }
            else if(cn.imaginary > imaginary){
                return false;
            }
        }
    }

    bool operator<(const ComplexNumber &cn){
        if(real > cn.real){
            return false;
        }else if(cn.real > real){
            return true;
        }else if(real == cn.real){
            if(imaginary > cn.imaginary){
                return false;
            }else if(cn.imaginary > imaginary){
                return true;
            }
        }
    }
};
class Equation{
    private:
    ComplexNumber *kompleksni;
    char *operacii;
    int brK, brOp;
    public:
        Equation(){
            brK = brOp = 0;
            kompleksni = new ComplexNumber[0];
            operacii = new char[0];
        }
        Equation &operator+=(const ComplexNumber &cn){
            ComplexNumber *temp = new ComplexNumber[brK + 1];
            for(int k = 0; k < brK; k++){
                temp[k] = kompleksni[k];
            }
            delete [] kompleksni;
            kompleksni = temp;
            kompleksni[brK] = cn;
            brK++;
        }
        Equation &operator+=(const char &op){
            char *tempop = new char[brOp + 1];
            for(int k = 0; k < brOp; k++){
                tempop[k] = operacii[k];
            }
            delete [] operacii;
            operacii = tempop;
            operacii[brOp] = op;
            brOp++;
        }
        friend istream &operator>>(istream &in, Equation &eq){
            float r, im;
            char op = ' ';
            for(int i = 0; op != '='; i++){
                in >> r >> im;
                eq += ComplexNumber(r, im);
                in >> op;
                eq += op;
            }
            eq.brOp--;
            return in;
        }
        ComplexNumber result(){
            ComplexNumber res = kompleksni[0];
            ComplexNumber mRes;
            for(int i = 0, j = 1; i < brOp; i++, j++){
                switch (operacii[i]){
                    case '+':
                        res = kompleksni[j] + res;
                        break;
                    case '-':
                        res = res - kompleksni[j];
                        break;
                    case '*':
                        res = res * kompleksni[j];
                        break;
                    case '/':
                        res = res / kompleksni[j];
                        break;
                    default:
                        break;
                }
            }
            return res;
        }
        double sumModules(){
            double mod = 0;
            for(int i = 0; i < brK; i++){
                mod += kompleksni[i].module();
            }
        }
};
int main() {
	int testCase;
	double real, imaginary;
	ComplexNumber first, second, result;

	cin >> testCase;

	if (testCase <= 8) {
		cin >> real;
		cin >> imaginary;
		first = ComplexNumber(real, imaginary);
		cin >> real;
		cin >> imaginary;
		second = ComplexNumber(real, imaginary);
	}

	if (testCase == 1) {
		cout << "===== OPERATOR + =====" << endl;
		result = first + second;
		cout << result;
	}
	else if (testCase == 2) {
		cout << "===== OPERATOR - =====" << endl;
		result = first - second;
		cout << result;
	}
	else if (testCase == 3) {
		cout << "===== OPERATOR * =====" << endl;
		result = first * second;
		cout << result;
	}
	else if (testCase == 4) {
		cout << "===== OPERATOR / =====" << endl;
		result = first / second;
		cout << result;
	}
	else if (testCase == 5) {
		cout << "===== OPERATOR == =====" << endl;
		cout << first;
		cout << second;
		if (first == second)
			cout << "EQUAL" << endl;
		else
			cout << "NOT EQUAL" << endl;
	}
	else if (testCase == 6) {
		cout << "===== OPERATOR > =====" << endl;
		cout << first;
		cout << second;
		if (first > second)
			cout << "FIRST GREATER THAN SECOND" << endl;
		else
			cout << "FIRST LESSER THAN SECOND" << endl;
	}
	else if (testCase == 7) {
		cout << "===== OPERATOR < =====" << endl;
		cout << first;
		cout << second;
		if (first < second)
			cout << "FIRST LESSER THAN SECOND" << endl;
		else
			cout << "FIRST GREATER THAN SECOND" << endl;
	}
	else if (testCase == 8) {
		cout << "===== MODULE =====" << endl;
		double module = first.module();
		cout << first;
		cout << "Module: " << module << endl;
		cout << second;
		module = second.module();
		cout << "Module: " << module << endl;
	}
	else if (testCase == 9) {
		cout << "===== OPERATOR >> & SUM OF MODULES =====" << endl;
		Equation equation;
		cin >> equation;
		cout << equation.sumModules();
	}
	else if (testCase == 10) {
		cout << "===== EQUATION RESULT =====" << endl;
		Equation equation;
		cin >> equation;
		result = equation.result();
		cout << result;
	}
	return 0;
}
