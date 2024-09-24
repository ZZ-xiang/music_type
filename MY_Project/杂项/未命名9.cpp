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

//�㷨д��
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
			cout << "���������ʲô^...^����" << endl;
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
		s.insert(s.begin(),flag + '0'); //����ת��Ϊ�ַ�Ȼ�����ַ�������
		decimal /= 2; 
	}
	
	return s;
}

int main()
{
	int number=8;
	string bin("11001111001110");
	
	//ʮ����ת������ 
	//���ٵ��ÿ�д�� 
	string binary = bitset<8>(number).to_string();
	cout << binary  <<endl;
	
	//�㷨д��:
	string st = decimal_to_binary(number);
	cout << st << endl;
	
	
	
	
	//������תʮ����
	//���ÿ�
	bitset<32> bits(bin);
	int shi = bits.to_ulong();
	cout << shi << endl;
	
	//ʹ���㷨��� 
	int b = binary_to_decimal(bin);
	cout << b << endl;
	
	
	//ʮ����ת16����
	cout << hex;
	cout << number << endl; 	
	
	return 0;
}

