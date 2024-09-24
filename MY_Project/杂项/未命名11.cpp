#include<iostream>
#include<stack>
#include<string>
using namespace std;
string nums = "0123456789";
//�ȽϺ��������ڱȽϵ�ǰ��������ջ�������������ȼ�
//�����ǰ���������ȼ�����ջ�����ȼ�������false
//���ջ��������Ϊ������(
//�����ǰ���������ȼ�С��ջ�����ȼ���true
//��Ҫ����������Ҽ���˳�������ǰ��������ջ��������Ϊͬ����ϵ������true
//����true˵����ʱ��Ҫ��ջ�����������������ڼ���
bool cmp(char top, char now){
    if(top == '('){
        return false;
    }else if((top == '-' || top == '+') && (now == '*' || now == '/')){
        return false;
    }
    return true;
}
//���㣬������ջ�е����������֣�������ջ�е���������
void calculate(stack<double> &num,stack<char> &op){
//     ����ջ�����ֵ�˳��Ҳ��Ҫ��
//     ��һ�������������ں��棬�ڶ�����������ǰ��
    double b = num.top();
    num.pop();
    double a = num.top();
    num.pop();
    char c = op.top();
    op.pop();
    if(c == '+') a = a+b;
    else if(c == '-') a = a-b;
    else if(c == '*') a = a*b;
    else if(c == '/') a = a/b;
    //�������������ջ
    num.push(a);
    return ;
}
int main(void){
    string s;
    while(getline(cin, s)){
        //����ջ
        stack<double> num_stk;
        //������ջ
        stack<char> op_stk;
        //Ԥ��������ʽ������������
        op_stk.push('(');
        s += ')';
        //��ʽ�ĵ�һ��Ӧ��������
        bool isNextOp = false;
        for(int i=0; i<s.size(); ++i){
            //�����ŵĻ���ֱ��ѹ�������ջ,������С���Ŷ�����С���Ŵ���
            if(s[i] == '(' || s[i] == '[' || s[i] == '{'){
                op_stk.push('(');
            }
            //�����ŵĻ��Ϳ��Կ�ʼ���㣬ֱ��������֮��Ӧ��������
            else if(s[i] == ')' || s[i] == ']' || s[i] == '}'){
                while(op_stk.top() != '(') //����
                    calculate(num_stk,op_stk);
                //������ʱ�ģ�
                op_stk.pop();
            }
            //�������⣬���ֺͲ�����Ӧ���Ǽ�����еģ�������ʽ�ĵ�һ��Ӧ��������
            //��û�����ţ���Ҫ���ǲ��������ȼ�����,�����Ǵ������Ҽ���
            else if(isNextOp){
                while(cmp(op_stk.top(),s[i])){
                    //����
                    calculate(num_stk,op_stk);
                }
                op_stk.push(s[i]);
                isNextOp = false;
            }
            //�����ִ��ַ�������ȡ����
            else{
                int j = i;
                //+ -���ſ�������������
                if(s[j] == '+' || s[j] == '-') ++i;
                //���ֿ����ж�λ����0-9��
                while(nums.find(s[i]) != nums.npos) ++i;
                //i��j֮����ַ���Ϊ����
                //��������ȡ����ѹ������ջ
                
                //num_stk.push(stod(nums.substr(j,i-j)));
                num_stk.push((double)stoi(s.substr(j,i-j)));
                --i;
                //��ǰΪ���֣�������һ��Ϊ������
                isNextOp = true;
            }
        }
        //����ջ����Ԫ�ؼ�Ϊ�����
        cout<<num_stk.top()<<endl;
    }
    return 0;
}
