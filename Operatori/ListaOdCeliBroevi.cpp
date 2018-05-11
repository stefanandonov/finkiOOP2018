#include<iostream>
#include<cmath>
using namespace std;

class List {
	int * elements;
	int length;	
	
	void copy(const List &l){
		this->length=l.length;
		elements = new int [l.length];
		for (int i=0;i<this->length;i++)
			this->elements[i]=l.elements[i];
		
	}
	
	public:
	List() {
		elements = new int [0];
		length = 0;
	}
	
	List (int length, int * elements){
		this->length=length;
		this->elements = new int [length];
		for (int i=0;i<this->length;i++)
			this->elements[i]=elements[i];		
	}
	
	List (const List &l){
		copy(l);
	}
	
	List &operator = (const List &l){
		if (this!=&l){
			delete [] elements;
			copy(l);
		}
		return *this;
	}
	
	int sum () const {
		int sum = 0;
		for (int i=0;i<length;i++)
			sum+=elements[i];
		return sum;
	}
	
	double average() const {
		return (double) sum()/length;
	}
	
	bool operator == (const  List &l) const {
		return sum() == l.sum();
	}
	
	friend ostream &operator<< (ostream &os, const List &l){
		
		if (l.length == 0)
			return os << "The list is empty"<<endl;
		os << l.length << ": ";
		for (int i=0;i<l.length;i++)
			os << l.elements[i] << " ";
		os << "sum: " << l.sum() << " average: " <<l.average() <<endl;
		return os;
	}
	
	friend istream &operator >> (istream &is, List &l){
		is >> l.length;
		l.elements = new int [l.length];
		for (int i=0;i<l.length;i++){
			is >> l.elements[i];
		}
        
        return is;
	}
	
	List operator + (const List &l){
		if (this->length!=l.length)
			return List();
		
		int * tmp = new int [l.length];
		for (int i=0;i<l.length;i++)
			tmp[i] = this->elements[i]+l.elements[i];
		
		return List(length,tmp);
	}
	
	List operator - (const List &l){
		if (this->length!=l.length)
			return List();
		
		int * tmp = new int [l.length];
		for (int i=0;i<l.length;i++)
			tmp[i] = this->elements[i]-l.elements[i];
		
		return List(length,tmp);
	}
	
	List &operator++() {
		for (int i=0;i<length;i++)
			++elements[i];
		
		return *this;
	}
	
	List operator--(int) {
		List l (*this);
		for (int i=0;i<length;i++)
			--elements[i];
		
		return l;
	}
	
	~List() {
		delete [] elements;
	}
	
	int countNumberFrequence (int number){
		int fr = 0;
		for (int i=0;i<length;i++)
			if (elements[i]==number)
				fr++;
			
		return fr;
	}
	
	List &operator += (const int newNumber) {
		//cout<<"Frekvencijata na brojot "<<newNumber<<" e: "<<countNumberFrequence(newNumber)+1<<endl;
		if (countNumberFrequence(newNumber)+1>2){
			return *this;
		}		
		
		int * tmp = new int [length+1];
		for (int i=0;i<length;i++)
			tmp[i]=elements[i];
		
		tmp[length++]=newNumber;
		delete [] elements;
		elements = tmp;
		
		return *this;
	}
	
	List addList (List l) {
		List copy(*this);
		for (int i=0;i<l.length;i++)
			copy+=l[i];
		return copy;
	}

	
	const int &operator [] (int i) {
		return elements[i];
	}	
};


int main() {
	
	int testCase;
	cin>>testCase;
	
	if (testCase==1){
		cout<<"Testiranje na operatorite << i >>"<<endl;
		List l;
		cin >> l;
		cout<< l;
	}
	else if (testCase == 2){
		cout<<"Testiranje na operatorot = za klasata List"<<endl;
		List l1;
		cin >> l1;
		List l2;
		l2 = l1;
		cout << l2;
	}
	else if (testCase == 3){
		//2 test primeri tuka
		cout << "Testiranje na operatorot +"<<endl;
		List l1,l2;
		cin >> l1;
		cin >> l2;
		List l3;
		l3 = l1+l2;
		cout << l3;
	}
	else if (testCase == 4){
		
		cout << "Testiranje na operatorot - "<<endl;
		List l1,l2;
		cin >> l1;
		cin >> l2;
		List l3;
		l3 = l1-l2;
		cout << l3;
	}
	else if (testCase == 5){
		cout << "Testiranje na operator ++ vo prefix notacija"<<endl;
		List l1;
		cin >> l1;
		cout << l1;
		cout << ++l1;
	}
	else if (testCase == 6){
		cout << "Testiranje na operatorot -- vo sufix notacija" << endl;
		List l1;
		cin >> l1;
		cout << "Pocetna vrednost: " << l1;
		List l2;
		l2 = l1--;
		cout << "Se povikuva ++ vo sufiks: " << l2;
		cout << "Posle povik: " << l1;		
	}
	else if (testCase == 7) {
		
		cout << "Testiranje na operator += "<<endl;
		List l1; 
		cin >> l1;
		int n;
		cin >> n;
		for (int i=0;i<n;i++){
			int broj;
			cin >> broj;
			l1 += broj;
		}
		cout << l1;			
	}
	else if (testCase == 8){
		cout << "Testiranje na operatorot [ ] "<< endl;
		List l1;
		cin >> l1;
		int n;
		cin >> n;
		for (int i=0;i<n;i++){
			int idx;
			cin >> idx;
			cout << "List["<< idx <<"] = " << l1[idx] << endl;
		}			
	}
	else {
		//Dopolnitelno baranje
		cout <<"Testiranje na addList() metodot"<<endl;
		List l1,l2;
		cin >> l1;
		cin >> l2;
		cout << l1.addList(l2);
	}
	
	return 0;
}

