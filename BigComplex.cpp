#include <malloc.h>
#include <iostream>
#include <string.h>
#include "bigInt.h"

using namespace std;


void BigInt::PrintValue()
{
	while (_digits[_numDigits - 1] == 0)
	{
		_numDigits = _numDigits - 1;
	}
	if (_numDigits == 0)
		cout << '0';
	else
	{
		if (sign == -1)
			cout << '-';
		//else
			//cout << '+';
		for (int i = _numDigits - 1; i >= 0; i--)
			cout << static_cast<int>(_digits[i]);
	}
	//cout << "  ";
}

void BigInt::Zero()
{
	for (int i = 0; i < _capacity; i++)
		_digits[i] = 0;
	_numDigits = 0;
}

BigInt::BigInt()
{
	// default constructor, value = 0, capacity = 100, numDigits = 0
	_capacity = 100;
	_digits = new char[_capacity];
	Zero();
	_digits[0] = 0;
	_numDigits++;
	sign = 1;
	BigIntCounter++;
}

BigInt::~BigInt()
{
	// destructor
	delete[] _digits;
	_digits = nullptr;
	_capacity = _numDigits = 0;
	BigIntCounter--;
}


BigInt::BigInt(const char* const s, int size)
{
	BigIntCounter++;
	_digits = nullptr; // Array: 儲存整數
	_capacity = _numDigits = 0; // Array 大小 // 整數位數

	int strSize = strlen(s);
	if (strSize > size)
		size = strSize;
	if (size < 1)
		return;
	_capacity = size;
	_digits = new char[_capacity];
	Zero();

	if (s[0] == '-')
		sign = -1;
	else
		sign = 1;

	for (_numDigits = 0; _numDigits < strSize; _numDigits++)
	{
		if (s[strSize - _numDigits - 1] < '0' || s[strSize - _numDigits - 1] > '9')
			break;
		_digits[_numDigits] = s[strSize - _numDigits - 1] - 48;
	}


	while (_digits[_numDigits - 1] == 0)
	{
		_numDigits = _numDigits - 1;
	}
}


// assign an integer value and capacity = size
BigInt::BigInt(const int valueR, const int size)
{
	BigIntCounter++;
	int value = valueR;
	if (value < 0)
	{
		sign = -1;
		value = value * -1;
	}
	else
	{
		sign = 1;
	}
	_numDigits = 0;
	int digitNum = 0;

	int numTemp = value;
	int numTemp2 = value;
	while (numTemp > 0)
	{
		digitNum++;
		numTemp = numTemp / 10;
	}

	if (digitNum > size)
	{
		_capacity = digitNum;
	}
	else
	{
		_capacity = size;
	}
	_digits = new char[_capacity]; // Array: 儲存整數

	Zero();

	_numDigits = digitNum;


	for (int i = 0; i < _numDigits; i++)
	{
		_digits[i] = numTemp2 % 10;
		numTemp2 = numTemp2 / 10;
	}
}

// copy constructor
BigInt::BigInt(const BigInt& bi)
{
	BigIntCounter++;
	sign = bi.sign;
	_capacity = bi._capacity;
	_digits = new char[_capacity]; // Array: 儲存整數
	Zero();
	_numDigits = bi._numDigits;

	for (int i = 0; i < _numDigits; i++)
	{
		_digits[i] = bi._digits[i];
	}
}

void BigInt::Add(const int addNum)
{
	BigInt temp2(addNum);
	Add(temp2);
}

void BigInt::Add(const char* const addchar)
{
	BigInt temp = (addchar);
	Add(temp);
}


void BigInt::Add(const BigInt& bi)
{
	int isSubtracttion = 0;
	int biSize;
	if (bi._numDigits + 1 >= _capacity)
	{
		BigInt temp(*this);
		delete[] _digits;
		_digits = new char[bi._numDigits + 1];
		_capacity = bi._numDigits + 1;
		Zero();
		_numDigits = 0;

		Add(temp);
	}


	if (bi._numDigits > _numDigits)
	{
		_numDigits = bi._numDigits;
		biSize = bi._numDigits;
	}
	else
	{
		biSize = _numDigits;
	}


	int i;
	if (sign == -1 && bi.sign == 1)
	{
		for (i = 0; i < biSize; i++)
		{
			if (i < _numDigits)
			{
				_digits[i] = 9 - _digits[i];
			}
			else
			{
				_digits[i] = 9;
			}
		}
		sign = 1;

		Add(1);
		isSubtracttion = 1;
	}


	BigInt adder;
	adder._digits = new char[biSize];


	if (sign == 1 && bi.sign == -1)
	{
		for (i = 0; i < biSize; i++)
		{
			if (i < bi._numDigits)
			{
				adder._digits[i] = 9 - bi._digits[i];
			}
			else
			{
				adder._digits[i] = 9;
			}
		}

		adder.Add(1);
		isSubtracttion = 1;
		adder._numDigits = biSize;
	}
	else
	{
		delete[] adder._digits;

		adder.sign = bi.sign;
		adder._capacity = bi._capacity;
		adder._digits = new char[adder._capacity];
		adder.Zero();
		adder._numDigits = bi._numDigits;
		for (i = 0; i < bi._numDigits; i++)
		{
			adder._digits[i] = bi._digits[i];
		}
	}

	/*cout << "add:";
	(*this).PrintValue();
	cout<<"+";
	adder.PrintValue();*/


	int carry = 0;
	i = 0;
	while (i < biSize)
	{
		int addedThisRound;
		if (i < adder._numDigits)
		{
			addedThisRound = _digits[i] + adder._digits[i] + carry;
		}
		else
		{
			addedThisRound = _digits[i] + 0 + carry;
		}

		if (addedThisRound > 9)
		{
			addedThisRound = addedThisRound - 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		_digits[i] = addedThisRound;
		i++;
	}


	if (isSubtracttion == 1)
	{
		if (carry == 1)
		{
			sign = 1;
		}
		else
		{
			for (i = 0; i < biSize; i++)
			{
				_digits[i] = 9 - _digits[i];
			}
			Add(1);
			sign = -1;
		}
	}
	else
	{
		if (carry == 1)
		{
			if (i >= _capacity)
			{
				BigInt temp(*this);
				delete[]_digits;
				_digits = new char[i + 1];
				_capacity = i + 1;
				Zero();
				_numDigits = 0;
				Add(temp);
			}
			_numDigits++;
			_digits[i] = _digits[i] + 1;
		}
	}
}

int BigInt::division(BigInt b, BigInt& remainder)
{

	b.sign = this->sign * -1;
	BigInt temp(*this);

	int counter = 0;
	while (temp.sign == this->sign)
	{
		temp.Add(b);
		counter++;
	}

	b.sign = b.sign * -1;
	temp.Add(b);
	remainder = temp;
	counter--;
	return counter;
}


int BigInt::isZero()
{
	int i = 0;
	for (i = 0; i < _numDigits; i++)
	{
		if (_digits[i] != 0)
		{
			return 0;
		}
	}
	return 1;
}


int BigInt::BigIntCounter = 0;


void main()
{

	BigComplexNumber x, y("10", "20"), z(2, 4);

	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;

	x = y + z;
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;
	
	x += y;
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;
	y += z;
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;

	y.setValue(10, 20);
	z.setValue(4, 2);
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;
	x = y - z;
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;
	x -= y;
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;
	z -= y;
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;
	
	y.setValue(2, 4);
	z.setValue(10, 20);
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;
	x = y * z;
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;
	x *= y;
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;
	z *= y;
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;
	
}
