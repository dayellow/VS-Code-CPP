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
    char sr[100];//最短路径信息
    int srl;//short road length
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

void read_distance()//从文件读取距离信息并储存到相应二维数组中
{
    fstream f("road.txt",ios::in);
    g.n=0;
    for(int i=0;i<20;++i)//距离初始化
        for(int j=0;j<20;++j)
            g.edges[i][j]=inf;
    string v1,v2;
    int ds;//distance距离
    int i=0;//将地点名称离散化，映射成整型
    while(!f.eof())
    {
        f>>v1>>v2>>ds;
        if(!site[v1])//如果该地点名称未被映射成整型
        {
            site[v1]=++i;
            site1[i]=v1;
        }
        if(!site[v2])//同上
        {
            site[v2]=++i;
            site1[i]=v2;
        }
        g.edges[site[v1]][site[v2]]=g.edges[site[v2]][site[v1]]=ds;//距离赋值
    }
    g.n=i;//结点个数
    f.close();
}

void Dijkstra(string v1,string v2)//输入两个地点名称输出最短路径
{
    if(site[v1]&&site[v2])//如果两个地点都存在
    {
        int start=site[v1],end=site[v2];
        int dist[20],path[20];
        int s[20];//已求出最短路径的顶点集合
        int mindis,i,j,u;
        for(i=1;i<=g.n;++i)//距离初始化
        {
            dist[i]=g.edges[start][i];
            s[i]=0;//s[]置空
            if(g.edges[start][i]<inf)//路径初始化
                path[i]=start;//start到i有边时
            else
                path[i]=-1;
        }
        s[start]=1;path[start]=start;//原点编号start放入s中
        for(i=1;i<=g.n-1;++i)//循环到所有点的最短距离都求出
        {
            mindis=inf;//最短路径初始化
            for(j=1;j<=g.n;++j)//选取不在s的start能到达的点的最短路径
                if(!s[j]&&dist[j]<inf&&dist[j]<mindis)
                {
                    u=j;
                    mindis=dist[j];
                }
            s[u]=1;//u放入s中
            for(j=1;j<=g.n;++j)//求增加u后，start到剩余定点的最短路径
                if(!s[j])
                    if(g.edges[u][j]<inf&&dist[u]+g.edges[u][j]<dist[j])
                    {
                        dist[j]=dist[u]+g.edges[u][j];
                        path[j]=u;
                    }
        }
        int t;
        int top=-1;
        string stack[20];//创立栈储存路径结点
        i=end;
        while(i!=start&&path[i]!=-1)//从目的地结点依次入栈
        {
                stack[++top]=site1[i];
                t=path[i];
                i=t;
        }
        if(path[i]==-1)//若不能到达
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
    int A[20][20],path[20][20];//A为图的邻接矩阵，path保存最短路径
    int i,j,k;
    for(i=1;i<=g.n;++i)//A的初始化
        for(j=1;j<=g.n;++j)
        {
            A[i][j]=g.edges[i][j];
            if(i!=j&&g.edges[i][j])
                path[i][j]=i;//有路径置i
            else
                path[i][j]=-1;
        }
    for(k=1;k<=g.n;++k)//分别考虑增加不同结点后生成子图的路径变化
        for(i=1;i<=g.n;++i)
            for(j=1;j<g.n;++j)
                if(A[i][j]>A[i][k]+A[k][j])
                {
                    A[i][j]=A[i][k]+A[k][j];//修改最短路径长度
                    path[i][j]=path[k][j];//修改最短路径
                }
    fstream f("AllPath.txt", ios::out);//将最短路径信息存入文件
    //格式： 起点   终点    最短路径    最短路径长度
	int s;
    int apath[20],d;//存放路径中间顶点（用法类似于栈）和顶点个数
    for(i=1;i<=g.n;++i)
        for(j=1;j<=g.n;++j)
        {
            if(A[i][j]!=inf&&i!=j)//若i和j间有路径
            {
                f<<site1[i]<<"  "<<site1[j]<<"  ";
                k=path[i][j];
                d=0;apath[d]=j;//压入终点
                while(k!=-1&&k!=i)
                {
                    ++d;apath[d]=k;//其实是压栈
                    k=path[i][k];
                }
                f<<site1[i];//从这开始输出最短路径及长度
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
    fstream f("AllPath.txt",ios::in);
    for(int i=1;i<g.n;++i)
        g1.adjlist[i].firstarc=NULL;
    string i,j;
    char k[100];
    ArcNode *p;
    while(!f.eof())
    {
        f>>i>>j>>k;//分别从文件中读取起点，终点，最短路径（如果没有则k为“no”）
        if(strcmp(k,"no")!=0)//若存在路径
        {
            p=(ArcNode*)malloc(sizeof(ArcNode));
            p->adjvex=site[j];//终点名称赋值
            strcpy(p->sr,k);//到该终点的最短路径赋值
            f>>p->srl;//路径长度
            p->nextarc=g1.adjlist[site[i]].firstarc;//类似于头插法
            g1.adjlist[site[i]].firstarc=p;
        }
    }
    f.close();
}

void road_search()
{
    int u;
    string i,j;
    ArcNode *p;
    string r;
    do
    {
        cin>>i>>j;//起点，终点
        p=g1.adjlist[site[i]].firstarc;
        u=site[j];
        while(p&&p->adjvex!=u)//这个两个条件的位置不可颠倒
                p=p->nextarc;//循环结束后p不为空直接输出该结点信息
                //否则p为空，则不存在该路径
        if(p)
        {
            r=p->sr;
            cout<<"path: "<<r<<"\nlength: "<<p->srl<<endl;
        }
        else if(i=="0"&&j=="0")
            break;
        else
            cout<<"no\n";
    } while (i!="0"&&j!="0");
}
int main() //由于不知何原因重复读取没有变化的文件
{          //总是会出现错误，所以用的这种结构
            //（使用f.close()函数了）好在问题解决了
    int choice;
    string v1,v2;
    read_distance();
    read_path();
    for(;;)
    {
        cin>>choice;
        switch(choice)
        {
            case 1: write_distance();
                    read_distance();
                    read_path();break;
            case 2: cin>>v1>>v2;
                    Dijkstra(v1,v2);break;
            case 3: Floyd();break;
            case 4: road_search();break;
            case 0: return 0;
        }
    }
}
