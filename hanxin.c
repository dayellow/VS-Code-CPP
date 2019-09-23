#include<stdio.h>
int num[3];
int sum[20];
int i;
int n=0;
int main ()
{
    FILE *fp=fopen("hanxin.txt","r");
    while(!feof(fp))
    {
        for(i=0;i<3;++i)
        {
            fscanf(fp,"%d ",&num[i]);
        }
        ++n;
        int ten=1,t=0;
        for(i=0;ten<=10;++ten)
        {
            t=ten*10+num[1];
            if(t%3==num[0]&&t%7==num[2]&&t<=100)
            {
                sum[n]=t;
                break;
            }
        }
        if(sum[n]==0)
            for(ten=1;ten<=10;++ten)
            {
                t=ten*10+num[1]+5;
                if(t%3==num[0]&&t%7==num[2]&&t<=100)
                {
                    sum[n]=t;
                    break;
                }
            }
    }
        for(int a=1;a<=n;++a)
        {
            if(sum[a])
                printf("Case %d: %d\n",a,sum[a]);
            else
                printf("Case %d: No answer\n",a);
        }
    return 0;
}