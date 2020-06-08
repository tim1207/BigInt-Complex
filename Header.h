#ifndef HEADER_H
#define HEADER_H
#include <string>
using namespace std;
//大整數
class BigInt
{
	// (一) default: 固定位(100) 的整數
	// (二) 任意位的整數


public:
	static int BigIntCounter;
	BigInt(); // default constructor, value = 0, capacity = 100, numDigits = 0
	BigInt(int value, int size = 100); // assign an integer value and capacity = size
	BigInt(const char*, int size = 100); // assign a string 
	BigInt(const BigInt&); // copy constructor
	~BigInt(); // destructor
	static int getCount()
	{
		return BigIntCounter;
	}

	void Zero();
	void Add(const BigInt&);
	void Add(int);
	void Add(const char*);
	//int isZero();
	int division(BigInt, BigInt&);//暴力減法
	void PrintValue();
	friend ostream& operator<<(ostream& cout, BigInt a);
	friend BigInt operator+=(BigInt& beadder, BigInt adder);
	friend BigInt operator-(BigInt BeSubstahend, BigInt Substahend);
	friend BigInt operator*(BigInt bemuti, BigInt times);
	friend BigInt operator+(BigInt beadder, BigInt adder);
	friend BigInt operator-(BigInt BeSubstahend, BigInt Substahend);
	friend BigInt operator-=(BigInt& BeSubstahend, BigInt Substahend);
	friend BigInt operator*=(BigInt& bemuti, BigInt times);
	friend BigInt operator*=(BigInt& bemuti, BigInt times);
	friend BigInt operator/=(BigInt& a, BigInt b);

	int operator> ( const BigInt& com);
	BigInt operator=(BigInt copy);
	BigInt operator/(BigInt div);
	BigInt& operator++();
	BigInt operator++(int );
	BigInt& operator--();
	BigInt operator--(int );
private:
	char* _digits;	// Array: array每一個整數存一位數 
	int _capacity;	// Array  記憶體容量 
	int _numDigits; // 整數有幾位數
	int sign;		// 擴充成允許正負數使用
};
ostream& operator<<(ostream& cout, BigInt print)
{
	print.PrintValue();
	return cout;
}
BigInt operator+(BigInt beadder, BigInt adder)
{
	beadder.Add(adder);
	return beadder;
}
BigInt operator-(BigInt BeSubstahend, BigInt Substahend)
{
	Substahend.sign = Substahend.sign * -1;
	BeSubstahend.Add(Substahend);
	return BeSubstahend;
}
BigInt operator+=(BigInt& beadd, BigInt adder)
{
	beadd.Add(adder);
	return beadd;
}
BigInt operator-=(BigInt& BeSubstahend, BigInt Substahend)
{
	BeSubstahend = BeSubstahend - Substahend;
	return BeSubstahend;
}
BigInt operator*(BigInt bemuti, BigInt times)
{
	BigInt temp(bemuti);
	//if (times._numDigits == 1 || times._digits[0] == 0)
	if (times._numDigits == 1 && times._digits[0] == 0)
	{
		return 0;
	}
	int isNegative = 0;
	if (times.sign == -1)
	{
		isNegative = 1;
		times.sign = 1;
	}
	while (times.sign == 1) //直到變0
	{
		//cout << "times: " << times << "a: " << a << endl;
		bemuti.Add(temp); // 暴力加
		times = times - 1;
	}

	temp.sign = temp.sign * -1;
	bemuti.Add(temp);//0
	bemuti.Add(temp);//-1

	if (isNegative == 1)
	{
		bemuti.sign = bemuti.sign * -1;
	}

	return bemuti;
}
BigInt operator*=(BigInt& bemuti, BigInt times)
{
	bemuti = bemuti * times;
	return bemuti;
}
BigInt operator/=(BigInt& a, BigInt b)
{
	a = a / b;
	return a;
}
BigInt BigInt::operator=(BigInt copy)// 同copy
{
	sign = copy.sign;
	_capacity = copy._capacity;
	_digits = new char[_capacity]; // Array: 儲存整數
	Zero();
	_numDigits = copy._numDigits;

	for (int i = 0; i < _numDigits; i++)
	{
		_digits[i] = copy._digits[i];
	}
	return *this;
}
BigInt& BigInt::operator++()
{
	Add(1);
	return *this;
}
BigInt BigInt::operator++(int )
{
	BigInt temp(*this);
	Add(1);
	return temp;
}
BigInt BigInt::operator--(int )
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
BigInt BigInt::operator/(BigInt div)
{
	int finalSign = sign * div.sign;

	BigInt temp(*this);
	temp.sign = 1;
	div.sign = 1;
	int currentIndex = _numDigits - div._numDigits; //終位數
	int Upper = _numDigits - 1;

	string answer = "";

	BigInt currentRemainder;
	//
	currentRemainder.PrintValue();
	//
	while (1)
	{

		if (currentIndex <= -1)
		{
			break;
		}

		string theNum = "";
		int i;
		for (i = Upper; i >= currentIndex; i--)//轉成數字 1次1個
		{
			theNum += to_string(temp._digits[i]);//轉乘數字
		}
		const char* buffer = theNum.c_str();//將String物件轉換成C語言形式的字串常數


		BigInt theNumThisRound(buffer);
		//cout <<"temp:"<<temp<< "\ttheNum: " << theNumThisRound << "\t";


		int resultThisRound = theNumThisRound.division(div, currentRemainder);

		//cout << "result this round:" << resultThisRound  <<"\tcurrentRemainder: "<<currentRemainder << endl;

		while (currentRemainder._digits[currentRemainder._numDigits - 1] == 0)//為零扣除
		{
			currentRemainder._numDigits = currentRemainder._numDigits - 1;
		}

		if (resultThisRound == 0)
		{
			answer += to_string(0);
			currentIndex--;//位數減少
		}
		else
		{
			answer += to_string(resultThisRound);
			int j = 0;
			while (j < currentRemainder._numDigits)
			{
				temp._digits[currentIndex + j] = currentRemainder._digits[j];
				j++;
			}
			temp._numDigits = currentIndex + j;
			Upper = temp._numDigits - 1;
			currentIndex--;
		}
	}
	const char* buffer = answer.c_str();
	BigInt lastAns(buffer);
	lastAns.sign = finalSign;
	return lastAns;

}
int BigInt :: operator> ( const BigInt& com) {
	int count = _numDigits-1;
	if (sign == 1 && com.sign == 1) {
		if (_numDigits > com._numDigits) return 1;
		for (int i = count; i >= 0; i--) {
			if (_digits[i] > com._digits[i])
				return 1;
		}
	}
	else if (sign == -1 && com.sign == -1) {
		if (_numDigits < com._numDigits) return 1;
		for (int i = count; i >= 0; i--) {
			if (_digits[i] < com._digits[i])
				return 1;
		}
	}
	else if (sign == 1 && com.sign == -1) return 1;
	else return 0;

}

#endif
