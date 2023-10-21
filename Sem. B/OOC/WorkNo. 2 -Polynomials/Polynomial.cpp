#define INVALID -1234.12
#include "Polynomial.h"

// static variable for highest degree
int Polynomial::maxDegree = 0;

// Constructors
Polynomial::Polynomial(int deg)
{
	int i;
	this->setDegree(deg);
	this->_coefArr = new double[deg + 1];
	for (i = 0; i <= deg; i++) {
		this->_coefArr[i] = 0; // set to 0 the entire array;
	}
}

Polynomial::Polynomial(double coefs[], int deg) {
	int i;
	this->setDegree(deg);
	this->_coefArr = new double[deg + 1];
	for (i = 0; i <= deg; i++) {
		this->setCoeff(i, coefs[i]);
	}
}

// copy constructor
Polynomial::Polynomial(const Polynomial& other) {
	this->setDegree(other._degree);
	int size = other.getDegree(false);
	this->_coefArr = new double[size + 1];
	for (int i = 0; i <= size; i++)
		this->_coefArr[i] = other._coefArr[i];
}

//Destructor
Polynomial::~Polynomial()
{
	delete[] this->_coefArr;
}

int Polynomial::getMaxDegree() {
	return Polynomial::maxDegree;
}

void Polynomial::print() const
{
	int trueDeg, i = 0;
	cout << "polynomial = ";
	if (this->_degree == 0)
		cout << "0";
	else {
		trueDeg = this->getDegree(true); // gets true degree of polynomial
		cout << this->_coefArr[i++]; // prints first element
		for (; i <= trueDeg; i++) // i starts from 1
		{
			cout <<"+" << "(" << this->_coefArr[i] <<")" << "*X^" << i;
		}
	}
	cout << endl;
}
// Getters 
double Polynomial::getDegree(const bool what) const {
	int i;
	int maxDeg = this->_degree;
	if (!what)
	{
		return this->_degree;
	}
	else {
		for (i = maxDeg; i >= 0; i--) {
			if (this->_coefArr[i] != 0) {
				return i;
			}
		}
		return 0; // all elements in coefArr are 0;
	}
}

int Polynomial::getDegree(const Polynomial& pol, const bool bl) const {
	return pol.getDegree(bl);
}



double Polynomial::getCoeff(const int index) const
{
	if (index > this->getDegree(false) || index < 0) { return INVALID; }
	else if (index > this->getDegree(true) && index < this->getDegree(false)) return 0;
	return this->_coefArr[index];
}

// Setters
void Polynomial::setDegree(const int degree) {
	this->_degree = degree;
}

void Polynomial::setCoeff(const int deg, const double coef)
{
	this->_coefArr[deg] = coef;

	maxDegree = (coef != 0 && deg > this->maxDegree) ? deg : maxDegree; // updating maxDegree if necessary
}


//operators

Polynomial& Polynomial::operator=(const Polynomial& p)
{
	int i;
	if(this->getDegree(false) < p._degree)
	{
		this->_coefArr = new double[p._degree + 1];
		this->_degree = p._degree;
		for (i = 0; i <= p._degree; i++)
		{
			this->_coefArr[i] = p._coefArr[i];
		}
	}
	for (i = 0; i <= p._degree; i++)
	{
		this->_coefArr[i] = p._coefArr[i];
	}
	return *this;
}

Polynomial Polynomial::operator+(const Polynomial&p) const
{
	int i, max;
	p._degree >= this->_degree ? max = p._degree : max = this->_degree;
	Polynomial *result= new Polynomial(maxDegree);

	for (int i = 0; i <= maxDegree; i++) {
		if (i <= this->_degree && i <= p._degree) {
			result->_coefArr[i] = this->_coefArr[i] + p._coefArr[i];
		}
		else if (i <= this->_degree) {
			result->_coefArr[i] = this->_coefArr[i];
		}
		else if (i <= p._degree) {
			result->_coefArr[i] = p._coefArr[i];
		}
	}

	return *result;
}

Polynomial Polynomial::operator-(const Polynomial& p) const
{
	int i, max;
	p._degree >= this->_degree ? max = p._degree : max = this->_degree;
	Polynomial* result= new Polynomial(maxDegree);

	for (int i = 0; i <= maxDegree; i++) {
		if (i <= this->_degree && i <= p._degree) {
			result->_coefArr[i] = this->_coefArr[i] - p._coefArr[i];
		}
		else if (i <= this->_degree) {
			result->_coefArr[i] = this->_coefArr[i];
		}
		else if (i <= p._degree) {
			result->_coefArr[i] = p._coefArr[i];
		}
	}

	return *result;
}

Polynomial Polynomial::operator*(const Polynomial& p) const
{
	int i, j;
	Polynomial* poly=new Polynomial(this->_degree+p._degree);
	for (i = 0; i <= this->_degree; i++) {
		for (j = 0; j <= p._degree; j++) {
			poly->_coefArr[i + j] += this->_coefArr[i] * p._coefArr[j];
			if (poly->_coefArr[i + j] && i + j > maxDegree) {
				maxDegree = i + j;
			}
		}
	}
	
	return* poly;
}
Polynomial Polynomial::operator*(const double d) const
{
	Polynomial* poly = new Polynomial();
	*poly = *this;
	for (int i = 0; i <= this->_degree; i++)
	{
		poly->_coefArr[i] *= d;
	}
	return *poly;
}
Polynomial operator*(const double d, const Polynomial& p)
{
	return p * d;
}


double& Polynomial::operator[](int const index)
{
	return this->_coefArr[index];
}

const double Polynomial::operator[](int const index) const
{
	return this->getCoeff(index);
}


ostream& operator<<(ostream& out, const Polynomial& p)
{
	int trueDeg, i = 0;
	out << "polynomial = ";
	if (p._degree == 0)
		out << "0";
	else {
		trueDeg = p.getDegree(true); 
		out << p._coefArr[i++];
		for (; i <= trueDeg; i++) 
		{
			out << "+" <<"("<<p._coefArr[i] <<")" << "*X^" << i;
		}
	}
	out << endl;
	return out;
}