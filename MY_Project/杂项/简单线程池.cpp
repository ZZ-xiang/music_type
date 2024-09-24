#include<iostream>
#include<condition_variable>
#include<mutex>
#include<thread>

using namespace std;

static int a = 0;

//���廥����
mutex m;

//������������
condition_variable cond;

//����������ģ��
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

//����������ģ��
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
			//cout << "�̳߳�����Դ" <<endl;
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
