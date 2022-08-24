#include <iostream>
using namespace std;

class Agol {
    private:
    int stepeni,minuti,sekundi;
    public:
    Agol(){}
    Agol(int deg, int min, int sec){
        stepeni=deg;
        minuti=min;
        sekundi=sec;
    }
    ~Agol(){}
    void set_stepeni(int deg){
        stepeni=deg;
    }
    void set_minuti(int min){
        minuti=min;
    }
    void set_sekundi(int sec){
        sekundi=sec;
    }
    int getSekundi(){
        return sekundi;
    }
    int to_sekundi(){
        return stepeni*60*60+minuti*60+sekundi;
    }
};
int proveri(int deg, int min, int sec){
    if(deg<360&&deg>=0){
        if(min<60&&min>=0){
            if(sec<60&&sec>=0){
                return 1;
            }else cout<<"Nevalidni vrednosti za agol";
        }else cout<<"Nevalidni vrednosti za agol";
    }else cout<<"Nevalidni vrednosti za agol";
}

bool changeOfSeconds(Agol a, int sec){
	return a.getSekundi()!=sec;
}

int main() {

    Agol a1;
    int deg, min, sec;
    cin >> deg >> min >> sec;

    if (proveri(deg, min, sec)==1) {

    	a1.set_stepeni(deg);
        a1.set_minuti(min);
        a1.set_sekundi(sec);
        cout << a1.to_sekundi();
        if (changeOfSeconds(a1,sec))
			cout << "Ne smeete da gi menuvate sekundite vo ramkite na klasata!" << endl;

    }

    return 0;
}
