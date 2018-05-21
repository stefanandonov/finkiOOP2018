#include<iostream>
#include<string.h>
using namespace std;

//место за вашиот код

class Delo {
    private:
    char ime [50];
    int godina;
    char zemja[50];
    
    public:
    Delo (char * ime="", int godina=0, char * zemja=""){
        strcpy(this->ime,ime);
        this->godina=godina;
        strcpy(this->zemja,zemja);
    }
    
    Delo (const Delo &d){
        strcpy(this->ime,d.ime);
        this->godina=d.godina;
        strcpy(this->zemja,d.zemja);
    }
    
    char * getIme() {return ime;}
    char * getZemja() {return zemja;}
    int getGodina() {return godina;}
    void setIme(char * ime) {strcpy(this->ime,ime);}
    void setZemja(char * zemja) {strcpy(this->zemja,zemja);}
    void setGodina(int godina) {this->godina=godina;}
    
    
    
    bool operator == (Delo &d){
        return strcmp(this->ime,d.ime)==0;
    }
    
};

class Pretstava {
    protected:
    Delo d;
    int karti;
    char datum [15];
    
    public:
    Pretstava(Delo d, int karti, char * datum){
        this->d=d;
        this->karti=karti;
        strcpy(this->datum,datum);
    }
    
    virtual int cena () {
        int c = 0;
        
        if (d.getGodina()>=1900)
            c+=50;
        else if (d.getGodina()>=1800)
            c+=75;
        else if (d.getGodina()<1800)
            c+=100;
            
        if (strcmp(d.getZemja(),"Italija")==0)
            c+=100;
        else if (strcmp(d.getZemja(),"Rusija")==0)
            c+=150;
        else 
            c+=80;
            
        return c;
           
    }
    
    Delo getDelo() {return d;}
    int getKarti () {return karti;}
    
    
};


class Opera : public Pretstava {
    public:
    Opera(Delo d, int karti, char * datum) : Pretstava(d,karti,datum){}
    
    int cena() {
        return Pretstava::cena();
    }
    
};

int prihod (Pretstava ** pretstavi, int n) {
    int vkupno=0;
    for (int i=0;i<n;i++)
        vkupno+=pretstavi[i]->cena()*pretstavi[i]->getKarti();
    return vkupno;
}

int brojPretstaviNaDelo (Pretstava ** pretstavi, int n, Delo d){
    int count = 0;
    for (int i=0;i<n;i++){
        if (pretstavi[i]->getDelo() == d)
            count++;
    }
    return count;
}

class Balet : public Pretstava{
    private:
    static int cenaBalet;
    
    public:
    Balet(Delo d, int karti, char * datum) : Pretstava(d,karti,datum){}
    
    static void setCenaBalet(int cena){
        cenaBalet = cena;
    }
    
    int cena() {
        return cenaBalet + Pretstava::cena();
    }
};

int Balet::cenaBalet = 150;

//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;
    
    switch(test_case){
    case 1:
    //Testiranje na klasite Opera i Balet
    {
        cout<<"======TEST CASE 1======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->getDelo().getIme()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->getDelo().getIme()<<endl;
    }break;
        
    case 2:
    //Testiranje na  klasite Opera i Balet so cena
    {
        cout<<"======TEST CASE 2======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->cena()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->cena()<<endl;
    }break;
    
    case 3:
    //Testiranje na operator ==
    {
        cout<<"======TEST CASE 3======="<<endl;
        Delo f1=readDelo();
        Delo f2=readDelo();
        Delo f3=readDelo();
        
        if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
        if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
    
    }break;
    
    case 4:
    //testiranje na funkcijata prihod
    {
        cout<<"======TEST CASE 4======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        
        }
        cout<<prihod(pole,n);
    }break;
    
    case 5:
    //testiranje na prihod so izmena na cena za 3d proekcii
    {
        cout<<"======TEST CASE 5======="<<endl;
        int cenaBalet;
        cin>>cenaBalet;
        Balet::setCenaBalet(cenaBalet);
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }
        cout<<prihod(pole,n);
        }break;
        
    case 6:
    //testiranje na brojPretstaviNaDelo
    {
        cout<<"======TEST CASE 6======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }
        
        Delo f=readDelo();
        cout<<brojPretstaviNaDelo(pole,n,f);
    }break;
    
    };


return 0;
}
