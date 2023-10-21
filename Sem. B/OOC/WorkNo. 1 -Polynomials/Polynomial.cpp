#include <iostream>
using namespace std;
#include "Polynomial.h"
int Polynomial::MaxDegree = 0;
Polynomial::Polynomial()
{
	this->_coeff = NULL;
	this->_dagree = 0;
}
Polynomial::Polynomial(int dagree)
{
	this->_dagree = dagree;
	this->_coeff = new double[dagree + 1];
	int i;
	for (i = 0; i <= dagree; i++)
	{
		_coeff[i] = 0;
		
	}
}
Polynomial::Polynomial(double coeff[], int dagree)
{
	this->_dagree = dagree;
	this->_coeff = new double[dagree + 1];
	int i;
	for (i = 0; i <= dagree; i++)
	{
		_coeff[i] = coeff[i];
		if (_coeff[i] != 0 && i > MaxDegree)//אם המקדם שווה לאפס והדרגה כביכול גבוהה יותר, אין צורך לבצע את ההשמה כי הוא שווה לאפס
		{
			MaxDegree = i;
		}
	}
}
Polynomial::Polynomial(const Polynomial& p)
{
	_dagree = p._dagree;
	if (p._coeff == NULL)//אם המערך של הפולי שהתקבל שווה לNULL אז גם הפולי של המערך החדש יהיה שווה לNULL
	{
		_coeff = NULL;
	}
	else
	{
		_coeff = new double[p._dagree + 1];
		int i;
		for (i = 0; i <= p._dagree; i++)
		{
			_coeff[i] = p._coeff[i];
		}
	}
}
Polynomial::~Polynomial() {}



double Polynomial::getCoeff(int index)const
{
	if (index >= 0 && index <= this->_dagree)
	{
		return this->_coeff[index];
	}
	else
	{
		return -12345.5;
	}
}

int Polynomial::getMaxDegree()
{
	return MaxDegree;
}
Polynomial&  Polynomial::setCoeff(int dagree, double coefficient)
{
	_coeff[dagree] = coefficient;
	return *this;
}
int Polynomial::getDegree(bool what) const
{
	if (what == false)
	{
		return _dagree;
	}
	else if ((what == true))
	{
		return getDegree();
	}
}

int Polynomial::getDegree() const
{
	int i, counter = 0;
	for (i = 0; i <= _dagree; i++)
	{
		if (_coeff[i] != 0)
		{
			counter = i;
		}
	}
	return counter;
}

void Polynomial::print() const
{
	int i, max_dagree=0;
	cout << "polynomial = ";
	if (_coeff == NULL && _dagree == 0)
	{
		cout << "0" << endl;
		return;
	}
	for (i = 0; i <= _dagree; i++)
	{
		if (_coeff[i] && i > max_dagree)
		{
			max_dagree = i;
		}
	}
	for (i = 0; i <= max_dagree; i++)
	{
		if (i == 0)//מקדם חופשי - 0
		{
			if (_coeff[i] == 0)
			{
				cout << "0";
			}
			else
			{
				cout << _coeff[i];
			}
		}
		else
		{
			cout << "+";
			if (_coeff[i] == 0)
			{
				cout << "0";
			}
			else
			{
				cout << _coeff[i];
			}
			cout << "X^" << i;
		}	
	}
	cout << endl;
}
