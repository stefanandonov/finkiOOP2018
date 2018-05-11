#include<iostream>
#include<cstring>
using namespace std;

class Lekar {
	protected:
	int faksimil;
	char ime [15];
	char prezime [15];
	double osnovnaPlata;
	
	void copy (const Lekar &l){
		this->faksimil=l.faksimil;
		strcpy(this->ime,l.ime);
		strcpy(this->prezime,l.prezime);
		this->osnovnaPlata=l.osnovnaPlata;
	}
	
	public:
	Lekar(int faksimil=0, char * ime="", char * prezime="", double osnovnaPlata=0.0) {
		this->faksimil=faksimil;
		strcpy(this->ime,ime);
		strcpy(this->prezime,prezime);
		this->osnovnaPlata=osnovnaPlata;
	}
	
	Lekar (const Lekar &l){
		copy(l);
	}
	
	Lekar &operator = (const Lekar &l){
		if (this!=&l){
			copy(l);
		}
		return *this;
	}
	
	void pecati() {
		cout<<faksimil<<": "<<ime<<" "<<prezime<<endl;
	}
	
	double plata() {
		return osnovnaPlata;
	}	
};

class MaticenLekar : public Lekar {
	int pacienti;
	double * kotizacii;
	
	void copy(const MaticenLekar &ml){
        this->faksimil = ml.faksimil;
        strcpy(this->ime,ml.ime);
        strcpy(this->prezime,ml.prezime);
        this->osnovnaPlata=ml.osnovnaPlata;
		this->pacienti = ml.pacienti;
		this->kotizacii = new double [this->pacienti];
		for (int i=0;i<pacienti;i++)
			this->kotizacii[i]=ml.kotizacii[i];
	}
	
	public:
    
    MaticenLekar () : Lekar() {
        this->pacienti = 0;
        this->kotizacii = new double[0];
    }
	MaticenLekar (Lekar l, int pacienti, double * kotizacii) : Lekar(l){
		this -> pacienti = pacienti;
        
		this->kotizacii = new double [pacienti];
		for (int i=0;i<pacienti;i++)
			this->kotizacii[i]=kotizacii[i];
	}
	
	MaticenLekar (const MaticenLekar &ml){
		copy(ml);
	}
	
	MaticenLekar &operator = (const MaticenLekar &ml){
		if (this!=&ml){
			delete [] kotizacii;
			copy(ml);
		}
		
		return *this;
	}
	
	double average() {
		double sum = 0.0;
		for (int i=0;i<pacienti;i++)
			sum+=kotizacii[i];
		return sum/pacienti*1.0;
	}
	
	void pecati() {
		Lekar::pecati();
		cout<<"Prosek na kotizacii: "<<average()<<endl;
	}
	
	double plata() {
		return Lekar::plata() + 0.3 * average();
	}
	
	
	
	~MaticenLekar() {
		delete [] kotizacii;
	}
	
	
};

int main() {
	int n;
	cin>>n;
	int pacienti;
	double kotizacii[100];
	int faksimil;
	char ime [20];
	char prezime [20];
	double osnovnaPlata;
	
	Lekar * lekari = new Lekar [n];
	MaticenLekar * maticni = new MaticenLekar [n];
	
	for (int i=0;i<n;i++){
		cin >> faksimil >> ime >> prezime >> osnovnaPlata;
		lekari[i] = Lekar(faksimil,ime,prezime,osnovnaPlata);		
	}
	
	for (int i=0;i<n;i++){
		cin >> pacienti;
		for (int j=0;j<pacienti;j++){
			cin >> kotizacii[j];
            //cout << kotizacii[j]<<endl;
		}
		maticni[i]=MaticenLekar(lekari[i],pacienti,kotizacii);
        //cout << pacienti << endl;
	}
	
	int testCase;
	cin>>testCase;
    //cout<<testCase;
	
	if (testCase==1){
		cout<<"===TESTIRANJE NA KLASATA LEKAR==="<<endl;
		for (int i=0;i<n;i++){
			lekari[i].pecati();
			cout<<"Osnovnata plata na gorenavedeniot lekar e: "<<lekari[i].plata()<<endl;
		}
	}
	else {
		cout<<"===TESTIRANJE NA KLASATA MATICENLEKAR==="<<endl;
		for (int i=0;i<n;i++){
			maticni[i].pecati();
			cout<<"Platata na gorenavedeniot maticen lekar e: "<<maticni[i].plata()<<endl;
		}
	}
	
	delete [] lekari;
	delete [] maticni;
	
	return 0;
}