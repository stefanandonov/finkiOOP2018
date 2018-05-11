#include<iostream>
#include<cstring>
using namespace std;

class Runner {
private:
  char *name;
  char country[50];
  int minutes;
  int seconds;
  int numberOfMedals;

  void copy(const Runner &r) {
    name = new char[strlen(r.name) + 1];
    strcpy(name,r.name);
    strcpy(country, r.country);
    minutes = r.minutes;
    seconds = r.seconds;
    numberOfMedals = r.numberOfMedals;
  }
public:
  Runner() {
    name = new char[0];
  }
  Runner(const char* ime, const char * drzava, int minuti, int sekundi, int medali){
    name = new char[strlen(ime) + 1];
    strcpy(name,ime);
    strcpy(country,drzava);
    minutes = minuti;
    seconds = sekundi;
    numberOfMedals = medali;
  }

  Runner(const Runner &r) {
    copy(r);
  }

  Runner & operator = (const Runner &r) {
    if (this != &r) {
      delete [] name;
      copy(r);
    }
    return *this;
  }

  ~Runner() {
    delete [] name;
  }

  Runner & operator++() {
    ++numberOfMedals;
    return *this;
  }

  bool operator != (const Runner &r) {
    return strcmp(country,r.country);
  }

  bool operator < (const Runner &r) {
    if (minutes == r.minutes){
      return seconds < r.seconds;
    }
    else
      return minutes < r.minutes;
  }

  friend ostream & operator << (ostream & out, const Runner &r) {
    out << r.name << " - " << r.country<< " - ";
    out << r.minutes << ":" << r.seconds << " - " << r.numberOfMedals << endl;
    return out;
  }
};

class Race {
private:
  char name[50];
  Runner *runners;
  int number;

  void copy(const Race &r) {
    strcpy(name,r.name);
    number = r.number;
    runners = new Runner[number];
    for (int i=0; i < number; ++i) {
      runners[i] = r.runners[i];
    }
  }

public:
  Race(const char * ime = "") {
    strcpy(name,ime);
    runners = new Runner[0];
    number = 0;
  }

  Race(const Race &r) {
    copy(r);
  }

  Race & operator = (const Race &r) {
    if (this != &r) {
      delete [] runners;
      copy(r);
    }
    return *this;
  }

  ~Race() {
    delete [] runners;
  }

  Race & operator += (const Runner &r) {
    Runner * tmp = new Runner[number + 1];
    for (int i=0; i < number; ++i) {
      tmp[i] = runners[i];
    }
    tmp[number++] = r;
    delete [] runners;
    runners = tmp;
    return *this;
  }

  Race & operator -= (const Runner &r) {
    int newSize = 0;
    for (int i=0; i < number; ++i) {
      if (runners[i] != r){
        newSize ++;
      }
    }
    Runner *tmp = new Runner[newSize];
    newSize = 0;
    for (int i=0; i < number; ++i) {
      if (runners[i] != r){
        tmp[newSize++] = runners[i];
      }
    }
    number = newSize;
    delete [] runners;
    runners = tmp;
    return *this;
  }

  Race & operator ++ () {
    Runner first = runners[0];
    int index = 0;
    for (int i=1; i < number; ++i) {
      if (runners[i] < first) {
        first = runners[i];
        index = i;
      }
    }
    ++runners[index];
    return *this;
  }

  friend ostream & operator << (ostream & out, const Race &r) {
    out << r.name << ":" << endl;
    for (int i=0; i < r.number; ++i){
      out << r.runners[i];
    }
    return out;
  }


};

int main() {

int n;
cin >> n;

char nameRace[50];
cin >> nameRace;

Race race = Race(nameRace);
int m;
cin >> m;

char name[50];
char country[50];
int minutes;
int seconds;
int numberOfMedals;
for (int i=0; i < m; ++i) {
  cin >> name;
  cin >> country;
  cin >> minutes;
  cin >> seconds;
  cin >> numberOfMedals;
  Runner r = Runner(name,country,minutes,seconds,numberOfMedals);
  race += r;
}
cout << race;

if (n == 1) {
  ++race;
  cout << race;
}
else if (n == 2) {
  cin >> name;
  cin >> country;
  cin >> minutes;
  cin >> seconds;
  cin >> numberOfMedals;
  Runner r = Runner(name,country,minutes,seconds,numberOfMedals);
  race -= r;
  cout << race;
}
else if (n == 3) {
  cin >> name;
  cin >> country;
  cin >> minutes;
  cin >> seconds;
  cin >> numberOfMedals;
  Runner r = Runner(name,country,minutes,seconds,numberOfMedals);
  race -= r;
  ++race;
  cout << race;
}
}
