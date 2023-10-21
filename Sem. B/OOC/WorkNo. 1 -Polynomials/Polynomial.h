#pragma once
using namespace std;
class Polynomial
{
private:
	double* _coeff; //מערך של מקדמים
	int _dagree;
	static int MaxDegree;
public:
	//קונסטרקטוקים
	Polynomial();
	Polynomial(int);
	Polynomial(double[], int);
	Polynomial(const Polynomial&);//קופי קונסטרקטור
	~Polynomial();

	//פונקציות
	double getCoeff(int) const;
	static int getMaxDegree();
	Polynomial &setCoeff(int deg, double c);
	int getDegree(bool) const;
	int getDegree() const;
	void print()const;
};

