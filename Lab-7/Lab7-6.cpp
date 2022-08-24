#include<iostream>
#include<cstring>
using namespace std;

class Task{
    protected:
        char id[5];
    public:
        Task(char * i){
            strcpy(id,i);
        }
        ~Task(){}
        virtual void print() = 0;
        virtual int getOrder() = 0;
        char *getId(){
            return id;
        }
};
bool operator==(Task * t, Task & m){
    return(!strcmp(t->getId(),m.getId())&& t->getOrder()==m.getOrder());
}

class TimedTask : public Task{
    private:
        int time;
    public:
        TimedTask(char * i, int t) : Task(i){
            time=t;
        }
        void print(){
            cout<<"TT->"<<id<<":"<<time<<endl;
        }

        int getOrder(){
            return time;
        }
};

class PriorityTask : public Task {
    private:
        int priority;
    public:
        PriorityTask(char * i, int p) : Task(i){
            priority=p;
        }
        void print(){
            cout<<"PT->"<<id<<":"<<priority<<endl;
        }

        int getOrder(){
            return priority;
        }
};
void scheduleTimedTasks(Task ** tasks, int n, int t) {
    Task **tmp = new Task*[n];
    int j = 0;
    for(int i = 0; i < n; i++){
        TimedTask *tt = dynamic_cast<TimedTask*>(tasks[i]);
        if(tasks[i]->getOrder() < t && tt != 0){
            tmp[j] = tasks[i];
            j++;
        }
    }
    for(int i=0;i<j;i++){
        for(int k=i+1;k<j;k++){
            if(tmp[i]->getOrder()>tmp[k]->getOrder()){
                swap(tmp[i],tmp[k]);
            }
        }
    }
    for(int i=0; i<j; i++){
        tmp[i]->print();
    }
}

void schedulePriorityTasks(Task ** tasks, int n, int p) {
    Task **tmp = new Task*[n];
    int j = 0;
    for(int i = 0; i < n; i++){
        PriorityTask *pt = dynamic_cast<PriorityTask*>(tasks[i]);
        if(tasks[i]->getOrder() < p && pt != 0){
            tmp[j] = tasks[i];
            j++;
        }
    }
    for(int i=0;i<j;i++){
        for(int k=i+1;k<j;k++){
            if(tmp[i]->getOrder()>tmp[k]->getOrder()){
                swap(tmp[i],tmp[k]);
            }
        }
    }
    for(int i=0; i<j; i++){
        tmp[i]->print();
    }
}

int main () {
    int testCase;
    int n;
    cin>>testCase;

    if (testCase==0){
        cin>>n;
    	Task ** tasks;
        tasks = new Task * [n];
    	for (int i=0;i<n;i++){
        char id [5];
        int timeOrPriority;
        int type; //0 za timed, 1 za priority
        cin >> type >>id >> timeOrPriority;
        if (type==0)
        	tasks[i] = new TimedTask(id,timeOrPriority);
        else
            tasks[i] = new PriorityTask(id,timeOrPriority);
        //tasks[i]->print();
    	}

    	cout<<"SCHEDULING PRIORITY TASKS WITH PRIORITY DEGREE LESS THAN 10"<<endl;
    	schedulePriorityTasks(tasks,n,10);

    }
    else if (testCase==1) {
        cin>>n;
    	Task ** tasks;
        tasks = new Task * [n];
    	for (int i=0;i<n;i++){
        char id [5];
        int timeOrPriority;
        int type; //0 za timed, 1 za priority
        cin >> type >>id >> timeOrPriority;
        if (type==0)
        	tasks[i] = new TimedTask(id,timeOrPriority);
        else
            tasks[i] = new PriorityTask(id,timeOrPriority);
        //tasks[i]->print();
    	}


        cout<<"SCHEDULING TIMED TASKS WITH EXECUTION TIME LESS THAN 50"<<endl;
        scheduleTimedTasks(tasks,n,50);
    }
    else {
        TimedTask * tt1 = new TimedTask("11",10);
        TimedTask * tt2 = new TimedTask("11",11);
        TimedTask * tt3 = new TimedTask("11",11);
        PriorityTask * pp1 = new PriorityTask("aa",10);
        PriorityTask * pp2 = new PriorityTask("11",10);

        cout << (tt1==(*tt2))<<endl;
        cout << (tt2==(*tt3))<<endl;
        cout << (pp1==(*pp2))<<endl;
        cout << (pp2==(*tt1))<<endl;
    }

	return 0;
}
