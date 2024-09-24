#include<iostream>
#include<string>
#include<bitset>
#include <cmath>

using namespace std;
void swap(int &a,int &b);
int binary_to_decimal(const string& binary_str);
string decimal_to_binary(int decimal);
void swap(int &a,int &b)
{
	int temp = 0;
	temp = a;
	a = b;
	b = temp;
}

//算法写法
int binary_to_decimal(const string& binary_str)
{
	int decimal = 0;
	int len = binary_str.length();
	for(int i=0;i<len;i++)
	{
		if(binary_str[i] == '0')
		{
			decimal *= 2;
		}
		else if(binary_str[i] == '1')
		{
			decimal = 2*decimal + 1;  
		}
		else
		{
			cout << "您输入的是什么^...^符号" << endl;
		}
	}
	
	return decimal;
} 

string decimal_to_binary(int decimal)
{
	if(decimal == 0)
	{
		return "0";
	}
	
	string s;
	
	while(decimal > 0)
	{
		int flag = decimal % 2;
		s.insert(s.begin(),flag + '0'); //数字转化为字符然后用字符串接受
		decimal /= 2; 
	}
	
	return s;
}

int main()
{
	int number=8;
	string bin("11001111001110");
	
	//十进制转二进制 
	//快速调用库写法 
	string binary = bitset<8>(number).to_string();
	cout << binary  <<endl;
	
	//算法写法:
	string st = decimal_to_binary(number);
	cout << st << endl;
	
	
	
	
	//二进制转十进制
	//调用库
	bitset<32> bits(bin);
	int shi = bits.to_ulong();
	cout << shi << endl;
	
	//使用算法解决 
	int b = binary_to_decimal(bin);
	cout << b << endl;
	
	
	//十进制转16进制
	cout << hex;
	cout << number << endl; 	
	
	return 0;
}

