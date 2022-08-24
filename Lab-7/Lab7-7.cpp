#include<cstring>
#include<iostream>
using namespace std;

class Secret{
    public:
        virtual double simpleEntropy() = 0;
        virtual int total() = 0;
};

bool operator==(Secret &s, Secret &s1){
    return s.simpleEntropy()==s1.simpleEntropy()&&s.total()==s1.total();
}
bool operator!=(Secret &s, Secret &s1){
    return s.simpleEntropy()!=s1.simpleEntropy()||s.total()!=s1.total();
}

class DigitSecret : public Secret{
    private:
        int digit[100];
        int br;
    public:
        DigitSecret(int * d, int b){
            for(int i=0;i<b;i++){
                digit[i]=d[i];
            }
            br=b;
        }
        double simpleEntropy(){
            int pojavuvanje[10] = {0}, unik = 0;
            for(int i = 0; i < br; i++){
                pojavuvanje[digit[i]]++;
            }
            for(int i = 0; i < 10; i++){
                if(pojavuvanje[i] == 1){
                    unik++;
                }
            }
            return (double)unik / br;
        }
        int total(){
            return br;
        }
        friend ostream & operator<<(ostream &out, DigitSecret &ds){
            for(int i=0; i<ds.br; i++){
                out<<ds.digit[i];
            }
            return out<<" Simple entropy: "<<ds.simpleEntropy()<<" Total: "<<ds.total();
        }
};

class CharSecret : public Secret {
    private:
        char c[100];
        int br;
    public:
        CharSecret(char * d){
            strcpy(c,d);
            br=strlen(c);
        }
        double simpleEntropy(){
            int pojavuvanje[26] = {0}, unik = 0, vk = 0;
            for(int i = 0; c[i] != '\0'; i++){
                pojavuvanje[c[i] - 'a']++;
                vk++;
            }
            for(int i = 0; i < 26; i++){
                if(pojavuvanje[i] == 1){
                    unik++;
                }
            }
            return (double)unik / vk;
        }
        int total(){
            return br;
        }
        friend ostream & operator<<(ostream &out, CharSecret &cs){
            for(int i=0; i<cs.br; i++){
                out<<cs.c[i];
            }
            return out<<" Simple entropy: "<<cs.simpleEntropy()<<" Total: "<<cs.total()<<endl;
        }
};

void process(Secret ** secrets, int n){
    int maxEntropy=0;
    for(int i=1; i<n; i++){
        if(secrets[i]->simpleEntropy()>secrets[maxEntropy]->simpleEntropy()){
            maxEntropy=i;
        }
    }
    DigitSecret *d = dynamic_cast<DigitSecret*>(secrets[maxEntropy]);
    if(d != 0){
        cout << *d;
    }
    else{
        CharSecret *c = dynamic_cast<CharSecret*>(secrets[maxEntropy]);
        cout << *c;
    }
}

void printAll (Secret ** secrets, int n) {
    for(int i=0; i<n; i++){
        DigitSecret *d = dynamic_cast<DigitSecret*>(secrets[i]);
        if(d != 0){
            cout << *d<<endl;
        }
        else{
            CharSecret *c = dynamic_cast<CharSecret*>(secrets[i]);
            cout << *c;
        }
    }
}


int main() {
    int n;
    cin >> n;
    if(n == 0) {
		cout << "Constructors" << endl;
		int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        cout << "OK" << endl;
    } else if(n == 1) {
  		cout << "operator <<" << endl;
		int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        cout << ds << endl;
        cout << cs << endl;
    }  else if(n == 2) {
  		cout << "== and !=" << endl;
		int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        CharSecret css("abcabc");
        cout << (ds == cs) << endl;
        cout << (cs != ds) << endl;
        cout << (cs == css) << endl;
        cout << (cs != css) << endl;
    } else if(n == 3) {
  		cout << "Secret processor" << endl;
		int numbers1 [] = {1,2,3,4,5,6,4,3,2,1,1,2,3,4,5};
        DigitSecret ds1(numbers1,15);
		int numbers2 [] = {1,2,3,4,5,0,0,0,5,5,4,4,3,3,2};
        DigitSecret ds2(numbers2,15);
		int numbers3 [] = {1,0,9,4,3,8,4,0,9,3,1,4,3,2,1,4,4,3,7,2};
        DigitSecret ds3(numbers3,20);
        CharSecret cs1("fhdaieowujkfjdsafjdsakjhueiqoyroq");
        CharSecret cs2("nvzcfsadrqipqhfjdfncxoqw");
        CharSecret cs3("uyoihfdsanmqeqrzvdhfeqyrq");
        Secret** s = new Secret*[6];
        s[0] = &ds1;
        s[1] = &ds2;
        s[2] = &ds3;
        s[3] = &cs1;
        s[4] = &cs2;
        s[5] = &cs3;
        process(s,6);
        delete [] s;
    }
    else if (n==4){
        cout << "Print all secrets" << endl;
		int numbers1 [] = {1,2,3,4,5,5,4,3,2,1,1,2,3,4,5};
        DigitSecret ds1(numbers1,15);
		int numbers2 [] = {1,2,3,4,5,0,0,0,5,5,4,4,3,3,2};
        DigitSecret ds2(numbers2,15);
		int numbers3 [] = {1,0,9,4,3,8,4,0,9,3,1,4,3,2,1,4,4,3,7,2};
        DigitSecret ds3(numbers3,20);
        CharSecret cs1("fhdaieowujkfjdsafjdsakjhueiqoyroq");
        CharSecret cs2("nvzcfsadrqipqhfjdfncxoqw");
        CharSecret cs3("uyoihfdsanmqeqrzvdhfeqyrq");
        Secret** s = new Secret*[6];
        s[0] = &ds1;
        s[1] = &ds2;
        s[2] = &ds3;
        s[3] = &cs1;
        s[4] = &cs2;
        s[5] = &cs3;
        printAll(s,6);
        delete [] s;
    }

    return 0;
}
