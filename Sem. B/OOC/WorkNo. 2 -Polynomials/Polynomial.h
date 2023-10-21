#pragma once
#include <iostream>
using namespace std;

class Polynomial
{
public:
	// constructors
	Polynomial(int degree = 1); // default param = 1;
	Polynomial(double coefs[], int n); // constructor with array of coefficients
	Polynomial(const Polynomial& other); // copy constructor 

	// destructor 
	~Polynomial();


	// getters
	double getDegree(const bool what) const;
	int getDegree(const Polynomial& pol, const bool bl) const;
	double getCoeff(const int index) const;
	static int getMaxDegree();

	// setters
	void setCoeff(const int deg, const double coef);
	void setDegree(const int degree);

	void print() const;



	//operators
	Polynomial& operator=(const Polynomial&);
	Polynomial operator+(const Polynomial&) const;
	Polynomial operator-(const Polynomial&) const;
	Polynomial operator*(const Polynomial&) const;
	Polynomial operator*(const double) const;
	friend ostream& operator<<(ostream&, const Polynomial&);
	friend Polynomial operator*(const double, const Polynomial&);
	double& operator[](int const);
	const double operator[](int const) const;
private:
	static int maxDegree;
	int _degree;
	double* _coefArr;
};

