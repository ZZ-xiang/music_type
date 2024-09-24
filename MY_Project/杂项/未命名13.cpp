#include <iostream>
#include<string.h>
#include<graphics.h>

using namespace std;
//typedef int ElemType;

template<typename ElemType>
class Stack {
		ElemType* items;
		ElemType Stacksize;
		ElemType top;
	public:
		Stack(int size): Stacksize{size}, top{0} {
			items = new int[Stacksize + 1];
		} 	//构造函数
		~Stack() {
			delete[] items;
			items = nullptr;
		} //析构函数
		bool isfull() const {
			return top == Stacksize;
		}
		bool isEmpty() const {
			return top == 0;
		}
		bool pushStack(const ElemType&item)
		{
			if(top < Stacksize){
				//TODO
				items[top++] = item;
				return true;
			}
			return false;
		}
		bool popStack(ElemType &item)
		{
			if(!isEmpty())
			{
				item = items[top-1];
				cout << item << endl;
				item = items[--top];
				return true;
			}
			return false;
		}
};

int main() {
	int item;
	Stack<int> stack(4);
	stack.pushStack(7);
	stack.pushStack(7);
	stack.pushStack(6);
	stack.pushStack(2);
	stack.popStack(item);
	stack.popStack(item);
	stack.popStack(item);
}

