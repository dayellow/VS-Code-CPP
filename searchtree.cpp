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
    int key;
    Node* parent;
    Node* lchild,*rchild;
};

Node* createNode(int key) 
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->key = key;
    temp->lchild = temp->rchild = temp->parent = NULL;    
    return temp; 
}

//在树中插入一个节点 
Node* insert(Node* &root, int key) 
{    
    if(!root)
    {
        root=createNode(key);
        return root;
    }
    else
    {
        Node* p=createNode(key);
        Node* head=root;
        for(;;) 
        {
            if(key<head->key&&head->lchild)   //若关键字小于结点的数据；
                head=head->lchild;//在左子树上查找； 
            else if(key>=head->key&&head->rchild)   //若关键字大于结点的数据；
                head=head->rchild;  //在右子树上查找；
            else 
                break;
        }
        //判断添加到左子树还是右子树；
        if(key<head->key)   //小于父结点；
        {
            head->lchild=p;
            p->parent=head;
        }    //添加到左子树；
        else    //大于父结点；
        {
            head->rchild=p;
            p->parent=head;
        }     //添加到右子树；
    }
}

//返回树中最小值节点的位置 
Node* minimum(Node* root)
{
    while(root->lchild)
        root=root->lchild;
    return root;
}

//返回该树中序遍历序列起始节点的位置 
Node* begin(Node* root) 
{    
    return minimum(root); 
}

//返回中序遍历序列中该节点的下一个节点的位置 
//如果该节点已经是序列的最后一个节点，则返回NULL 
Node* next(Node* current)
{
    if(current->rchild)
        return minimum(current->rchild);
    else if(current->parent->lchild==current)
        return current->parent;
    else
    {
        while(current->parent->parent)
        {
            current=current->parent;
            if(current==current->parent->lchild)
                    return current->parent;
        }
        return NULL;
    }
}

Node* end(Node* root) 
{    
    return NULL; 
}

int main() 
{    
    Node* root = NULL;  //一棵空树    
    int N;    
    scanf("%d", &N);    
    for (int i = 0; i < N; i++) 
    {        
        int x;        
        scanf("%d", &x);        
        insert(root, x);    
    }
    //进行一次中序遍历    
    for (Node* p = begin(root); p != end(root); p = next(p)) 
    {        
        printf("%d ", p->key);    
    }    
    printf("\n");  
    system("pause");  
    return 0; 
}