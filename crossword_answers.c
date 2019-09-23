#include<stdio.h>//13:50
#include<string.h>
int main()
{
    int r,c;
    int order=1;
    int n=0;
    for(;scanf("%d",&r)==1&&r!=0;++order,n=0)
    {
        scanf("%d",&c);
        char p[r][c];
        int  num[r][c];
        memset(num,0,sizeof(num));
        for(int i=0;i<r;++i)
            scanf("%s",p[i]); 
        for(int i=0;i<r;++i)
            for(int j=0;j<c;++j)
                if(p[i][j]!='*'&&!(i>0&&j>0&&p[i-1][j]!='*'&&p[i][j-1]!='*'))
                    num[i][j]=++n;
        printf("\npuzzle #%d:\nAcross\n",order);
        for(int i=0;i<r;++i)
            for(int j=0;j<c;++j)
                if(num[i][j])
                {
                    printf("  %d.",num[i][j]);
                    for(;p[i][j]!='*'&&j<c;++j)
                        printf("%c",p[i][j]);
                    putchar('\n');
                }
        printf("Down\n");
        for(int i=0;i<r;++i)
            for(int j=0;j<c;++j)
                if(num[i][j]&&(i==0||p[i-1][j]=='*'))
                {
                    printf("  %d.",num[i][j]);
                    int t=i;
                    for(;p[t][j]!='*'&&t<r;++t)
                        printf("%c",p[t][j]);
                    putchar('\n');
                }
        putchar('\n');
    }
    return 0;
}