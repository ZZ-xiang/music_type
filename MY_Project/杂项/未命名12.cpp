#include <iostream>
#include <string>
using namespace std;

class P1{
	private:
		int age;
		string name;
	public:
		virtual void getName()
		{
			cout << "P1::i am xiaozhou"<<endl;
		}	
		virtual void getAge()
		{
			cout << "P1::i am 21 years old"<<endl;
			
		}
};

class P2 : public P1{
	private:
		int age;
		string name;
	public:
		void getName()
		{
			cout << "P2::i am xiaozhou"<<endl;
		}	
		void getAge()  
		{
			cout << "P2::i am 21 years old"<<endl;;
		}
};

int main() {
	P1* p1 = new P2();
	P2* p2 = new P2();
	p1->getAge();
	p2->getAge();
	
	return 0;
}
