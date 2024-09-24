#include <iostream>
#include <vector>
#include <list>
#include <thread>
#include <mutex>  //引入互斥量头文件
using namespace std;

class A {
	public:
		//插入消息，模拟消息不断产生
		void insertMsg() {
			for (int i = 0; i < 100; i++) {
				cout << "插入一条消息:" << i << endl;
				my_mutex1.lock(); //语句1
				my_mutex2.lock(); //语句2
				Msg.push_back(i);
				my_mutex2.unlock();
				my_mutex1.unlock();
			}
		}
		//读取消息
		void readMsg() {
			int MsgCom;
			for (int i = 0; i < 100; i++) {
				MsgCom = MsgLULProc(i);
				if (MsgLULProc(MsgCom)) {
					//读出消息了
					cout << "消息已读出" << MsgCom << endl;
				} else {
					//消息暂时为空
					cout << "消息为空" << endl;
				}
			}
		}
		//加解锁代码
		bool MsgLULProc(int &command) {
			int curMsg;
			my_mutex1.lock();   //语句3
			my_mutex2.lock();   //语句4
			if (!Msg.empty()) {
				//读取消息，读完删除
				command = Msg.front();
				Msg.pop_front();

				my_mutex1.unlock();
				my_mutex2.unlock();
				return true;
			}
			my_mutex1.unlock();
			my_mutex2.unlock();
			return false;
		}
	private:
		std::list<int> Msg;  //消息变量
		std::mutex my_mutex1; //互斥量对象1
		std::mutex my_mutex2; //互斥量对象2
};

int main() {
	A a;
	//创建一个插入消息线程
	std::thread insertTd(&A::insertMsg, &a); //这里要传入引用保证是同一个对象
	//创建一个读取消息线程
	std::thread readTd(&A::readMsg, &a); //这里要传入引用保证是同一个对象
	insertTd.join();
	readTd.join();
	return 0;
}
