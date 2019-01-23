#include<iostream>
#include<string.h>
using namespace std;

class Date {
    int dd,mm, yy;
public:
    Date(int d=1,int m=1,int g=1900) {
        dd=d;
        mm=m;
        yy=g;
    }
    static int compare(Date d1,Date d2) {
        if(d1.yy<d2.yy)       return 1;
        else if (d1.yy>d2.yy) return -1;
        else if (d1.mm<d2.mm) return 1;
        else if (d1.mm>d2.mm) return -1;
        else if (d1.dd<d2.mm) return 1;
        else if (d1.dd>d2.dd) return -1;
        else return 0;
    }
    int getDay() const {
        return dd;
    }
    int getMonth()const {
        return mm;
    }
    int getYear()const {
        return yy;
    }
};

class InvalidAccountNumber {
private:
    char number [16];
    bool numberOfChars;
public:
    InvalidAccountNumber(char * number, bool numberOfChars) {
        strcpy(this->number,number);
        this->numberOfChars=numberOfChars;
    }

    void message () {
        if (!numberOfChars)
            cout<<"Non-digit account number form"<<endl;
        else
            cout<<"Error in the number of chars"<<endl;

    }
};

class Transaction {
private:
    char * name;
    char number[16];
    float amount;
    Date date;

    void copy (const Transaction &t) {
        strcpy(this->number,t.number);
        this->name = new char [strlen(t.name)];
        strcpy(this->name,t.name);
        this->amount = t.amount;
        this->date=t.date;
    }
public:
    Transaction() {
        name = new char [0];
        strcpy(name,"");
        amount = 0;

    }

    Transaction (char * name, char * number, float amount, Date date) {
        this->name = new char [strlen(name)];
        strcpy(this->name,name);

        //proverka
        if (strlen(number)!=15)
            throw InvalidAccountNumber(number,true);
        for (int i=0; i<15; i++)
            if (!isdigit(number[i]))
                throw InvalidAccountNumber(number,false);

        strcpy(this->number,number);
        this->amount=amount;
        this->date=date;
    }

    Transaction (const Transaction &t) {
        copy(t);
    }

    Transaction &operator = (const Transaction &t) {
        if (&t!=this) {
            delete name;
            copy(t);
        }

        return *this;
    }

    ~Transaction() {
        delete name;
    }

    Date getDate() {
        return date;

    }

    float getAmount() {
        return amount;

    }

    friend ostream &operator << (ostream &out, const Transaction &t) {
        if (t.amount>=0)
            out<<"Inflow "<<t.amount<<" "<<t.name<<"("<<t.number<<")-"<<t.date.getDay()<<"."<<t.date.getMonth()<<"."<<t.date.getYear()<<endl;
        else
            out<<"Outflow "<<t.amount<<" "<<t.name<<"("<<t.number<<")-"<<t.date.getDay()<<"."<<t.date.getMonth()<<"."<<t.date.getYear()<<endl;
        return out;
    }


};

class TransactionAccount {
private:
    char * name;
    char number [16];
    Transaction * tr;
    int size;
    int capacity;

    void copy (const TransactionAccount &ta) {
        name = new char [strlen(ta.name)];
        strcpy(name,ta.name);
        strcpy(number,ta.number);
        size=ta.size;
        capacity=ta.capacity;
        tr = new Transaction [size];
        for (int i=0; i<size; i++)
            tr[i]=ta.tr[i];
    }

public:
    TransactionAccount() {
        name = new char [0];
        strcpy(number,"");
        tr = new Transaction [0];
        size=0;
        capacity=3;
    }

    TransactionAccount(const TransactionAccount &ta) {
        copy(ta);
    }

    TransactionAccount &operator = (const TransactionAccount &ta) {
        if (this!=&ta) {
            delete [] name;
            delete [] tr;
            copy(ta);
        }

        return *this;
    }

    TransactionAccount(char * name, char * number) {
        this->name = new char [strlen(name)];
        strcpy(this->name,name);
        strcpy(this->number,number);
        tr = new Transaction [0];
        size=0;
        capacity=3;
    }

    ~TransactionAccount() {


        delete [] tr;

        delete name;
    }

    void addTransaction (Transaction t) {

        if (size==capacity)
            capacity*=2;

        Transaction * tmp = new Transaction [size+1];
        for (int i=0; i<size; i++)
            tmp[i]=tr[i];
        tmp[size]=t;
        size=size+1;
        delete [] tr;
        tr = tmp;


    }

    void reportTransaction(Date from, Date to, bool isInflow) {

        int k = 0;
        Transaction * tmp = new Transaction [size];
        for (int i=0; i<size; i++)
            if ((Date::compare(to,tr[i].getDate())<=0)&&(Date::compare(from,tr[i].getDate())>=0)) {
                tmp[k++]=tr[i];

            }

        Transaction temp;
        for(int i=0; i<k; i++) {
            for(int j=i+1; j<k; j++) {
                //If there is a smaller element found on right of the array then swap it.
                if(Date::compare(tmp[j].getDate(), tmp[i].getDate())==1) {
                    temp = tmp[i];
                    tmp[i] = tmp[j];
                    tmp[j] = temp;
                }
            }
        }

        cout<<"Name (acc. number):"<<this->name<<"("<<this->number<<")"<<endl;
        for (int i=0; i<k; i++)
            if (isInflow) {
                if (tmp[i].getAmount()>=0)
                    cout<<tmp[i];
            } else {
                cout<<tmp[i];
            }

    }

    int getTransCapacity() {
        return capacity;
    }

    int getTransNumber() {
        return size;
    }

    Transaction * getTransList() {
        return tr;
    }

    float getBalance() {
        float sum = 0;
        for (int i=0; i<size; i++)
            sum+=tr[i].getAmount();


        return sum;
    }


};

//your code here

int main() {

    char name[50],number[16];
    float amount;
    int d,m,y;
    int n;
    bool isInflow;
    TransactionAccount ta;
    int testcase;
    cin>>testcase;

    switch (testcase) {
    case 1: {
        cout<<"------Transaction test------"<<endl;
        cin>>name;
        cin>>number;
        cin>>amount;
        cin>>d>>m>>y;
        Transaction t(name,number,amount,Date(d,m,y));
        cout<<t;
    }
    break;
    case 2: {
        cout<<"------TransactionAccount test:constructor, desctuctor & get-functions------"<<endl;
        cin>>name;
        cin>>number;
        TransactionAccount ta(name,number);
        cin>>n;
        for (int j=0; j<n; j++) {

            cin>>name>>number>>amount>>d>>m>>y;
            Transaction t(name,number,amount,Date(d,m,y));
            ta.addTransaction(t);

        }
        cout<<"Capacity: "<<ta.getTransCapacity()<<endl;
        cout<<"Number of elements: "<<ta.getTransNumber()<<endl;
        cin>>n;
        cout<<"The element on position "<<n<<" is "<<endl;
        cout<<(ta.getTransList())[n];
    }
    break;
    case 3: {
        cout<<"------TransactionAccount: getSaldo------"<<endl;
        cin>>name;
        cin>>number;
        TransactionAccount ta(name,number);
        cin>>n;
        for (int j=0; j<n; j++) {

            cin>>name>>number>>amount>>d>>m>>y;
            Transaction t(name,number,amount,Date(d,m,y));
            ta.addTransaction(t);

        }
        cout<<"Balance: "<<ta.getBalance()<<endl;
    }
    break;
    case 4: {
        cout<<"------TransactionAccount: reportTransaction & Exception------"<<endl;
        cin>>name;
        cin>>number;
        ta=TransactionAccount(name,number);
        cin>>n;
        for (int j=0; j<n; j++) {
            try {
                cin>>name>>number>>amount>>d>>m>>y;
                Transaction t(name,number,amount,Date(d,m,y));
                ta.addTransaction(t);
            } catch (InvalidAccountNumber &e) {
                e.message();
            }
        }
        cin>>d>>m>>y;
        Date d1(d,m,y);
        cin>>d>>m>>y;
        Date d2(d,m,y);
        cin>>isInflow;
        ta.reportTransaction(d1,d2,isInflow);
    }
    break;

    };

    return 0;
}

