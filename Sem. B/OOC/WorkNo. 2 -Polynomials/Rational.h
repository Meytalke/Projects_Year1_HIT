#pragma once
#include <iostream>
using namespace std;
class Rational
{
public:
	Rational(int degNum = 0, int degDenom = 1);
	Rational(const Polynomial& p1, const Polynomial& p2);

	Polynomial& getNom();
	Polynomial& getDenom();
	void print() const;

	//operators
	Rational& operator=(const Rational&);
	Rational operator+(const Rational&) const;
	Rational operator*(const Rational&) const;
	Rational operator*(const double) const;
	friend ostream& operator<<(ostream&, const Rational&);
	friend Rational operator*(const double, const Rational&);
private:

	Polynomial numerator;
	Polynomial denominator;
};

