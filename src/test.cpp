
#include<iostream>
#include<stdlib.h>
#include<iomanip>
#include<time.h>  
#include<stdio.h> 
#include<string>
#include"math.h"  
#define true 1   
#define false 0   
#define OPSETSIZE 7  
#define random() (rand()%100000)  
#include"string.h"   
typedef int Status;
using namespace std;   
  
unsigned char Prior[7][7] =  
{ // ��������ȼ���   
    // '+' '-' '*' '/' '(' ')' '#'    
    /*'+'*/'>','>','<','<','<','>','>',  
    /*'-'*/'>','>','<','<','<','>','>',  
    /*'*'*/'>','>','>','>','<','>','>', 
    /*'/'*/'>','>','>','>','<','>','>',
    /*'('*/'<','<','<','<','<','=',' ', 
    /*')'*/'>','>','>','>',' ','>','>',
    /*'#'*/'<','<','<','<','<',' ','=', 
};   
  
typedef struct StackChar  
{  
    char c;   
    struct StackChar *next;   
}SC;       //StackChar���͵Ľ��SC  
  
typedef struct StackFloat  
{  
    float f;   
    struct StackFloat *next;   
}SF;       //StackFloat���͵Ľ��SF  
  
SC *Push(SC *s,char c)          //SC���͵�ָ��Push������p  
{  
    SC *p=(SC*)malloc(sizeof(SC));   
    p->c=c;   
    p->next=s;   
    return p;   
}   
  
SF *Push(SF *s,float f)        //SF���͵�ָ��Push������p  
{  
    SF *p=(SF*)malloc(sizeof(SF));   
    p->f=f;   
    p->next=s;   
    return p;   
}   
 
SC *Pop(SC *s)    //SC���͵�ָ��Pop  
{  
    SC *q=s;   
    s=s->next;   
    free(q);   
    return s;   
}   
  
SF *Pop(SF *s)      //SF���͵�ָ��Pop  
{  
    SF *q=s;   
    s=s->next;   
    free(q);   
    return s;   
}   
  
float Operate(float a,unsigned char theta, float b)      //���㺯��Operate  
{  
    switch(theta)  
    {  
    case '+': return a+b;   
    case '-': return a-b;   
    case '*': return a*b;   
    case '/': return a/b;   
    default : return 0;   
    }   
}   
  
char OPSET[OPSETSIZE]={'+','-','*','/','(',')','#'};   
  
Status In(char Test,char *TestOp)  
{  
    int Find=false;   
    for (int i=0; i< OPSETSIZE; i++)  
    {  
        if(Test == TestOp[i])  
            Find= true;   
    }   
    return Find;   
}   
  
Status ReturnOpOrd(char op,char *TestOp)  
{   
    for(int i=0; i< OPSETSIZE; i++)  
    {  
        if (op == TestOp[i])  
            return i;  
    }  
}  
  
char precede(char Aop, char Bop)  
{   
    return Prior[ReturnOpOrd(Aop,OPSET)][ReturnOpOrd(Bop,OPSET)];   
}   
  
float EvaluateExpression(char* MyExpression)  
{   
    // �������ʽ��ֵ����������㷨  
    // ��OPTR��OPND�ֱ�Ϊ�����ջ��������ջ��OPΪ���������   
    SC *OPTR=NULL;       // �����ջ���ַ�Ԫ��   
    SF *OPND=NULL;       // ������ջ��ʵ��Ԫ��   
    char TempData[20];   
    float Data,a,b;   
    char theta,*c,Dr[]={'#','\0'};   
    OPTR=Push(OPTR,'#');   
    c=strcat(MyExpression,Dr);   
    strcpy(TempData,"\0");//�ַ�����������   
    while (*c!= '#' || OPTR->c!='#')  
    {   
        if (!In(*c, OPSET))  
        {   
            Dr[0]=*c;   
            strcat(TempData,Dr);           //�ַ������Ӻ���   
            c++;   
            if (In(*c, OPSET))  
            {   
                Data=atof(TempData);       //�ַ���ת������(double)   
                OPND=Push(OPND, Data);   
                strcpy(TempData,"\0");   
            }   
        }   
        else    // ������������ջ   
        {  
            switch (precede(OPTR->c, *c))  
            {  
            case '<': // ջ��Ԫ�����ȼ���   
                OPTR=Push(OPTR, *c);   
                c++;   
                break;   
            case '=': // �����Ų�������һ�ַ�   
                OPTR=Pop(OPTR);   
                c++;   
                break;   
            case '>': // ��ջ������������ջ   
                theta=OPTR->c;OPTR=Pop(OPTR);   
                b=OPND->f;OPND=Pop(OPND);   
                a=OPND->f;OPND=Pop(OPND);   
                OPND=Push(OPND, Operate(a, theta, b));   
                break;   
            } //switch  
        }   
    } //while   
    return OPND->f;   
} //EvaluateExpression  

//��������
char create_symbol(int n)
{
    int n1,j;    
    char symbol[1];
    if(n==0)
    {
        n1=2;
    }
    else if(n=1)
    {
        n1=4;
    }
    j=random()%n1;
    if(j==0) symbol[0]='+';
    else if(j==1) symbol[0]='-';
    else if(j==2) symbol[0]='*';
    else symbol[0]='/';
    return symbol[0];      
 } 
 //������ת�����ַ�����
 string int_string(int number)
 {
    char str[200];
    itoa(number,str,10);
    string str_=str;
    return str_; 
  } 
  //������ϳ�һ���ַ���
 string combination1(string str1,string str2,char k) 
 {
     string equation;
     equation='('+str1+k+str2+')';
     return equation;
 } 
 //������һ����
string create_num(int proper_fs,int range)
{ 
    int num,num1,num2,fs;
    string str_num,str_num1,str_num2;
      num=random()%range+1;
    str_num=int_string(num);
    if(proper_fs==1)
    {
        fs=random()%3;
        if(fs==1)//�ж��Ƿ����������  
        {    
            for(;;)
            {
                num1=random()%range+1;
                 num2=random()%range+1;
                if(num1<num2) break;
            }
            str_num1=int_string(num1);
            str_num2=int_string(num2);
            str_num=combination1(str_num1,str_num2,'/');
        }
    }
    return str_num; 
  } 
 //����ʽת����һ���ַ���
 string combination(string str1,string str2,char k) 
 {
     string equation;
     equation=str1+k+str2;
     return equation;
 }

//�ó���ȷ�� 
float get_ans(string str)
{
    int len;
    float ans;
    len=str.length();
    //char num[len];
	char *num=new char[len];
    for(int j=0;j<len;j++)
    {
        num[j]=str[j];
    }
    //�ö�ջ��������� 
    ans=EvaluateExpression(num);
    return ans;
	delete[]num; 
} 
 //������ 
int main()
{
    srand((int)time(NULL));  //����ʱ������ ��ʹ�ó���ÿ�����еĽ������ͬ 
    int num1,num2,num3,num4,count,n,change,amount,shuchu,range,j,repeat=0,bracket,proper_fs,right=0,wrong=0;
    string str_num1,str_num2,temp;
    float Answer,InputAns;
    cout<<"���޳˳�����1�У�0û�У�"<<endl;
    cin>>n;
    cout<<"�Ƿ������ţ�1�У�0û�У�"<<endl;
    cin>>bracket; 
    cout<<"�Ƿ����������1�У�0û�У�"<<endl;
    cin>>proper_fs; 
    cout<<"���������ַ�Χ��"<<endl;
    cin>>range; 
    cout<<"���������������"<<endl;
    cin>>amount; 
    //string Equation[amount];
	string *Equation=new string[amount];
    char symbol;
    cout<<amount<<"���������������£�"<<endl; 
    for(int i=0;i<amount;i++)
    {    
        count=random()%3+2;
        str_num1=create_num(proper_fs,range);
        str_num2=create_num(proper_fs,range);
        symbol=create_symbol(n);
        Equation[i]=combination(str_num1,str_num2,symbol);
        if(count>2)
        {
            for(count;count>2;count--)
            {
                symbol=create_symbol(n);
                str_num1=Equation[i];
                if(bracket==1)
                {
                    change=random()%3;
                    if(change==0)
                    {
                       str_num1='('+str_num1+')';
                     }
                } 
                symbol=create_symbol(n);
                str_num2=create_num(proper_fs,range);    
                change=random()%2;
                if(change==0)
                {
                    temp=str_num1;
                    str_num1=str_num2;
                    str_num2=temp;
                }                
                Equation[i]=combination(str_num1,str_num2,symbol);
            }
        }
        //�ж��Ƿ��ظ�
         for(j=0;j<i;j++)
         {
             if(Equation[j]==Equation[i])
             {
                i=i-1;
                repeat=1;
                break;
             }
         }
         if(repeat!=1)//�����ظ�������� 
         {     
            cout<<Equation[i]<<"=";
            //�жϽ���Ƿ���ȷ
            cin>>InputAns;
            Answer=get_ans(Equation[i]);
            Answer*=100;
            int temp=(int)Answer;
            Answer=((double)temp)/100.00;
            if(InputAns==Answer)
            {
                cout<<"�ش���ȷ��"; 
                right++;
            }
            else
            {
                cout<<"�ش������ȷ��Ϊ";
                cout<<setprecision(2)<<fixed<<Answer;
                wrong++;
            } 
            cout<<endl;
         }
    }
    cout<<"һ�����"<<right<<"���⣬���"<<wrong<<"���⡣"<<endl; 
	delete[]Equation;
}