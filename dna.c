#include<stdio.h>//13:50
#include<string.h>
int main()
{
    int T;
    scanf("%d",&T);
    int m,n;
    while(T--)
    {
        scanf("%d%d",&m,&n);
        char dna[m][n];
        for(int i=0;i<m;++i)
            scanf("%s",dna[i]);
        char best;
        int answer=0;
        struct acgt{
            char word;
            int num;
        }acgt[4];
        int i,j;
        putchar('\n');
        for(j=0;j<n;++j)
        {
        	for(int k=0;k<4;++k) acgt[k].num=0;
            acgt[0].word='A';acgt[1].word='C';acgt[2].word='G';acgt[3].word='T';
        	for(i=0;i<m;++i)
                switch(dna[i][j])
                {
                    case 'A':++acgt[0].num;break;
                    case 'C':++acgt[1].num;break;
                    case 'G':++acgt[2].num;break;
                    case 'T':++acgt[3].num;break;
                }
            for(int k=0;k<3;++k)
            {
            	if(acgt[k].num>acgt[k+1].num)
                {
                    struct acgt acgt1;
                    acgt1=acgt[k];
                    acgt[k]=acgt[k+1];
                    acgt[k+1]=acgt1;
                }
                else if(acgt[k].num==acgt[k+1].num)
                {
                	if(acgt[k].word<acgt[k+1].word)
                	{
                		struct acgt acgt1;
                    	acgt1=acgt[k];
                    	acgt[k]=acgt[k+1];
                    	acgt[k+1]=acgt1;
					}
				}
			}
            best=acgt[3].word;
            printf("%c",best);
            answer=answer+acgt[0].num+acgt[1].num+acgt[2].num;
            if(j==n-1)
                printf("\n%d\n\n",answer);
		}
        
    }
    return 0;
}