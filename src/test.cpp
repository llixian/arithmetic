
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
{ // 运算符优先级表   
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
}SC;       //StackChar类型的结点SC  
  
typedef struct StackFloat  
{  
    float f;   
    struct StackFloat *next;   
}SF;       //StackFloat类型的结点SF  
  
SC *Push(SC *s,char c)          //SC类型的指针Push，返回p  
{  
    SC *p=(SC*)malloc(sizeof(SC));   
    p->c=c;   
    p->next=s;   
    return p;   
}   
  
SF *Push(SF *s,float f)        //SF类型的指针Push，返回p  
{  
    SF *p=(SF*)malloc(sizeof(SF));   
    p->f=f;   
    p->next=s;   
    return p;   
}   
 
SC *Pop(SC *s)    //SC类型的指针Pop  
{  
    SC *q=s;   
    s=s->next;   
    free(q);   
    return s;   
}   
  
SF *Pop(SF *s)      //SF类型的指针Pop  
{  
    SF *q=s;   
    s=s->next;   
    free(q);   
    return s;   
}   
  
float Operate(float a,unsigned char theta, float b)      //计算函数Operate  
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
    // 算术表达式求值的算符优先算法  
    // 设OPTR和OPND分别为运算符栈和运算数栈，OP为运算符集合   
    SC *OPTR=NULL;       // 运算符栈，字符元素   
    SF *OPND=NULL;       // 运算数栈，实数元素   
    char TempData[20];   
    float Data,a,b;   
    char theta,*c,Dr[]={'#','\0'};   
    OPTR=Push(OPTR,'#');   
    c=strcat(MyExpression,Dr);   
    strcpy(TempData,"\0");//字符串拷贝函数   
    while (*c!= '#' || OPTR->c!='#')  
    {   
        if (!In(*c, OPSET))  
        {   
            Dr[0]=*c;   
            strcat(TempData,Dr);           //字符串连接函数   
            c++;   
            if (In(*c, OPSET))  
            {   
                Data=atof(TempData);       //字符串转换函数(double)   
                OPND=Push(OPND, Data);   
                strcpy(TempData,"\0");   
            }   
        }   
        else    // 不是运算符则进栈   
        {  
            switch (precede(OPTR->c, *c))  
            {  
            case '<': // 栈顶元素优先级低   
                OPTR=Push(OPTR, *c);   
                c++;   
                break;   
            case '=': // 脱括号并接收下一字符   
                OPTR=Pop(OPTR);   
                c++;   
                break;   
            case '>': // 退栈并将运算结果入栈   
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

//符号生成
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
 //把数字转换成字符串型
 string int_string(int number)
 {
    char str[200];
    itoa(number,str,10);
    string str_=str;
    return str_; 
  } 
  //真分数合成一个字符串
 string combination1(string str1,string str2,char k) 
 {
     string equation;
     equation='('+str1+k+str2+')';
     return equation;
 } 
 //新生成一个数
string create_num(int proper_fs,int range)
{ 
    int num,num1,num2,fs;
    string str_num,str_num1,str_num2;
      num=random()%range+1;
    str_num=int_string(num);
    if(proper_fs==1)
    {
        fs=random()%3;
        if(fs==1)//判断是否生成真分数  
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
 //运算式转换成一个字符串
 string combination(string str1,string str2,char k) 
 {
     string equation;
     equation=str1+k+str2;
     return equation;
 }

//得出正确答案 
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
    //用堆栈解决。。。 
    ans=EvaluateExpression(num);
    return ans;
	delete[]num; 
} 
 //主函数 
int main()
{
    srand((int)time(NULL));  //设置时间种子 ，使得程序每次运行的结果都不同 
    int num1,num2,num3,num4,count,n,change,amount,shuchu,range,j,repeat=0,bracket,proper_fs,right=0,wrong=0;
    string str_num1,str_num2,temp;
    float Answer,InputAns;
    cout<<"有无乘除法？1有，0没有："<<endl;
    cin>>n;
    cout<<"是否有括号？1有，0没有："<<endl;
    cin>>bracket; 
    cout<<"是否有真分数？1有，0没有："<<endl;
    cin>>proper_fs; 
    cout<<"请输入数字范围："<<endl;
    cin>>range; 
    cout<<"请输入出题数量："<<endl;
    cin>>amount; 
    //string Equation[amount];
	string *Equation=new string[amount];
    char symbol;
    cout<<amount<<"道四则运算题如下："<<endl; 
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
        //判断是否重复
         for(j=0;j<i;j++)
         {
             if(Equation[j]==Equation[i])
             {
                i=i-1;
                repeat=1;
                break;
             }
         }
         if(repeat!=1)//若不重复，则输出 
         {     
            cout<<Equation[i]<<"=";
            //判断结果是否正确
            cin>>InputAns;
            Answer=get_ans(Equation[i]);
            Answer*=100;
            int temp=(int)Answer;
            Answer=((double)temp)/100.00;
            if(InputAns==Answer)
            {
                cout<<"回答正确！"; 
                right++;
            }
            else
            {
                cout<<"回答错误！正确答案为";
                cout<<setprecision(2)<<fixed<<Answer;
                wrong++;
            } 
            cout<<endl;
         }
    }
    cout<<"一共答对"<<right<<"道题，答错"<<wrong<<"道题。"<<endl; 
	delete[]Equation;
}