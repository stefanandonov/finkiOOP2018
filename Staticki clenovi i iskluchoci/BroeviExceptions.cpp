#include<iostream>
#include<cstring>

using namespace std;

class ArithmeticException {
	
	public:
	void message() {
		cout<<"Division by zero is not allowed"<<endl;
	}
};

class NumbersNotDivisibleException {
	private:
	int divider;
	
	public:
	NumbersNotDivisibleException (int d){
		divider=d;
	}
	
	void message() {
		cout<<"Division by "<<divider<<" is not supported"<<endl;		
	}
};

class ArrayFullException{
	public:
	void message() {
		cout<<"The array is full. Increase the capacity"<<endl;
	}
};

class IndexOutOfBoundsException {
	private:
	int index;
	
	public:
	IndexOutOfBoundsException(int i){
		index=i;
	}
	
	void message() {
		cout<<"Index "<<index<<" is out of bounds"<<endl;
	}
};

class NumbersIsNotPositiveException {
	private:
	int number;
	
	public:
	NumbersIsNotPositiveException(int n) {
		number=n;
	}
	
	void message() {
		cout<<"Number "<<number<<" is not positive integer"<<endl;
	}
};

class PositiveIntegers {
	private:
	int * numbers;
	int size;
	int capacity;
	
	void copy(const PositiveIntegers &ps){
		numbers = new int [ps.capacity];
		for (int i=0;i<ps.size;i++)
			numbers[i]=ps.numbers[i];
		size=ps.size;
		capacity=ps.capacity;
	}
	
	public:
	PositiveIntegers(int capacity=0){
		this->capacity=capacity;
		numbers = new int [capacity];
		size = 0;
	}
	
	PositiveIntegers (const PositiveIntegers &ps){
		copy(ps);
	}
	
	PositiveIntegers &operator = (const PositiveIntegers &ps){
		if (this!=&ps){
			delete [] numbers;
			copy(ps);
		}
        
        return *this;
	}
	
	~PositiveIntegers() {
		//delete [] numbers;
	}
	
	void increaseCapacity(int c) {
		int * tmp = new int [capacity+c];
		for (int i=0;i<size;i++){
			tmp[i]=numbers[i];
		}
		delete [] numbers;
		numbers=tmp;
		capacity+=c;
	}
	
	PositiveIntegers &operator += (int newNumber){
		if (size==capacity)
			throw ArrayFullException();
		if (newNumber<=0)
			throw NumbersIsNotPositiveException(newNumber);
		
		numbers[size++]=newNumber;
        return *this;
	}
	
	PositiveIntegers operator * (int x) {
		PositiveIntegers pi (*this);
		for (int i=0;i<pi.size;i++)
			pi.numbers[i]*=x;
		
		return pi;
	}
	
	PositiveIntegers operator / (int x){
		if (x==0)
			throw ArithmeticException();
		for (int i=0;i<size;i++)
			if (numbers[i]%x!=0)
				throw NumbersNotDivisibleException(x);
			
		PositiveIntegers pi (*this);
		for (int i=0;i<pi.size;i++)
			pi.numbers[i]/=x;
		
		return pi;
	}
	
	int &operator [] (int i){
		if (i<0 || i>this->size)
			throw IndexOutOfBoundsException(i);
		
		return numbers[i];
	}
	
	void print () {
		cout<<"Size: "<<size<<" Capacity: "<<capacity<<" Numbers: ";
		for (int i=0;i<size;i++)
			cout<<numbers[i]<<" ";
		
		cout<<endl;
	}
	
	
	
	
};


int main() {
	
	int n,capacity;
	cin >> n >> capacity;
	PositiveIntegers pi (capacity);
	for (int i=0;i<n;i++){
		int number;
		cin>>number;
		try{
            //cout<<number;
		pi+=number;
        
		}
		catch (ArrayFullException &e){
			e.message();
		}
		catch (NumbersIsNotPositiveException &e){
			e.message();
		}
	}
	cout<<"===FIRST ATTEMPT TO ADD NUMBERS==="<<endl;
	pi.print();
	int incCapacity;
	cin>>incCapacity;
	pi.increaseCapacity(incCapacity);
	cout<<"===INCREASING CAPACITY==="<<endl;
	pi.print();
	
	int n1;
	cin>>n1;
	for (int i=0;i<n1;i++){
		int number;
		cin>>number;
		try{
            //cout<<number;
		pi+=number;
        
		}
		catch (ArrayFullException &e){
			e.message();
		}
		catch (NumbersIsNotPositiveException &e){
			e.message();
		}
	}
	cout<<"===SECOND ATTEMPT TO ADD NUMBERS==="<<endl;
	pi.print();
	
	PositiveIntegers pi1;
	
	cout<<"===TESTING DIVISION==="<<endl;
	
	try{
	pi1 = pi/0;
	pi1.print();
	}
	catch (ArithmeticException &e){
		e.message();
	}
	catch (NumbersNotDivisibleException &e){
		e.message();
	}
	
	try{
	pi1 = pi/1;
	pi1.print();
	}
	catch (ArithmeticException &e){
		e.message();
	}
	catch (NumbersNotDivisibleException &e){
		e.message();
	}
	
	try{
	pi1 = pi/2;
	pi1.print();
	}
	catch (ArithmeticException &e){
		e.message();
	}
	catch (NumbersNotDivisibleException &e){
		e.message();
	}
	
	cout<<"===TESTING MULTIPLICATION==="<<endl;
	pi1 = pi*3;
	pi1.print();
	
	
	cout<<"===TESTING [] ==="<<endl;
	
	try{
	cout<<"PositiveIntegers[-1] = "<<pi[-1]<<endl;
	
	}
	catch (IndexOutOfBoundsException &e){
		e.message();
	}
	
	try{
	cout<<"PositiveIntegers[2] = "<<pi[2]<<endl;
	}
	catch (IndexOutOfBoundsException &e){
		e.message();
	}
	
	try{	
	cout<<"PositiveIntegers[3] = "<<pi[3]<<endl;
	}
	catch (IndexOutOfBoundsException &e){
		e.message();
	}
	
	try{
	cout<<"PositiveIntegers[12] = "<<pi[12]<<endl;
	}
	catch (IndexOutOfBoundsException &e){
		e.message();
	}
	
	
	
	return 0;
}