#include<iostream>
#include<stack>
#include<deque>
#include<string>
using namespace std;
int main() {
	stack<string> s;
	//��ʱջ
	stack<string> temp; 
	s.push("hello");
	s.push("World");
	s.push("!");
	while (!s.empty()) {
		cout<<s.top()<<endl;
		temp.push(s.top());
		s.pop();
	}
	cout<< "��ջǰ��С��"<<s.size()<<endl; 
	while(!temp.empty()){
		s.push(temp.top());
		temp.pop();
	}
	cout<< "��ջ���С��"<<s.size()<<endl; 
	
	//Ĭ�Ͽ��� 
	stack<string> stk2(s);
	while(!stk2.empty())
	{
		cout << stk2.top()<<endl;
		temp.push(stk2.top());
		stk2.pop();
	}
}
