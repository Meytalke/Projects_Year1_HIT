#include "Polynomial.h"
#include "Rational.h"

Rational::Rational(int degNum, int degDenom)
	: numerator(degNum), denominator(degDenom)
{
	this->denominator.setCoeff(0, 1);
}



Rational::Rational(const Polynomial& num, const Polynomial& deno) :numerator(num), denominator(deno) {}



void Rational::print() const
{
	this->numerator.print();
	cout << "--------------------------" << endl;
	this->denominator.print();
}

Polynomial& Rational::getNom()
{
	return this->numerator;
}
Polynomial& Rational::getDenom()
{
	return this->denominator;
}


//operators
Rational& Rational::operator=(const Rational& r)
{
	this->numerator = r.numerator;
	this->denominator = r.denominator;
	return *this;
}

Rational Rational::operator+(const Rational& r) const
{
	Rational* rat = new Rational(this->numerator * r.denominator + this->denominator * r.numerator, this->denominator * r.denominator);
	return *rat;
}

Rational Rational::operator*(const Rational&r) const
{
	Rational* rat = new Rational(this->numerator * r.numerator, this->denominator * r.denominator);
	return *rat;
}

Rational Rational::operator*(const double d) const
{
	Rational* rat = new Rational(this->numerator* d, this->denominator *d);
	return *rat;
}

ostream& operator<<(ostream& out, const Rational& r)
{
	out << "numerator=" << r.numerator;
	out << "--------------------------" << endl;
	out << "denominator=" << r.denominator;
	return out;
}

Rational operator*(const double d, const Rational& r)
{
	return r * d;
}
