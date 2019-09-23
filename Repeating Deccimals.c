#include <stdio.h>
#include <string.h>
int a[10000];
int b[10000];
int main(void)
{
    int m, n, i, j;
    while(scanf("%d%d", &m, &n) != EOF){
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        a[0] = m / n;
        printf("%d/%d = %d.", m, n, a[0]);
        m = m % n;
        int count = 1;
        while(!b[m] && m){
            b[m]= count;
            a[count++] = m * 10 / n;
            m = m * 10 % n;
        }
        if(m == 0){
            for(i = 1; i < count; i++)
            printf("%d", a[i]);
            printf("(0)\n");
        }
        else{
            //输出循环节之前的小数
            for(i = 1; i < b[m]; i++)
                printf("%d", a[i]);
            //输出循环节
            printf("(");
            for(; i < count && i <= 50; i++)
                printf("%d", a[i]);
            if(count > 50)
                printf("...");
            printf(")\n");
        }
        printf("   %d",!m ? 1: count - b[m]);
        printf(" = number of digits in repeating cycle\n\n");
    }
    return 0; 
}