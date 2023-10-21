#pragma once
using namespace std;
class Polynomial
{
private:
	double* _coeff; //���� �� ������
	int _dagree;
	static int MaxDegree;
public:
	//������������
	Polynomial();
	Polynomial(int);
	Polynomial(double[], int);
	Polynomial(const Polynomial&);//���� ����������
	~Polynomial();

	//��������
	double getCoeff(int) const;
	static int getMaxDegree();
	Polynomial &setCoeff(int deg, double c);
	int getDegree(bool) const;
	int getDegree() const;
	void print()const;
};

