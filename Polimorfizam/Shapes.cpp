#include <iostream>
#include <cmath>
using namespace std;


//abstract class
class Shape{

protected:

	int side;

public:

	Shape(){}

	Shape(int a) : side(a){}

	//pure virtual method; makes the class abstract
	virtual double plostina() = 0;

	virtual void pecati() = 0;

	virtual int getType() = 0;


};

//equilateral triangle
class Triangle : public Shape{

public:

	Triangle(int a) : Shape(a){}

	double plostina(){

		return (sqrt(3)/4) * side * side;
	}

	void pecati(){

		cout << "Triagolnik so plostina = " << plostina() << endl;
	}

	int getType(){

		return 3;
	}

};


class Square : public Shape{

public:

	Square(int a) : Shape(a){}

	double plostina(){

		return side * side;
	}

	void pecati(){

		cout << "Kvadrat so plostina = " << plostina() << endl;
	}

	int getType(){

		return 1;
	}


};

class Circle : public Shape{


public:

	Circle(int a) : Shape(a){}

	double plostina(){

		return 3.14 * side * side;
	}

	void pecati(){

		cout << "Krug so plostina = " << plostina() << endl;
	}

	int getType(){

		return 2;
	}


};

void checkNumTypes(Shape** niza, int n){


	int squares = 0;
	int circles = 0;
	int triangles = 0;

	for(int i = 0; i < n; ++i){

		if(niza[i]->getType() == 1){

			squares++;

		} else if(niza[i]->getType() == 2){

			circles++;

		} else if(niza[i]->getType() == 3){

			triangles++;
		}
	}
	cout << "Broj na kvadrati vo nizata = " << squares << endl;
	cout << "Broj na krugovi vo nizata = " << circles << endl;
	cout << "Broj na triagolnici vo nizata = " << triangles << endl;
}

int main(){


	Shape** niza;

	int n;
	cin >> n;

	niza = new Shape*[n];

	int classType;
	int side;

	for(int i = 0; i < n; ++i){

		cin >> classType;
		cin >> side;
		if (classType == 1){

			niza[i] = new Square(side);

		} else if(classType == 2){

			niza[i] = new Circle(side);

		} else if(classType == 3){

			niza[i] = new Triangle(side);
		}
	}

	for(int i = 0; i < n; ++i){

		niza[i]->pecati();
	}

	checkNumTypes(niza, n);


	return 0;
}