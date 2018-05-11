#include <iostream>
#include <cstring>

using namespace std;

enum Tip {
    LINUX, UNIX, WINDOWS
};

class OperativenSistem {
private:
    char *ime;
    float verzija;
    Tip tip;
    float golemina;

    void kopiraj(const OperativenSistem &kopija) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, kopija.ime);
        this->verzija = kopija.verzija;
        this->tip = kopija.tip;
        this->golemina = kopija.golemina;
    }

public:

    OperativenSistem() {
        this->ime = new char[0];
        this->verzija = 0;
        this->tip = LINUX;
        this->golemina = 0;
    }

    OperativenSistem(const char *ime, const float verzija, const Tip tip, const float golemina) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        this->verzija = verzija;
        this->tip = tip;
        this->golemina = golemina;
    }

    bool ednakviSe(const OperativenSistem &sporedba) {
        return strcmp(this->ime, sporedba.ime) == 0&&this->verzija == sporedba.verzija&&tip == sporedba.tip &&
               golemina == sporedba.golemina;
    }

    int sporediVerzija(const OperativenSistem &sporedba) {
        if (verzija == sporedba.verzija) return 0;
        if (verzija > sporedba.verzija) return 1;
        return -1;
    }

    bool istaFamilija(const OperativenSistem &sporedba) {
        return strcmp(ime, sporedba.ime) == 0 && tip == sporedba.tip;
    }

    ~OperativenSistem() {
        delete[] ime;
    }

    OperativenSistem &operator=(const OperativenSistem &operativenSistem) {
        if (&operativenSistem != this) {
            delete[] ime;
            kopiraj(operativenSistem);
        }
        return *this;
    }

    OperativenSistem(const OperativenSistem &kopija) {
        kopiraj(kopija);
    }

    void pecati(){
        cout<<"Ime: "<<ime<<" Verzija: "<<verzija<<" Tip: "<<tip<<" Golemina:"<<golemina<<"GB"<<endl;
    }

};

class Repozitorium {
private:
    char ime[20];
    int brojOperativniSistemi;
    OperativenSistem *operativniSistemi;
public:

    Repozitorium(const char *ime) {
        strcpy(this->ime, ime);
        this->brojOperativniSistemi = 0;
        this->operativniSistemi = 0;
    }

    void izbrishi(const OperativenSistem &operativenSistem) {
        int index = -1;
        for (int i = 0; i < brojOperativniSistemi; i++) {
            if (operativniSistemi[i].ednakviSe(operativenSistem)) {
                index = i;
            }
        }
        if (index != -1) {
            OperativenSistem *temp = operativniSistemi;
            this->operativniSistemi = new OperativenSistem[brojOperativniSistemi - 1];
            for (int i = 0, j = 0; i < brojOperativniSistemi; i++) {
                if (i != index) {
                    operativniSistemi[j++] = temp[i];
                }
            }
            brojOperativniSistemi--;
        }
    }

    void dodadi(const OperativenSistem &nov) {
        for (int i = 0; i < brojOperativniSistemi; i++) {
            if (operativniSistemi[i].istaFamilija(nov) && operativniSistemi[i].sporediVerzija(nov)<0) {
                operativniSistemi[i] = nov;
                return;
            }
        }

        OperativenSistem *temp = operativniSistemi;
        this->operativniSistemi = new OperativenSistem[brojOperativniSistemi + 1];
        for (int i = 0; i < brojOperativniSistemi; i++) {
            operativniSistemi[i] = temp[i];
        }
        operativniSistemi[brojOperativniSistemi++] = nov;
    }

    void pecatiOperativniSistemi(){
        cout<<"Repozitorium: "<<ime<<endl;
        for (int i=0; i<brojOperativniSistemi; i++){
            operativniSistemi[i].pecati();
        }
    }

};

int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }
    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
}