#include<iostream>
using namespace std;

class MyVector {

private:
  int a[15];
  int size;
public:
  MyVector(){
    size = 0;
  }

  MyVector(int niza[], int br) {
    size = br;
    for (int i=0; i < br; ++i) {
      a[i] = niza[i];
    }
  }

  friend istream & operator >> (istream & in, MyVector & vec) {
    in >> vec.size;
    for (int i=0; i < vec.size; ++i) {
      in >> vec.a[i];
    }
    return in;
  }

  friend ostream & operator << (ostream & out, const MyVector & vec) {
    out << "<";
    for (int i=0; i < vec.size - 1; ++i) {
      out << vec.a[i] << ",";
    }
    out << vec.a[vec.size - 1] << ">" << endl;
    return out;
  }

  MyVector & operator--() {
    for (int i=0; i < size; ++i) {
      if (a[i] > 0)
        --a[i];
    }
    return *this;
  }

  MyVector operator++(int) {
    MyVector temp = *this;
    for (int i=0; i < size; ++i){
      if (a[i] < 0)
        a[i]++;
    }
    return temp;
  }

  MyVector & operator -= (const MyVector & vec){
    for (int i=0; i < size; ++i) {
      a[i] -= vec.a[i];
    }
    return *this;
  }

  int operator * (const MyVector & vec) {
    int temp = 0;
    for (int i=0; i < size; ++i) {
      temp += a[i] * vec.a[i];
    }
    return temp;
  }

  bool operator <= (const MyVector & vec) {
    int tempA = 0;
    int tempB = 0;
    for (int i=0; i < size; ++i) {
      tempA += a[i];
    }
    for (int i=0; i < vec.size; ++i) {
      tempB += vec.a[i];
    }
    return tempA <= tempB;
  }

  int operator [](int index) {
    if (index < 0 || index >= size){
      cout << "Index out of bounds" << endl;
      return -1;
    }
    else
    return a[index];
  }

};

int main() {
int n;

cin >> n;
if (n == 1) {
  cout << "Testiranje na operatorite >> i <<" << endl;
  cout << "==============================\n";
  MyVector a;
  MyVector b;
  cin >> a;
  cin >> b;
  cout << a;
  cout << b;
}
else if (n == 2) {
  cout << "Testiranje na operatorot -="<< endl;
  cout << "==============================\n";
  int m;
  int niza[15];
  cin >> m;
  for (int i=0; i < m; ++i){
    cin >> niza[i];
  }
  MyVector a(niza,m);
  for (int i=0; i < m; ++i) {
    cin >> niza[i];
  }
  MyVector b(niza,m);
  a -= b;
  cout << a;
}
else if (n == 3) {
  cout << "Testiranje na operatorot *"<< endl;
  cout << "==============================\n";
  int m;
  int niza[15];
  cin >> m;
  for (int i=0; i < m; ++i){
    cin >> niza[i];
  }
  MyVector a(niza,m);
  for (int i=0; i < m; ++i) {
    cin >> niza[i];
  }
  MyVector b(niza,m);
  cout << a * b;
}
else if (n == 4){
  cout << "Testiranje na operatorot <="<< endl;
  cout << "==============================\n";
  int m;
  int l;
  int niza[15];
  cin >> m;
  for (int i=0; i < m; ++i){
    cin >> niza[i];
  }
  MyVector a(niza,m);
  cin >> l;
  for (int i=0; i < l; ++i) {
    cin >> niza[i];
  }
  MyVector b(niza,l);
  cout << (a <= b);
}
else if (n == 5){
  cout << "Testiranje na operatorot []"<< endl;
  cout << "==============================\n";
  int m;
  int niza[15];
  cin >> m;
  for (int i=0; i < m; ++i){
    cin >> niza[i];
  }
  MyVector a(niza,m);
  for (int i=0; i < m; ++i) {
    cin >> niza[i];
  }
  MyVector b(niza,m);
  cout << a[2];
  cout << endl;
  cout << b[3];
}
else if (n == 6) {
  cout << "Testiranje na operatorot --"<< endl;
  cout << "==============================\n";
  int m;
  int niza[15];
  cin >> m;
  for (int i=0; i < m; ++i){
    cin >> niza[i];
  }
  MyVector a(niza,m);
  --a;
  cout << a;
}
else if (n == 7) {
  cout << "Testiranje na operatorot ++"<< endl;
  cout << "==============================\n";
  int m;
  int niza[15];
  cin >> m;
  for (int i=0; i < m; ++i){
    cin >> niza[i];
  }
  MyVector a(niza,m);
  MyVector b = a++;
  cout << a;
  cout << b;
}
}
