#include<iostream>
#include<cstring>

using namespace std;

class InvalidDateException {
	private:
	int day;
	int month;
	int year;
	
	public:
	InvalidDateException(int d, int m, int y) {
		day=d;
		month=m;
		year=y;
	}
	
	void message() {
		cout<<"Invalid Date "<<day<<"/"<<month<<"/"<<year<<endl;
	}
};

class NotSupportedCurrencyException {
	private:
	char currency [3];
	
	public:
	NotSupportedCurrencyException(char * c){
		strcpy(currency,c);
	}
	
	void message() {
		cout<<currency<<" is not a supported currency"<<endl;
	}
};

class Transakcija {
	protected:
	int den;
	int mesec;
	int godina;
	double iznos;
	static double EUR;
	static double USD;
	
	public:
    
	Transakcija(int den, int mesec, int godina, double iznos) {
		if (den<1 || den > 31 || mesec<1 || mesec > 12)
			throw InvalidDateException(den,mesec,godina);
		this->den=den;
		this->mesec=mesec;
		this->godina=godina;
		this->iznos=iznos;
	}
	
	Transakcija(const Transakcija &t){
		this->den=t.den;
		this->mesec=t.mesec;
		this->godina=t.godina;
		this->iznos=t.iznos;
	}
    
    static void setEUR(double eur) {
        Transakcija::EUR=eur;
    }
    
    static void setUSD(double usd){
        Transakcija::USD=usd;
    }
    
    static double getEUR() {
    	return Transakcija::EUR;
    }
    
    static double getUSD() {
        return Transakcija::USD;
    }
	
	virtual double voDenari() = 0;
	virtual double voEvra() = 0;
	virtual double voDolari() = 0;
	virtual void pecati() = 0;	
};

double Transakcija::EUR = 61.0;
double Transakcija::USD = 50.0;

class DenarskaTransakcija : public Transakcija {
	public:
	DenarskaTransakcija(int den, int mesec, int godina, double iznos) 
	: Transakcija(den,mesec,godina,iznos){		
	}
	
	double voDenari() {
		return this->iznos;
	}
	
	double voEvra() {
		return this->iznos/EUR;
	}
	
	double voDolari() {
		return this->iznos/USD;
	}
	
	void pecati() {
		cout<<this->den<<"/"<<this->mesec<<"/"<<this->godina<<" "<<this->iznos<<" MKD"<<endl;
		//cout<<" MKD"<<endl;
	}
};

class DeviznaTransakcija : public Transakcija {
	private:
	char valuta [4];
	
	public: 
	DeviznaTransakcija(int den, int mesec, int godina, double iznos, char * valuta)
	: Transakcija(den,mesec,godina,iznos) {
		//cout<<valuta<<endl;
		if (strcmp(valuta,"USD")==0 || strcmp(valuta,"EUR")==0)
			strcpy(this->valuta,valuta);
		else
			throw NotSupportedCurrencyException(valuta);
	}
	
	double voDenari() {
		if (strcmp(valuta,"EUR")==0)
			return this->iznos*EUR;
		else
			return this->iznos * USD;
	}
	
	double voEvra() {
		if (strcmp(valuta,"EUR")==0)
			return this->iznos;
		else 
			return (this->iznos * USD) / EUR;
	}
	
	double voDolari() {
		if (strcmp(valuta,"USD")==0)
			return this->iznos;
		else 
			return (this->iznos * EUR) / USD;
	}
	
	void pecati () {
		if (strcmp(valuta,"EUR")==0)
			cout<<this->den<<"/"<<this->mesec<<"/"<<this->godina<<" "<<this->iznos<<" EUR"<<endl;
		else
			cout<<this->den<<"/"<<this->mesec<<"/"<<this->godina<<" "<<this->iznos<<" USD"<<endl;
	}
};

class Smetka {
	private:
	Transakcija ** transakcii;
	int brTr;
	double saldo;
	char brSmetka [15];
	
	public: 
	Smetka(char * brSmetka, int saldo){
		strcpy(this->brSmetka,brSmetka);
		this->saldo=saldo;
		transakcii = new Transakcija * [0];
		brTr=0;	
	}
	
	Smetka &operator += (Transakcija * t) {
		Transakcija ** pom = new Transakcija * [brTr+1];
		for (int i=0;i<brTr;i++)
			pom[i]=transakcii[i];
		pom[brTr++]=t;
		delete [] transakcii;
		transakcii = pom;
		
		return *this;
	}
    
    ~Smetka() {
        for (int i=0;i<brTr;i++) {
            //delete transakcii[i];
        }
        delete [] transakcii;
    }
    
	
	void izvestajVoDenari() {
		double sum = this->saldo;
		for (int i=0;i<brTr;i++)
			sum+=transakcii[i]->voDenari();
		
		cout<<"Korisnikot so smetka: "<<brSmetka<<" ima momentalno saldo od "<<sum<<" MKD"<<endl;
	}
	
	void izvestajVoEvra() {
		double sum = this->saldo / Transakcija::getEUR();
		for (int i=0;i<brTr;i++)
			sum+=transakcii[i]->voEvra();
		
		cout<<"Korisnikot so smetka: "<<brSmetka<<" ima momentalno saldo od "<<sum<<" EUR"<<endl;
	}
	
	void izvestajVoDolari() {
		double sum = this->saldo / Transakcija::getUSD();
        //cout<<Transakcija::getUSD();
		for (int i=0;i<brTr;i++)
			sum+=transakcii[i]->voDolari();
		
		cout<<"Korisnikot so smetka: "<<brSmetka<<" ima momentalno saldo od "<<sum<<" USD"<<endl;
	}
	
	void pecatiTransakcii() {
        for (int i=0;i<brTr;i++){
            transakcii[i]->pecati();
            //cout<<transakcii[i]->voDenari()<<" "<<transakcii[i]->voEvra()<<" "<<transakcii[i]->voDolari()<<endl;
        }
			
	}
};

int main () {
	
	Smetka s ("300047024112789",1500);
	
	int n, den, mesec, godina, tip;
	double iznos;
	char valuta [3];
	
	cin>>n;
    cout<<"===VNESUVANJE NA TRANSAKCIITE I SPRAVUVANJE SO ISKLUCOCI==="<<endl;
	for (int i=0;i<n;i++){
		cin>>tip>>den>>mesec>>godina>>iznos;
		try{
		if (tip==2){
			cin>>valuta;
			Transakcija * t = new DeviznaTransakcija(den,mesec,godina,iznos,valuta);
			s+=t;
            //delete t;
		}
		else {
			Transakcija * t = new DenarskaTransakcija(den,mesec,godina,iznos);
			s+=t;
            //delete t;
		}
		}
		catch (InvalidDateException &e){
			e.message();
		}
		catch (NotSupportedCurrencyException &e){
			e.message();
		}
        
        
		
		//s.pecatiTransakcii();
			
	}
    cout<<"===PECHATENJE NA SITE TRANSAKCII==="<<endl;
    s.pecatiTransakcii();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.izvestajVoDenari();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO EVRA==="<<endl;
    s.izvestajVoEvra();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DOLARI==="<<endl;
    s.izvestajVoDolari();
    
    cout<<"\n===PROMENA NA KURSOT NA EVROTO I DOLAROT===\n"<<endl;
    
        
    double newEUR, newUSD;
    cin>>newEUR>>newUSD;
    Transakcija::setEUR(newEUR);
    Transakcija::setUSD(newUSD);
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.izvestajVoDenari();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO EVRA==="<<endl;
    s.izvestajVoEvra();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DOLARI==="<<endl;
    s.izvestajVoDolari();
    
	
	
	return 0;
}