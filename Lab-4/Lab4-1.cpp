#include <iostream>
#include<cstring>
using namespace std;
class List{
    private:
        int * brOdLista;
        int brElementi;
    public:
        List(){
            brOdLista= new int[0];
            brElementi=0;
        }
        List(int *br, int n){
            brElementi=n;
            brOdLista=new int[n];
            for(int i=0;i<n;i++){
                brOdLista[i]=br[i];
            }
        }
        List(const List & list){
            brElementi=list.brElementi;
            brOdLista=new int[list.brElementi];
            for(int i=0;i<brElementi;i++){
                brOdLista[i]=list.brOdLista[i];
            }
        }
        ~List(){
            delete [] brOdLista;
        }
        List &operator= (List &list){
            if(this!=&list){
                delete [] brOdLista;
                brElementi=list.brElementi;
                brOdLista=new int[list.brElementi];
                for(int i=0;i<brElementi;i++){
                    brOdLista[i]=list.brOdLista[i];
                }
            }
        }
        int sum(){
            int suma=0;
            for(int i=0;i<brElementi;i++){
                    suma+=brOdLista[i];
            }
            return suma;
        }
        double average(){
            return sum()/(double)brElementi;
        }
        void pecati(){
            cout<<brElementi<<": ";
            for(int i=0;i<brElementi;i++){
                cout<<brOdLista[i]<<" ";
            }
            cout<<"sum: "<<sum()<<" average: "<<average()<<endl;
        }
        int getBrElementi(){
            return brElementi;
        }
};
class ListContainer{
    private:
        List *listi;
        int brElementi;
        int brObidi;
    public:
        ListContainer(){
            brObidi=0;
            brElementi=0;
            listi=new List[0];
        }
        ListContainer(const ListContainer & li){
            brObidi=li.brObidi;
            brElementi=li.brElementi;
            listi=new List[brElementi];
        }
        ~ListContainer(){
            delete[] listi;
        }
        ListContainer &operator=(ListContainer & li){
            if(this!=&li){
                delete [] listi;
                brObidi=li.brObidi;
                brElementi=li.brElementi;
                listi=new List[brElementi];
                for(int i=0;i<brElementi;i++){
                    listi[i]=li.listi[i];
                }
            }
        }
        void print(){
            if(brElementi>0){
                for(int i=0;i<brElementi;i++){
                cout<<"List number: "<<i+1<<" List info: ";
                listi[i].pecati();
                }
                cout<<"Sum: "<<sum()<<" Average: "<<average()<<endl;
                cout<<"Successful attempts: "<<brElementi<<" Failed attempts: "<<brObidi-brElementi<<endl;
            }else cout<<"The list is empty"<<endl;
        }
        int sum(){
            int globSum = 0;
            for(int i = 0; i < brElementi; i++){
                globSum += listi[i].sum();
            }
            return globSum;
        }
        double average(){
            int globElementi = 0;
            for(int i = 0; i < brElementi; i++){
                globElementi += listi[i].getBrElementi();
            }
            return sum() / (double) globElementi;
        }
        void addNewList(List li){
            for(int i=0;i<brElementi;i++){
                if(li.sum()==listi[i].sum()){
                    brObidi++;
                    return;
                }
            }
            List *temp = new List[brElementi + 1];
            for(int i = 0; i < brElementi; i++){
                temp[i] = listi[i];
            }
            delete [] listi;
                listi = temp;
            listi[brElementi] = li;
            brElementi++;
            brObidi++;
        }
};

int main() {

	ListContainer lc;
	int N;
	cin>>N;

	for (int i=0;i<N;i++) {
		int n;
		int niza[100];

		cin>>n;

		for (int j=0;j<n;j++){
			cin>>niza[j];

		}

		List l=List(niza,n);

		lc.addNewList(l);
	}


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}
