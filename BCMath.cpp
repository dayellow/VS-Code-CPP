#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <ctime>
#include <stack>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

void add(int a[],int b[])
{
    int len,i;
    len=(a[0]>b[0]?a[0]:b[0]);//取两个字符串最大的长度
    for(i=1;i<=len;++i)//做按位加法，同时处理进位
    {
        a[i]+=b[i];//两数相加
        a[i+1]+=a[i]/2;//进行进位操作，进位值为a[i]/2，注意进位是高位的，因此我们要除以2
        a[i]%=2;//对相加后的数据进行模2操作，使其取值范围为0或1
    }
    if(a[len+1])    //检查最高位是否有进位
        ++len;
    for(i=len;i>0;--i)
        printf("%d",a[i]);
}

int str_compare(int a[],int b[]){
    if(a[0]>b[0])//a长度大，则a>b
        return 1;
    if(a[0]<b[0])//b长度大，则a<b
        return 0;
    for(int i = a[0];i>0;--i){//进行循环按位比较,由于数组存储数据时，高位在数组前面，因此从数组前面开始比较就行
        if(a[i]>b[i]) return true;
        if(a[i]<b[i]) return false;
    }
    return 2;//说明相等
}

void sub_child(int a[],int b[])//已假定a>b
{
    for(int i=1;i<=a[0];++i)
    {
        a[i]-=b[i];
        if(a[i]<0)//借位
        {
            --a[i+1];
            a[i]+=2;
        }
    }
    while((!a[a[0]])&&(a[0]>1))   --a[0];//计算结果的位数
    for(int i=a[0];i>0;--i)
        printf("%d",a[i]);
}

void sub(int a[],int b[])
{
    if(str_compare(a,b))
        sub_child(a,b);
    else//若a<b,其结果就为-(b-a)
    {
        putchar('-');
        sub_child(b,a);
    }
}

void mul(int a[],int b[])
{
    int c[200],len;
    int i,j;
    memset(c,0,sizeof(c));
    for(i=1;i<=a[0];++i)
        for(j=1;j<=b[0];++j)
        {
            c[i+j-1]+=a[i]*b[j];//按位相乘，注意乘后数的位置 
            c[i+j]+=c[i+j-1]/2;
            c[i+j-1]%=2;
        }
    len=a[0]+b[0];
    if(!c[len])//由于乘法结果最高位为a[0]+b[0]或a[0]+b[0]-1位
        --len;//判断最高位
    for(i=len;i>0;--i)
        printf("%d",c[i]);
}

void subduction(int a[],int b[])//除法中计算a=a-b
{
    int flag;
    int i;
    flag=str_compare(a,b);
    if(flag==2)//相等
    {
        a[0]=0;
        return;
    }
    if(flag)//a>b,算法与sub_child类似
    {
        for(i=1;i<a[0];++i)
        {
            if(a[i]<b[i])
            {
                --a[i+1];
                a[i]+=2;
            }
            a[i]-=b[i];
        }
        while(a[0]>0&&(!a[a[0]]))
            --a[0];
        return;
    }
}

void div(int a[],int b[])
{
    int temp[100];
    int c[100];
    memset(c,0,sizeof(c));
    c[0]=a[0]-b[0]+1;
    int i,j;
    for(i=c[0];i>0;--i)
    {
        memset(temp,0,sizeof(temp));

        for(j=1;j<=b[0];++j)//从i开始的地方，复制数组b到数组temp
            temp[j+i-1]=b[j];
        temp[0]=b[0]+i-1;

        while(str_compare(a,temp)>0)//是否够减？除数的当前位+1，a-temp：退出；
        {
            ++c[i];
            subduction(a,temp);
        }
    }
    if(!c[c[0]])//除法运算中，当被除数大于等于除数时，其结果位数为a[0]-b[0] or a[0]-b[0]+1
        --c[0];
    cout<<"quotient:";
    for(i=c[0];i>0;--i)
        cout<<c[i];
    putchar(' ');
    cout<<"remainder:";
    if(!a[0])//余数若为0
        cout<<0;
    else
    {
        for(i=a[0];i>0;--i)
            cout<<a[i];
    }
}
int main() //base=2
{   
    int choice=1;
    while(choice)
    {
        cin>>choice;
        if(choice>0&&choice<5)
        {
            string str1,str2;
            int a[100],b[100];//数组的大小决定了计算的高精度最大位数
            int i;
            memset(a,0,sizeof(a));
            memset(b,0,sizeof(b));
            cin>>str1>>str2;//输入两个字符串
            a[0]=str1.length();//取得字符串的长度
            b[0]=str2.length();
            for(i=1;i<=a[0];++i)//把字符串转换为整数，存放在数组中
                a[i]=str1[a[0]-i]-'0';
            for(i=1;i<=b[0];++i)
                b[i]=str2[b[0]-i]-'0';
        
            switch(choice)
            {
                case 1:add(a,b);break;//加
                case 2:sub(a,b);break;//减
                case 3:mul(a,b);break;//乘
                case 4:div(a,b);break;//除
            }
            putchar('\n');
        }
        else  return 0;   
    }
}
