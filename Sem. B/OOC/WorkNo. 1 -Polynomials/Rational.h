#pragma once
#include <iostream>
using namespace std;
#include "Polynomial.h"
class Rational
{
private:
	Polynomial Numerator, Denominator;
public:
	Rational();
	Rational(const Polynomial&, const Polynomial&);
	void print();
	Polynomial& getNom();
	Polynomial& getDenom();
};

