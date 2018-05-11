#include<iostream>
using namespace std;

class Kvadrat {
	protected:
	double a;
	
	void copy(const Kvadrat &k){
		this->a=k.a;
	}
	
	public:
	Kvadrat(double a=0.0){
		this->a=a;
	}
	
	Kvadrat (const Kvadrat &k){
		copy(k);
	}
	
	double perimetar () {
		return 4*a;
	}
	
	double plostina() {
		return a*a;
	}
	
	void pecati() {
		cout<<"Kvadrat so dolzina a="<<a<<" ima plostina P="<<plostina()<<" i perimetar L="<<perimetar()<<endl;
	}
};

class Pravoagolnik : public Kvadrat{
	private:
	double x;
	double y;
	
	public:
	Pravoagolnik() : Kvadrat() {
		x=0.0;
		y=0.0;
	}
	
	Pravoagolnik (const Kvadrat &k,double x, double y) : Kvadrat(k) {
		this->x=x;
		this->y=y;
	}
	
	Pravoagolnik (const Pravoagolnik &p) {
		this->a=p.a;
		this->x=p.x;
		this->y=p.y;
	}
	
	double perimetar () {
		return Kvadrat::perimetar() + 2*x + 2*y;
	}
	
	double plostina() {
		return Kvadrat::plostina() + a*y + a*x + x*y;
	}
	
	void pecati() {
		if (x==y){
			a+=x;
			Kvadrat::pecati();
			return;
		}
		
		cout<<"Pravoagolnik so strani: "<<a+x<<" i "<<a+y<<" ima plostina P="<<plostina()<<" i perimetar L="<<perimetar()<<endl;
	}
	
	
	
	
};
int main() {
	int n;
    double a,x,y;
	Kvadrat * kvadrati;
	Pravoagolnik * pravoagolnici;
	
	cin>>n;
    
    kvadrati = new Kvadrat [n];
    pravoagolnici = new Pravoagolnik [n];
    
	for (int i=0;i<n;i++){
		cin>>a;
        
		kvadrati[i] = Kvadrat(a);
	}
	
	for (int i=0;i<n;i++){
		cin>>x>>y;
        
		pravoagolnici[i]=Pravoagolnik(kvadrati[i],x,y);
	}
	
	int testCase;
	cin>>testCase;
    
	if (testCase==1){
		cout<<"===Testiranje na klasata Kvadrat==="<<endl;
		for (int i=0;i<n;i++)
			kvadrati[i].pecati();
	}
	else {
		cout<<"===Testiranje na klasata Pravoagolnik==="<<endl;
		for (int i=0;i<n;i++)
			pravoagolnici[i].pecati();
	}
}