#include<cstring>
#include<iostream>
using namespace std;

class Secret {
	public:
	virtual double simpleEntropy() const = 0;
	virtual int total() const = 0;
};

class DigitSecret : public Secret{
	private:
	int digits [100] ;
	int length;
	
	public:
	DigitSecret(int * digits, int length){
		this->length=length;
		for (int i=0;i<length;i++)
			this->digits[i]=digits[i];
	}
	
	int total() const  {
		return length;
	}
	
	double simpleEntropy() const {
		double different=0.0;
		int count = 0;
		
		for (int i=0;i<length;i++){
			count = 0;
			for (int j=0;j<length;j++){
				if ((i!=j)&&(digits[i]==digits[j]))
					count++;
			}
			if (count==0)
				different+=1.0;
		}
		
		return different/total();
	}
	
	friend ostream &operator << (ostream &out, const DigitSecret &ds){
		for (int i=0;i<ds.total();i++)
			out<<ds.digits[i];
		out<<" Simple entropy: " << ds.simpleEntropy() << " Total: "<<ds.total();
		return out;
	}
};

class CharSecret : public Secret{
	private:
	char chars [100] ;
	int length;
	
	public:
	CharSecret(char * chars){
		for (int i=0;i<strlen(chars);i++)
			this->chars[i]=chars[i];
		this->length=strlen(chars);
	}
	
	int total() const {
		return length;
	}
	
	double simpleEntropy() const {
		double different=0.0;
		int count = 0;
		
		for (int i=0;i<length;i++){
			count = 0;
			for (int j=0;j<length;j++){
				if ((i!=j)&&(chars[i]==chars[j]))
					count++;
			}
			if (count==0)
				different+=1.0;
		}
		
		return different/total();
	}
	friend ostream &operator << (ostream &out, const CharSecret &cs){
		for (int i=0;i<cs.total();i++)
			out<<cs.chars[i];
		out<<" Simple entropy: " << cs.simpleEntropy() << " Total: "<<cs.total();
		return out;
	}
	
};

bool operator ==(const Secret &s1, const Secret &s2){
		return s1.total()==s2.total() && s1.simpleEntropy()==s2.simpleEntropy();
}

bool operator !=(const Secret &s1, const Secret &s2){
		return s1.total()!=s2.total() || s1.simpleEntropy()!=s2.simpleEntropy();
}


void process (Secret ** secrets, int n){
		double max = -1;
		int idx = -1;
		for (int i=0;i<n;i++){
			if (secrets[i]->simpleEntropy()>max){
				max=secrets[i]->simpleEntropy();
				idx=i;
			}
		}
		
		DigitSecret * ds = dynamic_cast<DigitSecret *>(secrets[idx]);
		if (ds!=0){
			cout<<*ds;
		}
		
		CharSecret * cs = dynamic_cast<CharSecret *>(secrets[idx]);
		if (cs!=0){
			cout<<*cs;
		}
}

void printAll(Secret ** secrets, int n){
    for (int i=0;i<n;i++){
        DigitSecret * ds = dynamic_cast<DigitSecret *>(secrets[i]);
		if (ds!=0){
			cout<<*ds<<endl;
		}
		
		CharSecret * cs = dynamic_cast<CharSecret *>(secrets[i]);
		if (cs!=0){
			cout<<*cs<<endl;
		}
    }
}



int main() {
    int n;
    cin >> n;
    if(n == 0) {
		cout << "Constructors" << endl;
		int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        cout << "OK" << endl;
    } else if(n == 1) {
  		cout << "operator <<" << endl;
		int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        cout << ds << endl;
        cout << cs << endl;
    }  else if(n == 2) {
  		cout << "== and !=" << endl;
		int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        CharSecret css("abcabc");
        cout << (ds == cs) << endl;
        cout << (cs != ds) << endl;
        cout << (cs == css) << endl;
        cout << (cs != css) << endl;
    } else if(n == 3) {
  		cout << "Secret processor" << endl;
		int numbers1 [] = {1,2,3,4,5,6,4,3,2,1,1,2,3,4,5};
        DigitSecret ds1(numbers1,15);
		int numbers2 [] = {1,2,3,4,5,0,0,0,5,5,4,4,3,3,2};
        DigitSecret ds2(numbers2,15);
		int numbers3 [] = {1,0,9,4,3,8,4,0,9,3,1,4,3,2,1,4,4,3,7,2};
        DigitSecret ds3(numbers3,20);
        CharSecret cs1("fhdaieowujkfjdsafjdsakjhueiqoyroq");
        CharSecret cs2("nvzcfsadrqipqhfjdfncxoqw");
        CharSecret cs3("uyoihfdsanmqeqrzvdhfeqyrq");
        Secret** s = new Secret*[6];
        s[0] = &ds1;
        s[1] = &ds2;
        s[2] = &ds3;
        s[3] = &cs1;
        s[4] = &cs2;
        s[5] = &cs3;
        process(s,6);
        delete [] s;
    }
    else if (n==4){
        cout << "Print all secrets" << endl;
		int numbers1 [] = {1,2,3,4,5,5,4,3,2,1,1,2,3,4,5};
        DigitSecret ds1(numbers1,15);
		int numbers2 [] = {1,2,3,4,5,0,0,0,5,5,4,4,3,3,2};
        DigitSecret ds2(numbers2,15);
		int numbers3 [] = {1,0,9,4,3,8,4,0,9,3,1,4,3,2,1,4,4,3,7,2};
        DigitSecret ds3(numbers3,20);
        CharSecret cs1("fhdaieowujkfjdsafjdsakjhueiqoyroq");
        CharSecret cs2("nvzcfsadrqipqhfjdfncxoqw");
        CharSecret cs3("uyoihfdsanmqeqrzvdhfeqyrq");
        Secret** s = new Secret*[6];
        s[0] = &ds1;
        s[1] = &ds2;
        s[2] = &ds3;
        s[3] = &cs1;
        s[4] = &cs2;
        s[5] = &cs3;
        printAll(s,6);
        delete [] s;
    }
    
    return 0;
}