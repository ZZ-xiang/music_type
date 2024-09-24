#include<iostream>
#include<stack>
#include<string>
using namespace std;
string nums = "0123456789";
//比较函数，用于比较当前操作符和栈顶操作符的优先级
//如果当前操作符优先级大于栈顶优先级，返回false
//如果栈顶操作符为左括号(
//如果当前操作符优先级小于栈顶优先级，true
//还要满足从左往右计算顺序，如果当前操作符与栈顶操作符为同级关系，返回true
//返回true说明此时需要将栈顶操作符弹出，用于计算
bool cmp(char top, char now){
    if(top == '('){
        return false;
    }else if((top == '-' || top == '+') && (now == '*' || now == '/')){
        return false;
    }
    return true;
}
//计算，从数字栈中弹出两个数字，操作符栈中弹出操作符
void calculate(stack<double> &num,stack<char> &op){
//     数字栈中数字的顺序也有要求
//     第一个弹出的数字在后面，第二个弹出的在前面
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
    //将结果放入数字栈
    num.push(a);
    return ;
}
int main(void){
    string s;
    while(getline(cin, s)){
        //数字栈
        stack<double> num_stk;
        //操作符栈
        stack<char> op_stk;
        //预处理，将算式用括号括起来
        op_stk.push('(');
        s += ')';
        //算式的第一个应该是数字
        bool isNextOp = false;
        for(int i=0; i<s.size(); ++i){
            //左括号的话，直接压入操作符栈,将大中小括号都当做小括号处理
            if(s[i] == '(' || s[i] == '[' || s[i] == '{'){
                op_stk.push('(');
            }
            //右括号的话就可以开始计算，直到遇到与之对应的左括号
            else if(s[i] == ')' || s[i] == ']' || s[i] == '}'){
                while(op_stk.top() != '(') //计算
                    calculate(num_stk,op_stk);
                //弹出此时的（
                op_stk.pop();
            }
            //除括号外，数字和操作符应该是间隔排列的，而且算式的第一个应该是数字
            //若没有括号，需要考虑操作符优先级问题,并且是从左往右计算
            else if(isNextOp){
                while(cmp(op_stk.top(),s[i])){
                    //计算
                    calculate(num_stk,op_stk);
                }
                op_stk.push(s[i]);
                isNextOp = false;
            }
            //将数字从字符串中提取出来
            else{
                int j = i;
                //+ -符号可能是正负符号
                if(s[j] == '+' || s[j] == '-') ++i;
                //数字可能有多位，在0-9中
                while(nums.find(s[i]) != nums.npos) ++i;
                //i和j之间的字符即为数字
                //将数字提取，并压入数字栈
                
                //num_stk.push(stod(nums.substr(j,i-j)));
                num_stk.push((double)stoi(s.substr(j,i-j)));
                --i;
                //当前为数字，所以下一个为操作符
                isNextOp = true;
            }
        }
        //数字栈顶的元素即为最后结果
        cout<<num_stk.top()<<endl;
    }
    return 0;
}
