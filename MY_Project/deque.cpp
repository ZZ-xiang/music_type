#include<iostream>
#include<algorithm>
#include<deque>
using namespace std;
typedef string Type;

int main() {
	//˫�˶���
	/*
		���������˽���ɾ���������
		��С���Զ�������������vector
		����ʹ���±�[] ar()������ʣ�������vector
		deque���ڴ�����Ƿֶεģ��ʺ�Ƶ���ļ���ɾ��
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

	//Ĭ�Ͽ���
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
	
	//����ͷβԪ��
	Type head = queue.front();
	Type tail = queue.back(); 
	cout<<"ͷ��"<<head<<"β��"<<tail<<endl;
	
	//��ȡ��С
	cout<<queue.size()<<endl;
	
	//���ı�����ʽ 
	for(const auto &i:queue)
	{
		cout<<i<<" ";
	}cout<<endl;
	
	//������ݲ����� 
	queue.clear();
	for(const auto&i:queue)
	{
		cout<<i<<" ";
	} cout<<endl;
	
}
