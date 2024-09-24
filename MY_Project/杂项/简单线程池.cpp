#include<iostream>
#include<condition_variable>
#include<mutex>
#include<thread>

using namespace std;

static int a = 0;

//定义互斥锁
mutex m;

//定义条件变量
condition_variable cond;

//定义生产者模型
void produce() {
	while (1) {
		//TODO
		m.lock();
		a++;
		cout << "produce:  " << a << endl;
		cond.notify_all();
		m.unlock();
		this_thread::sleep_for(chrono::milliseconds(300));

	}
}

//定义消费者模型
void comsumer() {
	while (1) {
		//TODO
		this_thread::sleep_for(chrono::milliseconds(100));
		unique_lock<mutex> mk{m};
		if (a > 0) {
			a--;
			cout << "comsumer:  " << a << endl;
		}
		else
		{
			//cout << "线程池无资源" <<endl;
			cond.wait(mk);
		}
	}
}

int main() {
	thread t1{produce};
	thread t2{produce};
	
	thread t3{comsumer};
	thread t4{comsumer};
	thread t5{comsumer};
	
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	
	return 0;
	
}
