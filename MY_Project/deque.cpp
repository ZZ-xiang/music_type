#include<iostream>
#include<algorithm>
#include<deque>
using namespace std;
typedef string Type;

int main() {
	//双端队列
	/*
		允许在两端进行删除加入操作
		大小可自动调整，类似于vector
		允许使用下标[] ar()随机访问，类似于vector
		deque的内存分配是分段的，适合频繁的加入删除
	*/
	deque<Type> queue;
	for (int i = 0; i <= 10; ++i) {
		//TODO
		queue.push_back("i");
	}
	queue.push_front("100");

	for (auto i = queue.begin(); i != queue.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;

	//默认快排
//	sort(queue.begin(), queue.end(), [](int a, int b) {
//		return a > b;
//	});
//	for (auto i = queue.begin(); i != queue.end(); i++) {
//
//		cout << *i << " ";
//	}
//	cout << endl;

	queue.pop_front();
	queue.pop_back();
	for (auto i = queue.begin(); i != queue.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;
	
	Type value = queue.at(0);
	cout<<value<<endl;
	value = queue[1];
	cout<<value<<endl;
	
	//访问头尾元素
	Type head = queue.front();
	Type tail = queue.back(); 
	cout<<"头："<<head<<"尾："<<tail<<endl;
	
	//获取大小
	cout<<queue.size()<<endl;
	
	//简便的遍历方式 
	for(const auto &i:queue)
	{
		cout<<i<<" ";
	}cout<<endl;
	
	//清空内容并遍历 
	queue.clear();
	for(const auto&i:queue)
	{
		cout<<i<<" ";
	} cout<<endl;
	
}
