//@name calculator
//@author lmy
//@date 20190307
//function:输入表达式(支持加减乘除)输出计算结果

#include<iostream>
#include<string>
#include<stack>  
#include<cmath>

using namespace std;

int In(char ch, char str[]);
char Precede(char a, char b);
float Operator (float a, char theta, float b);
//运算符
char OP[] = {'+','-','*','/','(',')','=','^'};
//运算符优先级
char level[8][9] = {">><<<>><",">><<<>><",">>>><>><",">>>><>><","<<<<<= <",">>>> >>>","<<<<< =<",">>>><>>>"};

int main() {
    char ch;
    char theta;//储存符号
    float a = 0;
    float b = 0;//两个数
    string temp = "";
    //定义栈OPTR存放运算符,定义OPND存放数字
    stack<char>OPTR;
    stack<float>OPND;

    OPTR.push('=');//用来结束计算
    cout<<"输入表达式,例如\"1.5+2^2=\""<<endl;//提示
    cout<<"支持加(+)减(-)乘(*)除(/)幂运算(^)"<<endl;
    cin>>ch;//读入

    while(ch!='='||OPTR.top() != '='){
        if(ch == ' '){//去空格
            cin>>ch;
            continue;
        }

        if(In(ch,OP) == -1){//数字部分
            while(ch <= '9' && ch >= '0'|| ch == '.'){
                temp.append(1,ch);//将数字存入temp
                cin>>ch;    
            }//将输入的字符串转化为数字
            OPND.push(atof(temp.c_str()));//存入数栈
            temp.erase(temp.begin(),temp.end());//清空temp
        }
        else {//运算符部分
            switch (Precede(OPTR.top(),ch)){//比较优先级
                case '<':
                    OPTR.push(ch);//将当前字符压入OPTR栈
                    cin>>ch;//读入下一字符
                    break;
                case '>':
                    //取出两个数进行运算
                    a = OPND.top();
                    OPND.pop();
                    b = OPND.top();
                    OPND.pop();
                    theta = OPTR.top();
                    OPTR.pop();
                    OPND.push(Operator(b,theta,a));
                    break;
                case '=':
                    OPTR.pop();//消去
                    cin>>ch;//读入
                    break;                    
            }  
        }
    }
    cout<<OPND.top();
    return 0;
}
//判断是否在运算符中,并返回位置
int In(char ch, char str[]){
    for(int i=0; str[i] != 0; i++){
        if(ch == str[i]) return i;
    }
    return -1;
}
//判断运算优先级
char Precede(char a, char b) {
    int i = In(a,OP);
    int j = In(b,OP);
    return level[i][j];
}
//计算
float Operator (float a, char theta, float b) {
    if(theta == '+')return a + b;
    if(theta == '-')return a - b;
    if(theta == '*')return a * b;
    if(theta == '/')return a / b;
    if(theta == '^')return pow(a,b);
}
