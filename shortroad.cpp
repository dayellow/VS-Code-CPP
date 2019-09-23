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

int N;//顶点数
int L;//边数
int inf=100000;
typedef struct Matgraph
{
    int n;
    int edges[20][20];
};

void Dijkstra(Matgraph g,int start,int end)
{
    int dist[20],path[20];
    int s[20];
    int mindis,i,j,u;
    for(i=0;i<g.n;++i)
    {
        dist[i]=g.edges[start][i];
        s[i]=0;
        if(g.edges[start][i]<inf)
            path[i]=start;
        else
            path[i]=-1;
    }
    s[start]=1;path[start]=start;
    for(i=0;i<g.n-1;++i)
    {
        mindis=inf;
        for(j=0;j<g.n;++j)
            if(!s[j]&&dist[j]<inf&&dist[j]<mindis)
            {
                u=j;
                mindis=dist[j];
            }
        s[u]=1;
        for(j=0;j<g.n;++j)
            if(!s[j])
                if(g.edges[u][j]<inf&&dist[u]+g.edges[u][j]<dist[j])
                {
                    dist[j]=dist[u]+g.edges[u][j];
                    path[j]=u;
                }
    }
    int t;
    int top=-1;
    int stack[20];
    for(i=end;i!=start&&path[i]!=-1;)
    {
        stack[++top]=i;
        t=path[i];
        i=t;
    }
    if(path[i]==-1)
        cout<<"can't reach";
    else
    {
        cout<<"min distance: "<<dist[end]<<"\n";
        cout<<start;
        while(top>-1)
            cout<<"->"<<stack[top--];
    }
    putchar('\n');
}

int main() 
{    
    int start,end;
    cin>>N>>L>>start>>end;//起点终点
    Matgraph g;
    g.n=N;
    for(int i=0;i<20;++i)
        for(int j=0;j<20;++j)
            g.edges[i][j]=inf;
    int s,e,length;//路径起点，终点，长度
    for(int i=0;i<L;++i)
    {
        cin>>s>>e>>length;
        g.edges[s][e]=length;
    }
    Dijkstra(g,start,end);
    system("pause");  
    return 0; 
}
