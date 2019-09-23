#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <ctime>

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
int contents[100];
int top=-1;
void make_empty(void)
{
    top=-1;
}
bool isempty(void)
{
    return top==-1;
}
bool is_full(void)
{
    return top==100;
}
void push(int i)
{
    if(!is_full())
        contents[++top]=i;
}
int pop(void)
{
    if(!isempty())
        return contents[top--];
}
int main()
{
    char example[100];
    cin>>example;
    int i;
    for(i=0;example[i]!='\0';i++)
    {
        if(example[i]=='{')
            push(1);
        else if(example[i]=='(')
            push(2);
        else if(example[i]=='[')
            push(3);
        else if(example[i]=='}')
        {
            if(contents[top]==1)
                pop();
            else break;
        }
        else if(example[i]==')')
        {
            if(contents[top]==2)
                pop();
            else break;
        }
        else if(example[i]==']')
        {
            if(contents[top]==3)
                pop();
            else break;
        }
    }
    if(top==-1) cout<<"yes\n";
    else cout<<"no\n";
    system("pause");
    return 0;
}