//============================================================================
// Name        : Constructor.cpp
// Author      : jiawh
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Deopy {
public:
	Deopy() {
		cout << "Deopy()" << endl;
	}
	Deopy(int i) :
			m_i(i) {
		cout << "Deopy(int)" << endl;
	}
	Deopy& operator= (const Deopy& d) {
		cout << "Deopy::operatro=()" << endl;
		if (this == &d) {
			return *this;
		}
		this->m_i = d.m_i;
		return *this;
	}
private:
	int m_i;
};

class Sneezy {
public:
	Sneezy() {
		cout << "Sneezy()" << endl;
	}

	Sneezy(int i) : m_i(i) {
		cout << "Sneezy(int)" << endl;
	}
private:
	int m_i;
};

class Bashful {
public:
	Bashful() {
		cout << "Bashful()" << endl;
	}

	Bashful(int i) : m_i(i) {
		cout << "Bashful(int)" << endl;
	}
private:
	int m_i;
};

class SnowWhite {
public:
	SnowWhite() : m_sneezy(10) {

	}

	SnowWhite(Deopy d) : m_deopy(d) {
		cout << "SnowWhilte(Deopy)" << endl;
		//m_deopy = d;
	}
private:

	Sneezy m_sneezy;
	Bashful m_bashful;
	Deopy m_deopy;
};

int main() {
	Deopy *d;
	SnowWhite sw(*d);

	return 0;
}
