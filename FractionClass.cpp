/*
编写人：李鹤鹏
编写时间：2018/03/27
功能：分数类：
			1.实现分数的规约化（正负号，分子分母化简）
			2.分数与实数类型相互转化，保留两位小数
			3.分数与整数转换（取整）
			4.增删改查，加减乘除，自增自减（运算符重载）
			5.大于小于等于比较，输入输出重载
			6.如果分母是零，报错
*/

#include <iostream>

using namespace std;

class Fraction
{
public:
	Fraction(int numNew, int denNew);	//构造函数
	Fraction(){num = den = 1;};
	Fraction(double number);	//double到分数转换
	Fraction(int number)	//int到分数转换
	{
		num = number,
		den = 1;
	}
	//Fraction(const Fraction& fra);//调用默认复制构造函数
	operator double ()const
	{
		return num / (den * 1.0);	//两个int相除要乘1.0
		//分数到double强制转换（不能写返回类型）
	}
	operator int ()const
	{
		return num / den;	//转换成整数刚好直接用取整
	}
	Fraction& operator ++ ();
		//前置自增重载，后置与自减相似，所以只写一个
	Fraction operator + (const Fraction& fac)const;
		//左分数右分数相加
	Fraction operator - (const Fraction& fac)const;
		//左分数右分数相减
	Fraction operator * (const Fraction& fac)const;
		//左分数右分数相乘
	Fraction operator / (const Fraction& fac)const;
		//左分数右分数相除
	Fraction operator + (double number)const;
		//左分数右小数相加
	Fraction operator - (double number);
		//左分数右小数相减
	Fraction operator * (double number);
		//左分数右小数相乘
	Fraction operator / (double number);
		//左分数右小数相除
	int operator == (const Fraction& fac)const;
	static int maxCommonDivisor(int max, int min);
		//求最大公约数
	friend ostream& operator << 
			(ostream& out, const Fraction& fra);
						//输出重载，可以直接输出对象
	friend istream& operator >> 
			(istream& in, Fraction& fra);
						//输入重载，可以直接输入对象
	~Fraction(){};
private:
	int num;	//分子
	int den;	//分母
};

Fraction::Fraction(int numNew, int denNew)
{
	if((numNew>0 && denNew<0) || (numNew<0 && denNew<0))
	{
		num = -numNew;
		den = -denNew;	//分子分母符号规约化
	}
	else
	{
		num = numNew;
		den = denNew;
	}
	int divisor = maxCommonDivisor(num, den);
	num /= divisor;
	den /= divisor;	//分子分母规约化

}

int Fraction::maxCommonDivisor(int max, int min)
{
	int temp, r;
	if(max < min)
	{
		temp = max;
		max = min;
		min = temp;	//保证max比min大
	}
	while(r != 0)
	{
		r = max % min;
		max = min;
		min = r;
	}
	return max;
}

Fraction::Fraction(double number)
{
	num = (int)(100 * number);	//分子就是小数乘100取整
	den = 100;	//分母是100，之后利用构造函数进行规约化
	int divisor = maxCommonDivisor(num, den);
	num /= divisor;
	den /= divisor;
}

Fraction& Fraction::operator ++()
{
	++num;
	++den;	//分子分母分别自加
	int divisor = maxCommonDivisor(num, den);
	num /= divisor;
	den /= divisor;
	return *this;	//返回当前对象
}

Fraction Fraction::operator + (const Fraction& fac)const
{
	return Fraction(num/(den*1.0)+fac.num /(fac.den*1.0));
}

Fraction Fraction::operator - (const Fraction& fac)const
{
	return Fraction(num/(den*1.0)-fac.num /(fac.den*1.0));
}

Fraction Fraction::operator * (const Fraction& fac)const
{
	return Fraction(num/(den*1.0)*fac.num /(fac.den*1.0));
}

Fraction Fraction::operator / (const Fraction& fac)const
{
	return Fraction(num/(den*1.0)/(fac.num /(fac.den*1.0)));
}

Fraction Fraction::operator + (double number)const
{
	return Fraction(num/(den*1.0) + number);
}

Fraction Fraction::operator - (double number)
{
	return Fraction(num/(den*1.0) - number);
}

Fraction Fraction::operator * (double number)
{
	return Fraction(num/(den*1.0) * number);
}

Fraction Fraction::operator / (double number)
{
	return Fraction(num/(den*1.0) / number);
}

ostream& operator << (ostream& out, const Fraction& fra)
{
	out<<"The fraction is "<<fra.num<<"/"<<fra.den<<endl;
	return out;	
}

istream& operator >> (istream& in, Fraction& fra)
{
	in>>fra.num>>fra.den;
	return in;
}

int main()
{
	//cout<<Fraction::maxCommonDivisor(8,4)<<endl;
	Fraction fra1(20, 100);
	Fraction fra2(2.22);
	cout<<fra1<<fra2;	
		//因为重载的时候末尾已经有endl所以这里不需要
	cout<<(double)fra2<<endl;	//double强制转换
	cout<<(int)fra2<<endl;		//int强制转换
	cout<<++fra2;
	Fraction fra3;
	cin>>fra3;
	cout<<fra3<<endl;
	Fraction fra4(fra1 + fra2);
	cout<<fra4<<endl;
	cout<<((double)fra1>=(double)fra2)<<endl;
	cout<<fra1+1<<endl;
	return 0;
}