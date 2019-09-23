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

std::map<string,int> site;
string site1[20];

int inf=100000;

typedef struct ArcNode
{
    int adjvex;
    string sr;
    int srl;
    ArcNode *nextarc;
};

typedef struct VNode
{
    ArcNode *firstarc;
};

typedef struct AdjGraph
{
    VNode adjlist[20];
};
AdjGraph g1;

typedef struct Matgraph
{
    int n;
    int edges[20][20];
};
Matgraph g;

void write_distance()
{
	fstream f("road.txt", ios::out);
	string v1,v2;
    int ds=1;
    for(;;)
    {
        cin>>v1>>v2>>ds;
        if(ds)
            f<<v1<<"\t"<<v2<<"\t"<<ds<<"\n";
        else break;
    }
	f.close();
}

void read_distance()
{
    fstream f("road.txt",ios::in);
    g.n=0;
    for(int i=0;i<20;++i)
        for(int j=0;j<20;++j)
            g.edges[i][j]=inf;
    string v1,v2;
    int ds;
    int i=0;
    while(!f.eof())
    {
        f>>v1>>v2>>ds;
        if(!site[v1])
        {
            site[v1]=++i;
            site1[i]=v1;
        }
        if(!site[v2])
        {
            site[v2]=++i;
            site1[i]=v2;
        }
        g.edges[site[v1]][site[v2]]=g.edges[site[v2]][site[v1]]=ds;
    }
    g.n=i;
    f.close();
}

void Dijkstra(string v1,string v2)
{
    if(site[v1]&&site[v2])
    {
        int start=site[v1],end=site[v2];
        int dist[20],path[20];
        int s[20];
        int mindis,i,j,u;
        for(i=1;i<=g.n;++i)
        {
            dist[i]=g.edges[start][i];
            s[i]=0;
            if(g.edges[start][i]<inf)
                path[i]=start;
            else
                path[i]=-1;
        }
        s[start]=1;path[start]=start;
        for(i=1;i<=g.n-1;++i)
        {
            mindis=inf;
            for(j=1;j<=g.n;++j)
                if(!s[j]&&dist[j]<inf&&dist[j]<mindis)
                {
                    u=j;
                    mindis=dist[j];
                }
            s[u]=1;
            for(j=1;j<=g.n;++j)
                if(!s[j])
                    if(g.edges[u][j]<inf&&dist[u]+g.edges[u][j]<dist[j])
                    {
                        dist[j]=dist[u]+g.edges[u][j];
                        path[j]=u;
                    }
        }
        int t;
        int top=-1;
        string stack[20];
        for(i=end;i!=start&&path[i]!=-1;)
        {
            stack[++top]=site1[i];
            t=path[i];
            i=t;
        }
        if(path[i]==-1)
            cout<<"can't reach";
        else
        {
            cout<<"min distance: "<<dist[end]<<"\n";
            cout<<site1[start];
            while(top>-1)
                cout<<"->"<<stack[top--];
        }
        putchar('\n');
    }
}

void Floyd()
{
    int A[20][20],path[20][20];
    int i,j,k;
    for(i=1;i<=g.n;++i)
        for(j=1;j<=g.n;++j)
        {
            A[i][j]=g.edges[i][j];
            if(i!=j&&g.edges[i][j])
                path[i][j]=i;
            else
                path[i][j]=-1;
        }
    for(k=1;k<=g.n;++k)
        for(i=1;i<=g.n;++i)
            for(j=1;j<g.n;++j)
                if(A[i][j]>A[i][k]+A[k][j])
                {
                    A[i][j]=A[i][k]+A[k][j];
                    path[i][j]=path[k][j];
                }
    fstream f("AllPath.txt", ios::out);
	int s;
    int apath[20],d;
    for(i=1;i<=g.n;++i)
        for(j=1;j<=g.n;++j)
        {
            if(A[i][j]!=inf&&i!=j)
            {
                f<<site1[i]<<"  "<<site1[j]<<"  ";
                k=path[i][j];
                d=0;apath[d]=j;
                while(k!=-1&&k!=i)
                {
                    ++d;apath[d]=k;
                    k=path[i][k];
                }
                f<<site1[i];
                for(s=d;s>=0;--s)
                    f<<"->"<<site1[apath[s]];
                f<<"    "<<A[i][j]<<"\n";
            }
            else if(i!=j)
                f<<site1[i]<<"  "<<site1[j]<<"  no\n";
        }
	f.close();
}

void read_path()
{
    fstream f("road.txt",ios::in);
    
    while(!f.eof())
    {
        
    }
    f.close();
}
int main() 
{   
    int choice;
    string v1,v2;
    for(;;)
    {
        cin>>choice;
        switch(choice)
        {
            case 1: write_distance();break;
            case 2: read_distance();
                    cin>>v1>>v2;
                    Dijkstra(v1,v2);break;
            case 3: read_distance();
                    Floyd();break;
            case 4: break;
            case 0: return 0;
        }
    }
}
