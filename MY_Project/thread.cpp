#include <iostream>
#include <vector>
#include <list>
#include <thread>
#include <mutex>  //���뻥����ͷ�ļ�
using namespace std;

class A {
	public:
		//������Ϣ��ģ����Ϣ���ϲ���
		void insertMsg() {
			for (int i = 0; i < 100; i++) {
				cout << "����һ����Ϣ:" << i << endl;
				my_mutex1.lock(); //���1
				my_mutex2.lock(); //���2
				Msg.push_back(i);
				my_mutex2.unlock();
				my_mutex1.unlock();
			}
		}
		//��ȡ��Ϣ
		void readMsg() {
			int MsgCom;
			for (int i = 0; i < 100; i++) {
				MsgCom = MsgLULProc(i);
				if (MsgLULProc(MsgCom)) {
					//������Ϣ��
					cout << "��Ϣ�Ѷ���" << MsgCom << endl;
				} else {
					//��Ϣ��ʱΪ��
					cout << "��ϢΪ��" << endl;
				}
			}
		}
		//�ӽ�������
		bool MsgLULProc(int &command) {
			int curMsg;
			my_mutex1.lock();   //���3
			my_mutex2.lock();   //���4
			if (!Msg.empty()) {
				//��ȡ��Ϣ������ɾ��
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
		std::list<int> Msg;  //��Ϣ����
		std::mutex my_mutex1; //����������1
		std::mutex my_mutex2; //����������2
};

int main() {
	A a;
	//����һ��������Ϣ�߳�
	std::thread insertTd(&A::insertMsg, &a); //����Ҫ�������ñ�֤��ͬһ������
	//����һ����ȡ��Ϣ�߳�
	std::thread readTd(&A::readMsg, &a); //����Ҫ�������ñ�֤��ͬһ������
	insertTd.join();
	readTd.join();
	return 0;
}
