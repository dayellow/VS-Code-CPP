#include<stdio.h>//21:50
#include<string.h>
int main()
{
    char p[5][5];
    char o[20];
    int i=0,j=0,k=0;
    int m,n;
    int t=0;
    for(;i<5;++i)
        gets(p[i]);
    for(i=0;i<5;++i)
        for(j=0;j<5;++j)
            if(p[i][j]==' ')
            {
                m=i,n=j;
                goto start;
            }
    start:
    gets(o);
    for(;o[k]!='0';++k)
    {
        switch(o[k])
        {
            case 'A':
            if(m)
            {
                p[m][n]=p[m-1][n];
                p[--m][n]=' ';
            }
            else
                printf("wrong"),t=1;break;
            case 'B':
            if(m<4)
            {
                p[m][n]=p[m+1][n];
                p[++m][n]=' ';
            }
            else
                printf("wrong"),t=1;break;
            case 'L':
            if(n)
            {
                p[m][n]=p[m][n-1];
                p[m][--n]=' ';
            }
            else
                printf("wrong"),t=1;break;
            case 'R':
            if(n<4)
            {
                p[m][n]=p[m][n+1];
                p[m][++n]=' ';
            }
            else
                printf("wrong"),t=1;break;
        }
        if(t) break;
    }
    if(o[k]=='0')
        for(i=0;i<5;++i)
        {
            for(j=0;j<5;++j)
                printf("%c",p[i][j]);
            putchar('\n');
        }
    return 0;
}