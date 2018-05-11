#include<iostream>
#include<cstring>

using namespace std;

class Par {
	char * kluc;
	double vrednost;
	
	void copy (const Par &p){
		this->kluc = new char [strlen(p.kluc)+1];
		strcpy(this->kluc,p.kluc);
		this->vrednost = p.vrednost;
	}
	
	public:
	
	Par () {
		this -> kluc = new char [0];
		vrednost = 0;
	}
	Par (char * kluc, double vrednost){
		this->kluc = new char [strlen(kluc)+1];
		strcpy(this->kluc,kluc);
		this->vrednost = vrednost;
	}
	
	Par (const Par &p){
		copy(p);
	}
	
	Par &operator = (const Par &p){
		if (this!=&p){
			delete [] kluc;
			copy(p);
		}
		
		return *this;
	}
	
	~Par(){
		delete [] kluc;
	}
	
	friend ostream &operator << (ostream &os, const Par &p){
		return os << "(" << p.kluc <<", " << p.vrednost <<")"<<endl;
	}
	
	Par &operator++ () {
		vrednost ++ ;
		return *this;
	}
	
	Par operator++ (int) {
		Par p (*this);
		vrednost++;
		return p;
	}
	
	Par operator + (const Par &p){
		if (strlen(this->kluc)>=strlen(p.kluc))
			return Par(this->kluc,this->vrednost+p.vrednost);
		else 
			return Par(p.kluc,this->vrednost+p.vrednost);	
	}
	
	bool operator == (const Par &p){
		return strcmp(this->kluc,p.kluc)==0&&this->vrednost == p.vrednost;
	}
	
	bool operator != (const Par &p){
		return strcmp(this->kluc,p.kluc)!=0 || this->vrednost != p.vrednost;
	}
	
	friend class Kolekcija;
	
	
};

class Kolekcija {
	private:
	Par * parovi;
	int n;
	
	void copy (const Kolekcija &k){
		this->n=k.n;
		this->parovi = new Par [k.n];
		for (int i=0;i<n;i++)
			this->parovi[i]=k.parovi[i];
	}
	
	public:
	Kolekcija() {
		this->n = 0;
		parovi = new Par [0];
	}
	
	Kolekcija (const Kolekcija &k){
		copy(k);
	}
	
	Kolekcija &operator = (const Kolekcija &k){
		if (this!=&k){
			delete [] parovi;
			copy(k);
		}
		return *this;
	}
	
	~Kolekcija() {
		delete [] parovi;
	}
	
	Kolekcija &operator += (const Par &p){

		Par * tmp = new Par [n+1];
		
		for (int i=0;i<n;i++)
			tmp[i]=parovi[i];
		
		tmp[n++]=p;
		
		//delete [] parovi;
		
		parovi = tmp;
		
		
		return *this;
	}
	
	friend ostream &operator << (ostream &os, const Kolekcija &k){
		os<<k.n<<endl;
		for (int i=0;i<k.n;i++)
			os << k.parovi[i];
		
		return os;
	}
	
	bool operator == (const Kolekcija &k){
		if (this->n!=k.n)
			return false;
		
		for (int i=0;i<this->n;i++)
			if (this->parovi[i]!=k.parovi[i])
				return false;
			
		return true;
	}
	
	void najdi (const char * kluc){
		//bool found = false;
		
		for (int i=0;i<n;i++)
			if (strcmp(parovi[i].kluc,kluc)==0){
				cout << parovi[i];
				return ;
			}
			
		cout << "Ne postoi par so kluc: "<<kluc<<endl;
				
	}
};

void printTrueOrFalse (Kolekcija k1, Kolekcija k2){
	if (k1==k2)
		cout << "TRUE" <<endl;
	else
		cout <<"FALSE" << endl;
}

int main() {
	
	int testCase;
	cin >> testCase;
	
	if (testCase == 1){
		cout<<"Testiranje na konstruktori za Par i operator << "<<endl;
		Par p[20];
		int n;
		cin>>n;
		char kluc[50];
		double vrednost;
		for (int i=0;i<n;i++){
			cin >> kluc >> vrednost;
			//cout << kluc << vrednost;
			Par p1 = Par(kluc,vrednost);
			//cout <<"GRESKA";
			p[i] = p1;
			cout << p[i];
		}
	}
	else if (testCase == 2) {
		cout << "Testiranje na operatorite ++ vo prefix i postfix notacija" <<endl;
		Par p1 = Par("FINKI",10.20);
		
		cout << p1;
		cout << p1++;
		cout << p1;
		
		Par p2 = Par("OOP",69.69);
		
		cout << p2;
		cout << ++p2;
		cout << p2;		
	}
	else if (testCase == 3) {
		cout << "Testiranje na operatorot + vo klasata Par"<<endl;
		double vrednost;
		char kluc[50];
		Par p[2];
		for (int i=0;i<2;i++){
			cin >> kluc >> vrednost;
			p[i]=Par(kluc,vrednost);
		}
		
		cout << p[0]+p[1];			
	}
	else if (testCase==4) {
		cout << "Testiranje na operatorot + vo klasata Par"<<endl;
		double vrednost;
		char kluc [50];
		int n;
		cin >> n;
		Par p [50];
		for (int i=0;i<n;i++){
			cin>>kluc>>vrednost;
			p[i]=Par(kluc,vrednost);
		}
		
		Par p1 = p[0];
		for (int i=1;i<n;i++)
			p1 = (p1 + p[i]);
		
		cout << p1;
	}
	else if (testCase == 5) {
		cout<<"Testiranje na operatorite << i += vo klasata Kolekcija"<<endl;
		Kolekcija k;
		int n;
		double vrednost;
		char kluc [50];
		cin >> n;
		for (int i=0;i<n;i++){
			cin >> kluc >> vrednost;
			Par p = Par (kluc,vrednost);
			k+=p;
			//cout << p;
		}
		
		cout << k;
	}
	else if (testCase == 6){
		cout << "Testiranje na operator == za klasata Kolekcija"<<endl;
		
		Par p1 ("A",1);
		Par p2 ("B",2);
		Par p3 ("B",3);
		Par p4 ("C",4);
		
		Kolekcija k1;
		k1 += p1;
		k1 += p2;
		k1 += p3;
		
		Kolekcija k2;
		k2+=p1;
		k2+=p4;
		
		Kolekcija k3;
		k3+=p1;
		k3+=p4;
		
		Kolekcija k4;
		k4+=p1;
		k4+=p3;
		
		printTrueOrFalse(k1,k2);
		printTrueOrFalse(k1,k3);
		printTrueOrFalse(k1,k4);
		printTrueOrFalse(k2,k3);
		printTrueOrFalse(k2,k4);
		printTrueOrFalse(k3,k4);
		
		
	}
	else {
		cout << "Testiranje na metodot najdi() vo klasata Kolekcija"<<endl;
		Kolekcija k;
		int n;
		double vrednost;
		char kluc [50];
		cin >> n;
		for (int i=0;i<n;i++){
			cin >> kluc >> vrednost;
			Par p = Par (kluc,vrednost);
			k+=p;
			//cout << p;
		}
		
		char toFind[50];
		cin >> toFind;
		k.najdi(toFind);
	}	
	return 0;
	
}