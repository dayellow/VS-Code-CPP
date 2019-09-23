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

int inf=10000;
int topo[20];//拓扑排序结果数组

typedef struct ArcNode
{
    int adjvex;
    ArcNode *nextarc=NULL;
    int weight;
};

typedef struct VNode
{
    int count=0;
    int maxPath=0;//到此点的最长路径
	int v;//到该节点的最长路径中，此节点的邻接结点
    ArcNode *firstarc=NULL;
};

typedef struct AdjGraph
{
    VNode adjlist[20];
    int n,e;//顶点数，边数
};

bool toposort(AdjGraph g)
{
    int i=0,j,k,check=g.n;
    int top=-1,st[20];
    while(check)
    {
        for(j=0;j<g.n;++j)
            if(g.adjlist[j].count==0)
            {
                --check;
                topo[i++]=j;
                st[++top]=j;
                g.adjlist[j].count=-1;//设结点入度为-1
            }
        if(top==-1)
            return false;
        while(top>-1)
        {
            ArcNode *p;
            p=g.adjlist[st[top--]].firstarc;
            while(p)
            {
                --g.adjlist[p->adjvex].count;
                p=p->nextarc;
            }
        }
    }
    return true;
}

void getMaxPath(AdjGraph g)
{
    int i,j,k,v1,v2,max=0;
    ArcNode *q;
    for(j=0;j<g.n;++j)
    {
        v2=topo[j];
        if(!g.adjlist[v2].count)
            continue;
        for(k=0;k<j;++k)
        {
            v1=topo[k];
            q=g.adjlist[v1].firstarc;
            while(q&&q->adjvex!=v2)
                q=q->nextarc;
            if(q)
            {
                if(g.adjlist[v1].maxPath+q->weight>g.adjlist[v2].maxPath)
                {
                    g.adjlist[v2].maxPath=g.adjlist[v1].maxPath+q->weight;
					g.adjlist[v2].v=v1;
                }
                if(g.adjlist[v2].maxPath>max)
                    max=g.adjlist[v2].maxPath;
            }
        }
    }
    int s[20];
	int top=-1;
    s[++top]=v2;
	for(i=g.adjlist[v2].v;g.adjlist[i].count;)
	{
        s[++top]=i;
        i=g.adjlist[i].v;
    }
    cout<<endl<<"max length: "<<max<<endl;
    cout<<i;
	    while(top!=-1)
		{
			cout<<" -> "; 
			cout<<s[top--];
		}		
		cout<<endl;
}
int main() 
{    
    AdjGraph g;
    cin>>g.n>>g.e;
    memset(topo,-1,sizeof(topo));
    int start,end,weight;
    for(int i=0;i<g.e;++i)
    {
        cin>>start>>end>>weight;
        ArcNode *p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=end;
        p->weight=weight;
        p->nextarc=g.adjlist[start].firstarc;
        g.adjlist[start].firstarc=p;
        ++g.adjlist[p->adjvex].count;
    }
    AdjGraph g1=g;
    if(toposort(g1))
        getMaxPath(g);
    else
        cout<<"A loop was detected in this graph.\n";
    system("pause");  
    return 0; 
}
