#ifndef BIGINT_H
#define BIGINT_H
#include <string>
using namespace std;

//�j���
class BigInt
{
	// (�@) default: �T�w��(100) �����
	// (�G) ���N�쪺���


public:
	static int BigIntCounter;
	BigInt(); // default constructor, value = 0, capacity = 100, numDigits = 0
	BigInt(int value, int size = 100); // assign an integer value and capacity = size
	BigInt(const char*, int size = 100); // assign a string 
	BigInt(const BigInt&); // copy constructor
	~BigInt(); // destructor
	int getsign() { return sign; }
	static int getCount()
	{
		return BigIntCounter;
	}

	void Zero();
	void Add(const BigInt&);
	void Add(int);
	void Add(const char*);
	int isZero();
	int division(BigInt, BigInt&);
	void PrintValue();
	friend ostream& operator<<(ostream& out, BigInt a);
	friend BigInt operator+=(BigInt& a, BigInt b);

	friend BigInt operator-(BigInt a, BigInt b);
	friend BigInt operator*(BigInt a, BigInt times);
	BigInt operator=(BigInt b);
	BigInt operator/(BigInt b);
	BigInt& operator++();
	BigInt operator++(int b);
	BigInt& operator--();
	BigInt operator--(int b);

private:
	char* _digits; // Array: array�C�@�Ӿ�Ʀs�@��� �s��ƥi�H�˹L�Ӧs�p������K(array�Ĥ@�Ӧs�Ӧ�� array�ĤG�Ӧs�Q��� ...)
	int _capacity; // Array  �O����e�q 
	int _numDigits; // ��Ʀ��X���
	int sign;
	// �X�R�����\���t�ƨϥ�
};


ostream& operator<<(ostream& out, BigInt a)
{
	a.PrintValue();
	return out;
}

BigInt BigInt::operator=(BigInt copy)
{
	sign = copy.sign;
	_capacity = copy._capacity;
	_digits = new char[_capacity]; // Array: �x�s���
	Zero();
	_numDigits = copy._numDigits;

	for (int i = 0; i < _numDigits; i++)
	{
		_digits[i] = copy._digits[i];
	}
	return *this;
}

BigInt operator+=(BigInt& a, BigInt b)
{
	a.Add(b);
	return a;
}

BigInt operator-=(BigInt& a, BigInt b)
{
	a = a - b;
	return a;
}


BigInt& BigInt::operator++()
{
	Add(1);
	return *this;
}

BigInt BigInt::operator++(int b)
{
	BigInt temp(*this);
	Add(1);
	return temp;
}

BigInt operator+(BigInt a, BigInt b)
{
	a.Add(b);
	return a;
}

BigInt operator-(BigInt a, BigInt b)
{
	b.sign = b.sign * -1;
	a.Add(b);
	return a;
}

BigInt BigInt::operator--(int b)
{
	BigInt temp(*this);
	Add(-1);
	return temp;
}

BigInt& BigInt::operator--()
{
	Add(-1);
	return *this;
}


BigInt operator*(BigInt a, BigInt times)
{
	BigInt temp(a);
	if (temp.isZero() == 1 || times.isZero() == 1)
	{
		return 0;
	}
	int isNegative = 0;
	if (times.sign == -1)
	{
		isNegative = 1;
		times.sign = 1;
	}
	while (times.sign == 1)
	{
		//cout << "times: " << times << "a: " << a << endl;
		a.Add(temp);
		times = times - 1;
	}
	temp.sign = temp.sign * -1;
	a.Add(temp);
	a.Add(temp);
	if (isNegative == 1)
	{
		a.sign = a.sign * -1;
	}

	//cout << "a final: " << a<<endl;
	return a;
}

BigInt operator*=(BigInt& a, BigInt times)
{
	a = a * times;
	return a;
}

BigInt BigInt::operator/(BigInt div)
{
	int finalSign = sign * div.sign;
	BigInt temp(*this);
	temp.sign = 1;
	div.sign = 1;

	//main idea:�`���k

	int currentIndex = _numDigits - div._numDigits; //�s�ثe���k���ؼЦ�m
	int currentUpperCap = _numDigits - 1; //�s�ثe�Ʀr���̤j��m


	string answer = ""; //�o�@�Ӧr��s����

	BigInt currentRemainder; //�s�C�����l��


	while (true)
	{

		if (currentIndex == -1)//�p�G�ؼЦ�m�O0�N��w�g���������F
		{
			break;
		}


		//��X�o�@���n�Q�����ơA�q�ثe�̤j��}�l��A���ؼЦ�m����
		string theNum = "";
		int i;
		for (i = currentUpperCap; i >= currentIndex; i--)
		{
			theNum += to_string(temp._digits[i]);
		}
		const char* buffer = theNum.c_str(); //�r����char����
		BigInt theNumThisRound(buffer);


		//�o��o�����өM�l��
		int resultThisRound = theNumThisRound.division(div, currentRemainder);


		//clear Zero
		while (currentRemainder._digits[currentRemainder._numDigits - 1] == 0)
		{
			currentRemainder._numDigits = currentRemainder._numDigits - 1;
		}

		if (resultThisRound == 0)//�p�G�����ӬO0
		{
			answer += to_string(0); //��0�[�i����
			currentIndex--;
		}
		else //�p�G�����Ӥ��O0
		{
			answer += to_string(resultThisRound); //��ӥ[�i����
			int j = 0;

			//��l�Ʊ��^�h�쥻���Ʀr�A�N�i�i��U�@�������k
			while (j < currentRemainder._numDigits)
			{
				temp._digits[currentIndex + j] = currentRemainder._digits[j];
				j++;
			}
			temp._numDigits = currentIndex + j;
			currentUpperCap = temp._numDigits - 1; //��̤j���]�����F�W�����l�ƫ�o����
			currentIndex--;
		}
	}
	const char* buffer = answer.c_str();
	BigInt lastAns(buffer);
	lastAns.sign = finalSign;
	return lastAns;
}

BigInt operator/=(BigInt& a, BigInt div)
{
	a = a / div;
	return a;
}


class BigComplexNumber {
public:
	BigComplexNumber(int a = 0, int b = 0);
	BigComplexNumber(const char* const a, const char* const b);
	void setValue(int, int);
	friend ostream& operator<<(ostream& out, BigComplexNumber print);
	BigComplexNumber operator=(BigComplexNumber b);
	BigComplexNumber operator+(BigComplexNumber b);
	BigComplexNumber operator-(BigComplexNumber b);
	BigComplexNumber operator+=(BigComplexNumber b);
	BigComplexNumber operator-=(BigComplexNumber b);
	BigComplexNumber operator*(BigComplexNumber b);
	BigComplexNumber operator*=(BigComplexNumber b);
private:
	BigInt real, unreal;
};
BigComplexNumber::BigComplexNumber(int a, int b) {
	real = a;
	unreal = b;
}
BigComplexNumber::BigComplexNumber(const char* const a, const char* const b) {
	real = a;
	unreal = b;
}
void BigComplexNumber::setValue(int a, int b) {
	real = a;
	unreal = b;
}
ostream& operator<<(ostream& out, BigComplexNumber print) {
	print.real.PrintValue();
	if (print.unreal.getsign() == 1) printf("+");
	print.unreal.PrintValue();
	printf("i");
	return out;
}

BigComplexNumber BigComplexNumber:: operator=(BigComplexNumber b) {
	real = b.real;
	unreal = b.unreal;
	return *this;
}

BigComplexNumber BigComplexNumber ::  operator +(BigComplexNumber b) {
	BigComplexNumber temp = *this;
	temp.real+=b.real;
	temp.unreal.Add(b.unreal);
	return temp;
}

BigComplexNumber BigComplexNumber ::  operator -(BigComplexNumber b) {
	BigComplexNumber temp = *this;
	temp.real -= b.real;
	temp.unreal -= b.unreal;
	return temp;
}

BigComplexNumber BigComplexNumber ::  operator +=(BigComplexNumber b) {
	real += b.real;
	unreal += b.unreal;
	return *this;
}

BigComplexNumber BigComplexNumber ::  operator -=(BigComplexNumber b) {
	real -= b.real;
	unreal -= b.unreal;
	return *this;
}
BigComplexNumber BigComplexNumber ::  operator *(BigComplexNumber b) {
	BigComplexNumber temp = *this;
	temp.real = real*b.real - unreal*b.unreal;
	temp.unreal = real * b.unreal + unreal * b.real;
	return temp;
}

BigComplexNumber BigComplexNumber ::  operator *=(BigComplexNumber b) {
	BigComplexNumber temp = *this;
	*this = temp* b;
	return *this;
}


#endif
#pragma once
