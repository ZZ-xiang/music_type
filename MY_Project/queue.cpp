#include<iostream>
#include<queue>

using namespace std;
int main()
//默认构造方式构造一个队列容器
{
	queue<int> que;
	queue<int> temp;
	que.push(66);
	que.push(77);
	que.push(88);
	que.push(55);
	while(!que.empty())
	{
		cout<<que.front()<<endl;
		temp.push(que.front());
		que.pop();
	}
	
	cout << que.size() << endl;
		
	
	while(!temp.empty())
	{
		que.push(temp.front());
		temp.pop();
	}
	
	
	cout << que.size() << endl;
	que.pop();
	que.pop();
	
	
	
	return 0;
}
