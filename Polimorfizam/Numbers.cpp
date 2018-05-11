#include<iostream>
using namespace std;

class Number {
	public:
	virtual int intValue() = 0;
	virtual double doubleValue() = 0;
	virtual void print() = 0;
};

class Integer : public Number{
	private:
	int number;
	
	public:
	Integer(int number){
		this->number=number;
	}
	
	Integer(const Integer &n){
		this->number=n.number;
	}
	
	int intValue() {
		return number;
	}
	
	double doubleValue() {
		return (double) number;
	}
	
	void print () {
		cout << "Integer: " << number << endl;
	}
	
	
	
};

class Double : public Number{
	private:
	double number;
	
	public:
	Double(double number){
		this->number=number;
	}
	
	Double(const Double &n){
		this->number=n.number;
	}
	
	int intValue() {
		return (int) number;
	}
	
	double doubleValue() {
		return number;
	}
	
	void print () {
		cout << "Double: " << number << endl;
	}
	
};

class Numbers {
	private:
	Number ** numbers;
	int count;
	
	void copy (const Numbers &n){
		this->count=n.count;
		this->numbers = new Number * [n.count+1];
		for (int i=0;i<this->count;i++)
			numbers[i]=n.numbers[i];
	}
	
	public:
	Numbers() {
		this->numbers = new Number * [0];
		count = 0;
	}
	
	Numbers (const Numbers &n){
		copy(n);
	}
	
	Numbers &operator = (const Numbers &n){
		if (this!=&n){
			delete [] numbers;
			copy(n);
		}
		return *this;
	}
	
	~Numbers () {
		delete [] numbers;
	}
	
	Numbers &operator += (Number * n){
		Number ** tmp = new Number * [this->count+1];
		for (int i=0;i<count;i++)
			tmp[i]=numbers[i];
		
		tmp[count++]=n;
		delete [] numbers;
		numbers=tmp;
		return *this;
	}
	
	void statistics() {
		
		int integers=0,doubles=0;
		int sumInt=0;
		double sumAll=0.0;
		double sumDouble=0.0;
		
		for (int i=0;i<count;i++){
			Integer * integer = dynamic_cast<Integer *>(numbers[i]);
			if (integer!=0){
				integers++;
				sumInt+=numbers[i]->intValue();
				
			}
			Double * doublee = dynamic_cast<Double *>(numbers[i]);
			if (doublee!=0){
				doubles++;
				sumDouble+=numbers[i]->doubleValue();
			}
			sumAll+=numbers[i]->doubleValue();
		}
		
		cout<<"Count of numbers: "<<count<<endl;

		cout<<"Sum of all numbers: "<<sumAll<<endl;

		cout<<"Count of integer numbers: "<<integers<<endl;

		cout<<"Sum of integer numbers: "<<sumInt<<endl;

		cout<<"Count of double numbers: "<<doubles<<endl;

		cout<<"Sum of double numbers: "<<sumDouble<<endl;//[сума на сите децимални броеви (Double)]
	}
	
	void integersLessThan (Integer n) {
        bool flag = true;
		for (int i=0;i<count;i++){
			Integer * integer = dynamic_cast<Integer *>(numbers[i]);
            if (integer!=0&&numbers[i]->intValue()<n.intValue()){
				numbers[i]->print();
                flag=false;
            }
		}
        
        if (flag)
            cout<<"None"<<endl;
	}
	
	void doublesBiggerThan (Double n) {
        bool flag = true;
		for (int i=0;i<count;i++){
			Double * doublee = dynamic_cast<Double *>(numbers[i]);
            if (doublee!=0 && numbers[i]->doubleValue()>n.doubleValue()){
                numbers[i]->print();
                flag=false;
            }
		}
        if (flag)
            cout<<"None"<<endl;
	}	
};



int main() {
	
	int n;
	cin>>n;
	Numbers numbers;
	for (int i=0;i<n;i++){
		int type;
		double number;
		cin>>type>>number;
		if (type==0){//Integer object
			Integer * integer = new Integer((int) number);
			numbers+=integer;
		}
		else {
			Double * doublee = new Double(number);
			numbers+=doublee;
		}
	}
	
	int lessThan;
	double biggerThan;
	
	cin>>lessThan;
	cin>>biggerThan;		
	
	cout<<"STATISTICS FOR THE NUMBERS\n";
	numbers.statistics();
	cout<<"INTEGER NUMBERS LESS THAN "<<lessThan<<endl;
	numbers.integersLessThan(Integer(lessThan));
	cout<<"DOUBLE NUMBERS BIGGER THAN "<<biggerThan<<endl;
	numbers.doublesBiggerThan(Double(biggerThan));
	
	return 0;
}