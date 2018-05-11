#include<iostream>
#include<cstring>
using namespace std;

class Task {
    protected:
    char ID [5];
    
    public: 
    Task (char * id = ""){
        strcpy(ID,id);
    }
    
    char * getID() {
    return ID;
    }
    
    virtual int getOrder() = 0;
    virtual void print() = 0;
};



class TimedTask : public Task{
    private:
    int time;
    
    public:
    TimedTask(char * id, int time) : Task(id) {
        this->time=time;
    }
    
    int getOrder() {
        return time;
    }
    
    void print() {
        cout<<"TT->"<<ID<<":"<<time<<endl;
    }   
    
};

class PriorityTask : public Task {
    private:
    int priority;
    
    public:
    PriorityTask(char * id, int priority) : Task(id) {
        this->priority=priority;
    }
    
    int getOrder() {
        return priority;
    }
    
    void print() {
        cout<<"PT->"<<this->ID<<":"<<priority<<endl;
    } 
    
    
};

bool operator ==(Task * t1, Task & t2) {
    return strcmp(t1->getID(),t2.getID())==0&&t1->getOrder()==t2.getOrder();
}

void scheduleTimedTasks(Task ** tasks, int n,int t) {
    for (int i=0;i<n-1;i++){
        for (int j=i+1;j<n;j++){
            if (tasks[i]->getOrder()>tasks[j]->getOrder()){
                Task * tmp = tasks[i];
                tasks[i]=tasks[j];
                tasks[j]=tmp;
            }
        }
    }
    
    for (int i=0;i<n;i++){
        TimedTask * timed = dynamic_cast<TimedTask *>(tasks[i]);
        if (timed!=0&&tasks[i]->getOrder()<t){
            tasks[i]->print();
        }
    }
}


void schedulePriorityTasks(Task ** tasks, int n, int p){
    for (int i=0;i<n-1;i++){
        for (int j=i+1;j<n;j++){
            if (tasks[i]->getOrder()>tasks[j]->getOrder()){
                Task * tmp = tasks[i];
                tasks[i]=tasks[j];
                tasks[j]=tmp;
            }
        }
    }
    
    for (int i=0;i<n;i++){
        PriorityTask * timed = dynamic_cast<PriorityTask *>(tasks[i]);
        if (timed!=0&&tasks[i]->getOrder()<p){
            tasks[i]->print();
        }
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