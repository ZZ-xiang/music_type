#include<iostream>
#include<stack>
#include<deque>
#include<string>
using namespace std;
int main() {
	stack<string> s;
	//临时栈
	stack<string> temp; 
	s.push("hello");
	s.push("World");
	s.push("!");
	while (!s.empty()) {
		cout<<s.top()<<endl;
		temp.push(s.top());
		s.pop();
	}
	cout<< "入栈前大小："<<s.size()<<endl; 
	while(!temp.empty()){
		s.push(temp.top());
		temp.pop();
	}
	cout<< "入栈后大小："<<s.size()<<endl; 
	
	//默认拷贝 
	stack<string> stk2(s);
	while(!stk2.empty())
	{
		cout << stk2.top()<<endl;
		temp.push(stk2.top());
		stk2.pop();
	}
}
