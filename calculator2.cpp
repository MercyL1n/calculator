//@name calculator
//@author lmy
//@date 20190307
//function:������ʽ(֧�ּӼ��˳�)���������

#include<iostream>
#include<string>
#include<stack>  
#include<cmath>

using namespace std;

int In(char ch, char str[]);
char Precede(char a, char b);
float Operator (float a, char theta, float b);
void Calculator();
//�����
char OP[] = {'+','-','*','/','(',')','=','^'};
//��������ȼ�
char level[8][9] = {">><<<>><",">><<<>><",">>>><>><",">>>><>><","<<<<<= <",">>>> >>>","<<<<< =<",">>>><>>>"};

int main() {
    char ch;
    cout<<"������ʽ,����\"1.5+2^2=\""<<endl;//��ʾ
    cout<<"֧�ּ�(+)��(-)��(*)��(/)������(^)"<<endl;
    Calculator();
    ch = getchar();
    while(ch == '\n'){
        Calculator();
        ch = getchar();
    }
    return 0;
}
//�ж��Ƿ����������,������λ��
int In(char ch, char str[]){
    for(int i=0; str[i] != 0; i++){
        if(ch == str[i]) return i;
    }
    return -1;
}
//�ж��������ȼ�
char Precede(char a, char b) {
    int i = In(a,OP);
    int j = In(b,OP);
    return level[i][j];
}
//����
float Operator(float a, char theta, float b) {
    if(theta == '+')return a + b;
    if(theta == '-')return a - b;
    if(theta == '*')return a * b;
    if(theta == '/')return a / b;
    if(theta == '^')return pow(a,b);
}

void Calculator() {
    char ch;
    char theta;//�������
    float a = 0;
    float b = 0;//������
    string temp = "";
    //����ջOPTR��������,����OPND�������
    stack<char>OPTR;
    stack<float>OPND;    
    cin>>ch;//����
    OPTR.push('=');//������������
    while(ch!='='||OPTR.top() != '='){
        if(ch == ' '){//ȥ�ո�
            cin>>ch;
            continue;
        }

        if(In(ch,OP) == -1){//���ֲ���
            while(ch <= '9' && ch >= '0'|| ch == '.'){
                temp.append(1,ch);//�����ִ���temp
                cin>>ch;    
            }//��������ַ���ת��Ϊ����
            OPND.push(atof(temp.c_str()));//������ջ
            temp.erase(temp.begin(),temp.end());//���temp
        }
        else {//���������
            switch (Precede(OPTR.top(),ch)){//�Ƚ����ȼ�
                case '<':
                    OPTR.push(ch);//����ǰ�ַ�ѹ��OPTRջ
                    cin>>ch;//������һ�ַ�
                    break;
                case '>':
                    //ȡ����������������
                    a = OPND.top();
                    OPND.pop();
                    b = OPND.top();
                    OPND.pop();
                    theta = OPTR.top();
                    OPTR.pop();
                    OPND.push(Operator(b,theta,a));
                    break;
                case '=':
                    OPTR.pop();//��ȥ
                    cin>>ch;//����
                    break;                    
            }  
        }
    }
    cout<<OPND.top()<<endl;
    getchar();
    cout<<"����س����� ,�������������˳�";
}