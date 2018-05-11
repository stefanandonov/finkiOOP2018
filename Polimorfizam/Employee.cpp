#include<iostream>
#include<cstring>

using namespace std;

class Employee {

protected:
  char name[50];
  int age;
  int experience;

public:
  Employee(const char * ime, int godini, int iskustvo) {
    strcpy(name,ime);
    age = godini;
    experience = iskustvo;
  }

  int getAge() const {
    return age;
  }

  virtual double plata() const = 0;
  virtual double bonus() const{
    return 0;
  }

  virtual ~Employee() {}
};

bool operator == (const Employee &emp1,const Employee &emp2) {
  return emp1.getAge() == emp2.getAge()&&emp1.bonus() == emp2.bonus();
}
class SalaryEmployee : public Employee {
private:
  double basicSalary;
  static int br;

public:
  SalaryEmployee(const char * ime, int godini, int iskustvo, int osnovica)
  : Employee(ime,godini, iskustvo) {
    basicSalary = osnovica;
    br++;
  }

  static int getStatic() {
    return br;
  }

  double bonus() const{
    return (experience * basicSalary) / 100.0;
  }

  double plata() const{
    return basicSalary + bonus();
  }
};

int SalaryEmployee :: br = 0;

class HourlyEmployee : public Employee {
private:
  int hoursWorked;
  double hourlyPay;
  static int br;
public:
  HourlyEmployee(const char * ime, int godini, int iskustvo, int casovi, double saatnica)
  : Employee(ime, godini, iskustvo) {
    hoursWorked = casovi;
    hourlyPay = saatnica;
    br++;
  }

  static int getStatic() {
    return br;
  }

  double bonus()const{
    if (hoursWorked > 320) {
      return (hoursWorked - 320) * 0.5 * hourlyPay;
    }
    else
    return 0;
  }
  double plata() const{
    return hoursWorked * hourlyPay + bonus();
  }

};

int HourlyEmployee :: br = 0;

class Freelancer : public Employee {
private:
  int num;
  double projects[10];
  static int br;
public:
  Freelancer(const char * ime, int godini, int iskustvo, int broj, double proekti[])
  : Employee(ime,godini,iskustvo) {
    num = broj;
    for (int i=0; i < num; ++i) {
      projects[i] = proekti[i];
    }
    br++;
  }

  static int getStatic() {
    return br;
  }

  double bonus() const{
      if (num > 5) {
        return (num - 5) * 1000.0;
      }
      else
        return 0;
  }

  double plata() const{
    double p = 0;
    for (int i=0; i < num; ++i) {
      p += projects[i];
    }
    return p + bonus();
  }
};

int Freelancer :: br = 0;

class Company {
private:
  char name[50];
  int number;
  Employee ** employees;
public:
  Company(const char* ime) {
    number = 0;
    strcpy(name,ime);
    employees = new Employee*[0];
  }

  Company & operator += (Employee *emp) {
    Employee ** tmp = new Employee*[number + 1];

    for (int i=0; i < number; ++i) {
      tmp[i] = employees[i];
    }
    tmp[number++] = emp;
    delete [] employees;
    employees = tmp;
    return * this;
  }

  double vkupnaPlata() {
    double plata = 0;
    for (int i=0; i < number; ++i) {
      plata += employees[i] -> plata();
    }
    return plata;
  }

  void pecatiRabotnici() {
    cout << "Vo kompanijata " << name << " rabotat:" <<endl;
    cout << "Salary employees: " << SalaryEmployee::getStatic() << endl;
    cout << "Hourly employees: " << HourlyEmployee::getStatic() << endl;
    cout << "Freelancers: " << Freelancer::getStatic() << endl;
  }

  double filtriranaPlata(Employee  *emp) {
    double plata = 0;
    for (int i=0; i < number; ++i) {
      if (*emp == *employees[i]) {
        plata += employees[i] -> plata();
      }
    }
    return plata;
  }

  ~Company() {
    for (int i=0; i < number; ++i) {
      delete employees[i];
    }
    delete [] employees;
  }

};

int main() {

char name[50];
cin >> name;
Company c(name);

int n;
cin >> n;

char employeeName[50];
int age;
int experience;
int type;

for (int i=0; i <n; ++i) {
  cin >> type;
  cin >> employeeName >> age >> experience;

  if (type == 1) {
    int basicSalary;
    cin >> basicSalary;
    c += new SalaryEmployee(employeeName, age, experience, basicSalary);
  }

  else if (type == 2) {
    int hoursWorked;
    int hourlyPay;
    cin >> hoursWorked >> hourlyPay;
    c += new HourlyEmployee(employeeName, age, experience, hoursWorked, hourlyPay);
  }

  else {
    int numProjects;
    cin >> numProjects;
    double projects[10];
    for (int i=0; i < numProjects; ++i) {
      cin >> projects[i];
    }
    c += new Freelancer(employeeName, age, experience, numProjects, projects);
  }
}

c.pecatiRabotnici();
cout << "Vkupnata plata e: " << c.vkupnaPlata() << endl;
Employee * emp = new HourlyEmployee("Petre_Petrov",31,6,340,80);
cout << "Filtriranata plata e: " << c.filtriranaPlata(emp);

delete emp;
}
