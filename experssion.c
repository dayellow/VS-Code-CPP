//输入表达式（只能输入正整数和加减乘除号和括号），输出小数点后保留两位的结果，当输入0后，程序结束
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stdbool.h>
double nstk[50];//数字栈
char sstk[50];//算符栈
int ntop=-1;//数字栈顶
int stop=-1;//算符栈顶
void nmake_empty(void)
{
    ntop=-1;
}
bool nis_empty(void)
{
    return ntop==-1;
}
bool nis_full(void)
{
    return ntop==50;
}
void npush(double i)
{
    if(!nis_full())
        nstk[++ntop]=i;
}
double npop(void)
{
    if(!nis_empty())
        return nstk[ntop--];
}
void npop2(int j,double num)
{
    if(nstk[j])
    {
        nstk[j++]=num;
        for(;j<ntop;++j)
        {
            nstk[j]=nstk[j+1];
        }
        --ntop;
    }
}


void smake_empty(void)
{
    stop=-1;
}
bool sis_empty(void)
{
    return stop==-1;
}
bool sis_full(void)
{
    return stop==50;
}
void spush(char i)
{
    if(!sis_full())
        sstk[++stop]=i;
}
char spop(void)
{
    if(!sis_empty())
        return nstk[stop--];
}

void spop1(int k)
{
    if(sstk[k])
    {
        for(;k<stop;++k)
        {
            sstk[k]=sstk[k+1];
        }
        --stop;
    }
}
int value(char exp)
{
    switch(exp)
    {
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        
    }
}
int main()
{
    char exp[50];
    while(scanf("%s",exp))
    {
        int judge=0;//判断无括号情况下符号优先顺序
        if(exp[0]=='0'&&!exp[1]) break;
        int i;
        for(i=0;exp[i];++i)
        {
            if(exp[i]>='0'&&exp[i]<='9')
            {
                int k;//整数位数
                double num=0;
                for(k=0;exp[i]>='0'&&exp[i]<='9';++i)
                {
                    for(k=0;exp[i]>='0'&&exp[i]<='9';++k,++i);
                    int j=--i;
                    for(double ten=1;k;--k,--j,ten*=10)
                    {
                        switch(exp[j])
                        {
                            case '0': break;
                            case '1': num+=ten;break;
                            case '2': num+=(ten*2);break;
                            case '3': num+=(ten*3);break;
                            case '4': num+=(ten*4);break;
                            case '5': num+=(ten*5);break;
                            case '6': num+=(ten*6);break;
                            case '7': num+=(ten*7);break;
                            case '8': num+=(ten*8);break;
                            case '9': num+=(ten*9);break;
                        }
                    }
                }
                --i;
                npush(num);
            }
            
            else if(exp[i]=='(') spush(exp[i]);
            else if(exp[i]!=')') 
            {
                if(sstk[stop]=='+'||sstk[stop]=='-'||sstk[stop]=='*'||sstk[stop]=='/')
                {
                    if(value(exp[i])<=value(sstk[stop]))
                    {
                        double num;
                        switch(sstk[stop])
                        {
                            case '+': num=nstk[ntop-1]+nstk[ntop];break;
                            case '-': num=nstk[ntop-1]-nstk[ntop];break;
                            case '*': num=nstk[ntop-1]*nstk[ntop];break;
                            case '/': num=nstk[ntop-1]/nstk[ntop];break;
                        }
                        npop(),npop(),npush(num);
                        spop(),spush(exp[i]);
                    }
                    else if(exp[i+1]>='0'&&exp[i+1]<='9')
                    {
                        spush(exp[i]);++judge;continue;
                    }
                    else
                    spush(exp[i]);
                }

                else
                    spush(exp[i]);
            }
            
            else if(exp[i]==')')
            {
                double num;
                for(;sstk[stop]!='(';spop())
                {
                    switch(sstk[stop])
                    {
                        case '+': num=nstk[ntop-1]+nstk[ntop];break;
                        case '-': num=nstk[ntop-1]-nstk[ntop];break;
                        case '*': num=nstk[ntop-1]*nstk[ntop];break;
                        case '/': num=nstk[ntop-1]/nstk[ntop];break;
                    }
                    npop(),npop(),npush(num);
                }
                spop();
            }
            
            if(judge)
            {
                double num;
                switch(sstk[stop])
                {
                    case '*': num=nstk[ntop-1]*nstk[ntop];break;
                    case '/': num=nstk[ntop-1]/nstk[ntop];break;
                }
                npop(),npop(),npush(num);
                spop();
                --judge;
            }

            
            if(!exp[i+1])
            {
                
                for(int k=0;k<=stop;++k)
                    if(k>0&&value(sstk[k])>value(sstk[k-1]))
                    {
                        double num=nstk[k];
                        switch(sstk[k])
                        {
                            case '*': num*=nstk[k+1];break;
                            case '/': num/=nstk[k+1];break;
                        }
                        npop2(k,num);
                        spop1(k);
                    }
                    double num=nstk[0];
                    for(int j=0,k=0;k<=stop;++j,++k)//j定位整数栈 k定位符号栈
                    {
                        
                        switch(sstk[k])
                        {
                            case '+': num+=nstk[j+1];break;
                            case '-': num-=nstk[j+1];break;
                            case '*': num*=nstk[j+1];break;
                            case '/': num/=nstk[j+1];break;
                        }
                    }
                    smake_empty();nmake_empty();
                    printf("%.2f\n",num);
                
            }
        }
    }
    return 0;
}