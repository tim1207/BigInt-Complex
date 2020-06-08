#include <malloc.h>
#include <iostream>
#include <string.h>
#include "Header.h"
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
		else
			cout << '+';
		for (int i = _numDigits - 1; i >= 0; i--)
			cout << static_cast<int>(_digits[i]);
	}
	cout << "  ";
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
	_digits = nullptr; // Array: 纗俱计
	_capacity = _numDigits = 0; // Array  // 俱计计

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

	int NumTemp = value;

	while (NumTemp > 0)
	{
		digitNum++;
		NumTemp = NumTemp / 10;
	}

	if (digitNum > size)
	{
		_capacity = digitNum;
	}
	else
	{
		_capacity = size;
	}
	_digits = new char[_capacity]; 

	Zero();

	_numDigits = digitNum;

	NumTemp = value;
	for (int i = 0; i < _numDigits; i++)
	{
		_digits[i] = NumTemp % 10;
		NumTemp = NumTemp / 10;
	}
}
BigInt::BigInt(const BigInt& copy)
{
	BigIntCounter++;
	sign = copy.sign;
	_capacity = copy._capacity;
	_digits = new char[_capacity]; // Array: 纗俱计
	Zero();
	_numDigits = copy._numDigits;

	for (int i = 0; i < _numDigits; i++)
	{
		_digits[i] = copy._digits[i];
	}
}
void BigInt::Add(const int addNum)
{
	BigInt temp(addNum);
	Add(temp);
}
void BigInt::Add(const char* const addchar)
{
	BigInt temp = (addchar);
	Add(temp);
}
void BigInt::Add(const BigInt& bi)
{
	int isSubtracttion = 0;
	int Size;
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
		Size = bi._numDigits;
	}
	else
	{
		Size = _numDigits;
	}


	int i;
	if (sign == -1 && bi.sign == 1) //钵腹  - +
	{
		for (i = 0; i < Size; i++) //传Θ干计
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

		Add(1);		//ソ计1 干计
		isSubtracttion = 1;
	}


	BigInt adder;
	adder._digits = new char[Size];


	if (sign == 1 && bi.sign == -1) //钵腹  - +
	{
		for (i = 0; i < Size; i++)
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
		adder._numDigits = Size;
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
	while (i < Size) // _digits + adder
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


	if (isSubtracttion == 1) //搭猭
	{
		if (carry == 1)
		{
			sign = 1;
		}
		else
		{
			for (i = 0; i < Size; i++)
			{
				_digits[i] = 9 - _digits[i];
			}
			Add(1);
			sign = -1;
		}
	}
	else // 秈
	{
		if (carry == 1)
		{
			if (i >= _capacity)//耎丁
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
	}//穦搭Ω

	b.sign = b.sign * -1;
	temp.Add(b);//ㄓ
	remainder = temp;
	counter--;
	return counter;//肚Ω计
}
int BigInt::BigIntCounter = 0;
void main()
{	
	
	BigInt x, y("1234"), z("00000987654321");
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;

	BigInt i(44, 2); // Array  2		 
	BigInt j(i);
	BigInt k(10);
	cout << "i j k values: " << i << ' ' << j << ' ' << k << endl;
	cout << "Total BigInt Object Count: " << BigInt::getCount() << endl;
	
	x = y = "987654321098765432109876543210987654321098765432109876543210";
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;

	y = 10; y *= -88;			cout << "y values: " << y << endl;
	y = 10; y *= i;	 			cout << "y values: " << y << endl;
	y = x / 8;					cout << "y values: " << y << endl;
	x /= -8;					cout << "x values: " << x << endl;
	x /= i;	 					cout << "x values: " << x << endl;

	y = 10; y += -88;			cout << "y values: " << y << endl;
	y = 10; y += i;	 			cout << "y values: " << y << endl;
	y = 10; y -= -88;			cout << "y values: " << y << endl;
	y = 10; y -= i;	 			cout << "y values: " << y << endl;

	x = i + 3 + j * 2 * k;		cout << "x values: " << x << endl;
	x = i - 3 - j * 2 * k;		cout << "x values: " << x << endl;
	cout << "k values: " << k++ << ' ' << k << endl;
	
	k = 10;	x = (++k)++; 		
	cout << "x k values: " << x << ' ' << k << endl;
	k = 10;	x = (--k)--; 		
	cout << "x k values: " << x << ' ' << k << endl;

	x = y = "987654321098765432109876543210";
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;
	int result = x > z;
	cout << result<<endl;

	system("pause");
}
