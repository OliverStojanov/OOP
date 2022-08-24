#include<iostream>
#include <cstring>
using namespace std;

struct Train{
    char path[50];
    double length;
    int passengerNum;
};
struct TrainStation{
    char city[20];
    Train arr[30];
    int trainNum;
};

void shortestPath(TrainStation *ts, int n, char *city){
    double minDestination=0; int pos1=0, pos2=0;
    for(int i=0; i<n; i++){ if(strcmp(ts[i].city,city)==0){
            for(int j=0; j<ts[i].trainNum; j++){
                minDestination >= ts[i].arr[j].length?minDestination = ts[i].arr[j].length,pos1 = i, pos2 = j:minDestination = ts[i].arr[j].length;
            }
        }
    }
    cout<<"Najkratka relacija: "<<ts[pos1].arr[pos2].path<<" ("<<ts[pos1].arr[pos2].length<<" km)";
}
int main(){

    int num;
	cin>>num; //se cita brojot na zelezlnichki stanici
    TrainStation tStation[100];
    for(int i=0; i<num; i++){ cin>>tStation[i].city>>tStation[i].trainNum;
        for(int j=0; j<tStation[i].trainNum; j++){
            cin>>tStation[i].arr[j].path>>tStation[i].arr[j].length>>tStation[i].arr[j].passengerNum;
        }
    }
    char city[25];
    cin>>city;
    shortestPath(tStation,num,city);
	return 0;
}
