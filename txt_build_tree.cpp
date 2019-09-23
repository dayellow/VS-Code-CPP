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

typedef struct Node
{
    char data;
    Node *lchild;
    Node *rchild;
};

Node* createNode(char data) //
{    
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;  
    temp->lchild=temp->rchild=NULL; 
    return temp; 
}

int i=0;
void createTree(Node *&B1,char order[])
{
    B1=createNode('#');//建立data为“#”的结点

    if(order[i])//order为先序序列
    {
        if(order[i]!='#')//如果该结点不为空
        {
            B1->data=order[i++];//输入该结点data
            createTree(B1->lchild,order);//检索左孩子
        }
        else//否则退出
        {
            ++i;
            return;
        }
        createTree(B1->rchild,order);//检索右孩子
        return;
    }
}

void preorder_storage1(Node *B,char order[])
{
    if(B)
    {
        cout<<B->data;order[i++]=B->data;
        preorder_storage1(B->lchild,order);
        preorder_storage1(B->rchild,order);
    }
}

void preorder_storage(Node *B,char order[])
{
    FILE *fp=fopen("preorder.txt","w");
    while(order[i++])
        order[i]='\0';
    i=0;
    preorder_storage1(B,order);
    fprintf(fp,"%s",order);
    fclose(fp);putchar('\n');
}

void txt_build_tree(Node *&B,char order[])
{
    FILE *fp=fopen("preorder.txt","r");
    fscanf(fp,"%s",order);
    fclose(fp);
    i=0;
    createTree(B,order);i=0;
}

void preorder(Node *B)
{
    if(B)
    {
        cout<<B->data;
        preorder(B->lchild);
        preorder(B->rchild);
    }
}
void txt_build_tree2(Node *&B,char order[])//非递归
{
    FILE *fp=fopen("preorder.txt","r");
    fscanf(fp,"%s",order);//从文件获取序列
    fclose(fp);
    B=createNode('#');//建立根结点
    Node* p;//借助p建立树
    Node *st[50];//建立储存结点指针的栈
    int top=-1;
    st[++top]=B;//根结点入栈
    for(;order[i];++i)
    {
        p=st[top];//p取栈顶结点
        st[top--]->data=order[i];//对栈顶结点赋值并弾栈
        if(order[i]!='#')//如果这一个结点不为空
        {
            p->rchild=createNode('#');//分别创立其左右孩子结点
            p->lchild=createNode('#');
            st[++top]=p->rchild;//先入栈其右孩子在入栈其左孩子
            st[++top]=p->lchild;
        }
    }
    i=0;
}

void inorder1(Node *B)
{
    Node *p;
    Node *st[50];//建立栈
    int top=-1;
    p=B;
    while(top!=-1||p)//栈不为空或结点不为空
    {
        while(p)//将子树的左子树以次入栈
        {
            st[++top]=p;
            p=p->lchild;
        }
        if(top!=-1)//栈不为空时弹栈，并处理右子树
        {
            p=st[top--];
            cout<<p->data;
            p=p->rchild;
        }
    }
    putchar('\n');
}


void postorder(Node *B)
{
    Node *p,*r;
    bool flag;
    Node *st[50];//栈
    int top=-1;
    p=B;
    if(B){
    do
    {
        while(p)//先将p的所有左孩子入栈
        {
            st[++top]=p;
            p=p->lchild;
        }
        r=NULL;//标记刚刚访问过的结点
        flag=true;//flag为真表示正在处理栈顶结点
        while(top!=-1&&flag)
        {
            p=st[top];//取栈顶结点
            if(p->rchild==r)//若p的右孩子为空或为刚刚访问过的节点
            {
                cout<<st[top--]->data;//访问p
                r=p;//r指向刚访问过的结点
            }
            else
            {
                p=p->rchild;//转向处理右子树
                flag=false;//表示当前不是处理栈顶结点
            }
        }
    }while(top!=-1);//栈不为空时循环
    putchar('\n');
    }
}

void destroytree(Node *&B)
{
    if(B)
    {
        destroytree(B->lchild);
        destroytree(B->rchild);
        free(B);
        B=NULL;
    }
}
int main() 
{   
    Node *B1=NULL,*B2=NULL,*B3=NULL;
    int choice;
    char order[50];//序列输入如：AB##C##
    for(;;)
    {
        cin>>choice;
        switch(choice)
        {
            case 1: cin>>order;createTree(B1,order);i=0;break;

            case 2: preorder_storage(B1,order);break;

            case 3: txt_build_tree(B2,order);preorder(B2);putchar('\n');break;

            case 4: txt_build_tree2(B3,order);break;

            case 5: inorder1(B3);break;

            case 6: postorder(B3);break;

            case 7: destroytree(B1),destroytree(B2),destroytree(B3);break;

            case 0: return 0;
        }
    }
}
