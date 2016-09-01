#include <iostream>

using namespace std;

class B {
public:
	B(int x) {
		cout << "B::B()" << endl;
	}
	void init(int x) {
		cout << "B::init(int)" << endl;
	}
};

class C : public B {
public:
	using B::B;

/*
	C() {
		cout << "C:C()" << endl;
	}
	using B::init;
	void init(int x) {
		cout << "C::init(int)" << endl;
	}
*/
	void init(double d) {
		//B::init(10);  // OK
		cout << "C::init(double)" << endl;
	}

	double getD() const {
		return m_d;
	}

private:
	double m_d {9.9};
};

ostream& operator <<(ostream& out, const C& c) 
{
	out << c.getD();
}

int main()
{
	int x = 10;
	double d = 10.0;
	C c(100);
	c.init(x);
	c.init(d);

	cout << c << endl;;
	return 0;
}
