#include "Rational.h"
#include <iostream>
using namespace std;
#include "Polynomial.h"

Rational::Rational(): Numerator(), Denominator(0)
{
	Denominator.setCoeff(0, 1);//רוצים לפי התמונה שהמכנה יהיה 1
}

Rational::Rational(const Polynomial& p1, const Polynomial& p2)
{
	Numerator = p1;
	Denominator = p2;
}

void Rational::print()
{
	Numerator.print();
	cout << "------------------------------" << endl;
	Denominator.print();
}

Polynomial& Rational::getNom()
{
	return Numerator;
}

Polynomial& Rational::getDenom()
{
	return Denominator;
}
