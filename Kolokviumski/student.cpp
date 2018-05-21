#include<iostream>
#include<string.h>
using namespace std;

class StudentKurs{
   protected:
    char ime[30];
    int ocena;
    bool daliUsno;
	static int MAX;
	const static int MIN = 6;
    

   public:
    StudentKurs(char* ime="",int finalenIspit=0){
       strcpy(this->ime,ime);
       this->ocena=finalenIspit;
       this->daliUsno=false;
     }
    void static setMAX(int m){
		MAX=m;
	}
    
    //virtual int ocenkaOpisna(char * opis) = 0;
	
	virtual int ocenka() {
        //cout<<"OCENKA"<<endl;
		return ocena;
	}
    
    bool operator == (char *  ime){
        return strcmp(this->ime,ime)==0;
    }
    
    bool getDaliUsno() {
        return daliUsno;
    }
	
	friend ostream &operator << (ostream &out, StudentKurs &sk){
		out<<sk.ime<<" --- "<<sk.ocena<<endl;
		return out;
	}
    
    static int getMIN() {
        return MIN;
    }
};

int StudentKurs::MAX = 10;

class BadInputException {
	public:
	void message() {
		cout<<"Greshna opisna ocenka"<<endl;
	}
};

char * cleanString (char * string) {
	int count;
	for (int i=0;i<strlen(string);i++)
		if (isalpha(string[i]))
			count++;
	
	char * newString = new char [count+1];
	int j=0;
	for (int i=0;i<strlen(string);i++){
		if (isalpha(string[i])){
			newString[j]=string[i];
			++j;
		}			
	}
    
    return newString;
}

class StudentKursUsno : public StudentKurs {
	private:
	char * opisna;
	
	public:
	StudentKursUsno(char* ime,int finalenIspit) : StudentKurs(ime,finalenIspit){
        this->daliUsno=true;
    }
    
    StudentKursUsno(const StudentKursUsno &sku): StudentKurs(sku){        
        
    }
    
    
	
	int ocenka() {
        //cout<<opisna<<endl;
        //cout<<(strcmp(opisna,"odlicen")==0)<<" "<<(strcmp(opisna,"dobar")==0)<<" "<<(strcmp(opisna,"losho")==0)<<endl;
		if (strcmp(opisna,"odlicen")==0)
			ocena+=2;
		else if (strcmp(opisna,"dobro")==0)
			ocena+=1;
		else if (strcmp(opisna,"losho")==0)
			ocena-=1;
		
		if (ocena>MAX)
			ocena=MAX;
		
		return ocena;
	}
	
	StudentKursUsno &operator += (char * opisnaOcena){
		for (int i=0;i<strlen(opisnaOcena);i++)
			if (!isalpha(opisnaOcena[i]))
				throw BadInputException();
		opisna = new char [strlen(opisnaOcena)];
		strcpy(this->opisna,opisnaOcena);
        
        return *this;
	}
    
   
	
};

//вметни го кодот за StudentKursUsno 


class KursFakultet{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;
    
public:
    KursFakultet(char *naziv, StudentKurs** studenti,int broj ){
      strcpy(this->naziv,naziv);
        
      for (int i=0;i<broj;i++){
        //ako studentot ima usno isprashuvanje
        if (studenti[i]->getDaliUsno()){
            //cout<<studenti[i]->getDaliUsno();
            this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
        }
        else this->studenti[i]=new StudentKurs(*studenti[i]);
          //this->studenti[i]=studenti[i];
      }
      this->broj=broj;
    }
    ~KursFakultet(){
    for (int i=0;i<broj;i++) delete studenti[i];
    }

    void pecatiStudenti() {
		cout<<"Kursot "<<naziv<<" go polozile:"<<endl;
		for (int i=0;i<broj;i++){
			if (studenti[i]->ocenka()>=StudentKurs::getMIN())
				cout<<(*studenti[i]);
		}
	}
    
    void postaviOpisnaOcenka(char * ime, char* opisnaOcenka){
        for (int i=0;i<broj;i++){
            StudentKursUsno * sku = dynamic_cast<StudentKursUsno *>(studenti[i]);
            //cout<<(sku)<<endl;
            if (studenti[i]->getDaliUsno()&&(*studenti[i])==ime){
                try{
                	(*sku)+=opisnaOcenka;
                }
                catch (BadInputException &e){
                    e.message();
                    //cout<<cleanString(opisnaOcenka);
                    (*sku)+=cleanString(opisnaOcenka);
                }
            }
        }
    }
	
	
};

int main(){

StudentKurs **niza;
int n,m,ocenka;
char ime[30],opisna[10];
bool daliUsno;
cin>>n;
niza=new StudentKurs*[n];
for (int i=0;i<n;i++){
   cin>>ime;
   cin>>ocenka;
   cin>>daliUsno;
   if (!daliUsno)
    niza[i]=new StudentKurs(ime,ocenka);
   else
    niza[i]=new StudentKursUsno(ime,ocenka);
}

KursFakultet programiranje("OOP",niza,n);
for (int i=0;i<n;i++) delete niza[i];
delete [] niza;
cin>>m;
    
for (int i=0;i<m;i++){
   cin>>ime>>opisna;
   programiranje.postaviOpisnaOcenka(ime,opisna);
}

StudentKurs::setMAX(9);

programiranje.pecatiStudenti();

}
