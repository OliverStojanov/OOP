#include <iostream>
#include <string.h>
using namespace std;
class List{
    private:
    int *brVoLista;
    int brElementi;
    public:
    List(){
        brVoLista = new int[0];
        brElementi = 0;
    }
    List(int *br,int n=0){
        brVoLista= new int[n];
        for(int i=0;i<n;i++){
            brVoLista[i]=br[i];
        }
        brElementi = n;
    }
    List(const List &other){
        brVoLista= new int[other.brElementi];
        for(int i=0;i<other.brElementi;i++){
            brVoLista[i]=other.brVoLista[i];
        }
        brElementi = other.brElementi;
    }
    ~List(){
        delete[]brVoLista;
    }
    List &operator= (List &other){
        if(this!=&other){
            delete [] brVoLista;
            brVoLista= new int[other.brElementi];
            for(int i=0;i<other.brElementi;i++){
                brVoLista[i]=other.brVoLista[i];
            }
            brElementi = other.brElementi;
        }
        return *this;
    }
    void pecati(){
        cout<<brElementi<<":";
        for(int i=0;i<brElementi;i++){
            cout<<" "<<brVoLista[i];
        }
        cout<<" sum: "<<sum()<<" "<<"average: "<<average()<<endl;
    }
    int sum(){
        int sum=0;
        for (int j=0;j<brElementi;j++){
            sum+=brVoLista[j];
        }
        return sum;
    }
    double average(){
        return sum()/(double)brElementi;
    }
    int getElementi(){
        return brElementi;
    }
};
class ListContainer{
    private:
    List *lista;
    int brElementi,brObidi;
    public:
    ListContainer(){
        lista= new List[0];
        brElementi=0;
        brObidi=0;
    }
    ListContainer(const ListContainer &lc){
        lista = new List[lc.brElementi];
        lista=lc.lista;
        brObidi=lc.brObidi;
    }
    ~ListContainer(){
        delete []lista;
    }
    ListContainer &operator= (ListContainer &lc){
        if(this!=&lc){
            delete []lista;
            lista = new List[lc.brElementi];
            for(int i=0;i<lc.brElementi;i++){
                lista[i]=lc.lista[i];
            }
            brElementi = lc.brElementi;
            brObidi=lc.brObidi;
        }
        return *this;
    }
    void pecati(){
        if(brElementi>0){
            for (int i=0;i<brElementi;i++){
                cout<<"List number: "<<i+1;
                cout<<" List info: ";
                lista[i].pecati();
            }
            cout<<"Sum: "<<sum()<<" "<<"Average: "<<average()<<endl;
            cout<<"Successful attempts: "<<brElementi<<" Failed attempts: "<<brObidi-brElementi<<endl;
        }
        else cout<<"The list is empty"<<endl;
    }
    int sum(){
        int globsum=0;
        for (int i=0;i<brElementi;i++){
            globsum+=lista[i].sum();
        }
        return globsum;
    }
    double average(){
        int globElementi=0;
        for(int i=0;i<brElementi;i++){
            globElementi+=lista[i].getElementi();
        }
        return sum()/(double)globElementi;
    }
    void addNewList(List l){
        for(int i = 0; i < brElementi; i++){
            if(l.sum() == lista[i].sum()){
                brObidi++;
                return;
            }
        }
        List *temp = new List[brElementi + 1];
        for(int i = 0; i < brElementi; i++){
            temp[i] = lista[i];
        }
        delete [] lista;
        lista = temp;
        lista[brElementi] = l;
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
        lc1.pecati();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.pecati();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.pecati();
    }
}
