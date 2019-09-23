#include<stdio.h>//
#include<string.h>
int main()
{
    char exm[82];
    int n=1;//单周期字母数
    int i=0;//exm序号
    int len=0;
    scanf("%s",exm);
    for(;exm[len];++len);
    for(;n<=len/2&&i!=len-n+1;++n)
        for(i=0;i+n<len&&exm[i]==exm[i+n];++i);
    if(i!=len-n+1)
        printf("%s",exm);
    else
        for(i=0;i<n-1;++i)
            printf("%c",exm[i]);
    return 0;
}