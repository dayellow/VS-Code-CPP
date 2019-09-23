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
    int data;
    Node *lchild,*rchild;
    int size;
};

Node* createNode(int data) 
{    
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;   
    temp->size; 
    temp->lchild = temp->rchild = NULL;
    return temp; 
}

void setNodeChild(Node* root, Node* lchild, Node* rchild) 
{    
    root->lchild = lchild;    
    root->rchild = rchild; 
}

//返回后序遍历的第K个（K从1开始计数）节点的指针 
int n=0;
void rankInPostorder(Node* &p,Node* t, int k)
{
    if(t)
    {
        rankInPostorder(p,t->lchild,k);
        rankInPostorder(p,t->rchild,k);
        ++n;
        if(n==k)
            p=t;
    }
}

//计算每个节点的size的值 
//需要的话你可以把该函数的返回值改为int类型
int generateEachNodeSize(Node* root)
{
    if(root)
    {
        root->size=1;
        if(root->lchild)
        {
            root->size+=generateEachNodeSize(root->lchild);
        }
        if(root->rchild)
        {
            root->size+=generateEachNodeSize(root->rchild);
        }
        if(!root->lchild&&!root->rchild)
        {
            return 1;
        }
        return root->size;
    }
}

int main() 
{
    Node* root = createNode(1); 
    Node* node2 = createNode(2); 
    Node* node3 = createNode(3);
    Node* node4 = createNode(4);
    Node* node5 = createNode(5);
    Node* node6 = createNode(6);
    Node* node7 = createNode(7);
    Node* node8 = createNode(8);

    setNodeChild(root, node2, node3);
    setNodeChild(node2, node4, node5);
    setNodeChild(node3, NULL, node7); 
    setNodeChild(node5, node6, NULL);
    setNodeChild(node4, NULL, node8);

    generateEachNodeSize(root);
    Node* p;
    for (int i = 1; i <= 8; i++,n=0)
    {
        rankInPostorder(p,root, i);
        printf("%d ", p->data); 
    }
    putchar('\n');
    system("pause");
    return 0;
}