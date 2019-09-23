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
};

Node* createTree(int preOrder[], int inOrder[], int N)
{
    Node* b;
    int *p;
    int k;
    if(N<=0) return NULL;
    b=(Node*)malloc(sizeof(Node));
    b->data=preOrder[0];
    for(p=inOrder;p<inOrder+N;++p)
        if(*p==preOrder[0])
            break;
    k=p-inOrder;
    b->lchild=createTree(preOrder+1,inOrder,k);
    b->rchild=createTree(preOrder+k+1,p+1,N-k-1);
    return b;
}

int getTreeHeight(Node* root)
{
    int lchildh,rchildh;
    if(!root) return 0;
    else
    {
        lchildh=getTreeHeight(root->lchild);
        rchildh=getTreeHeight(root->rchild);
        return (lchildh>rchildh)? (lchildh+1):(rchildh+1);
    }
}

int getTreeWidth(Node* root)
{
    int rear=0,front=0;
    int Last, temp_width, max_width;
    Node* queue[50];
    temp_width = max_width = 0;
    Last = 0;//标注队尾位置
 
    if ( root == NULL) return 0;
    else 
    {
        queue[++rear]=root;//将二叉树的树根入队列
        while (rear!=front) 
        {
            ++front; //由队头出队列一个元素
            ++temp_width;
            if (queue[front]->lchild)  queue[++rear]=queue[front]->lchild;//将出队列的这个元素的左孩子节点入队
            if (queue[front]->rchild)  queue[++rear]=queue[front]->rchild;//将出队列的这个元素的右孩子节点入队
            if ( front >=Last ) //判断上一层是否遍历完
            {
                Last = rear;//更新标注变量的值
                if ( temp_width > max_width ) max_width = temp_width;
                temp_width = 0;
            } /* end-if */
        } /* end-while */
        return  max_width;
    }
}

int countLeafNode(Node* root)
{
    int sum=0;
    if(root) ++sum;
    if(root->lchild) sum+=countLeafNode(root->lchild);
    if(root->rchild) sum+=countLeafNode(root->rchild);
    return sum;
}

Node* CloneTree(Node* root)
{
    if(root)
    {
        Node *croot=(Node*)malloc(sizeof(Node));
        croot->data=root->data;
        croot->lchild=CloneTree(root->lchild);
        croot->rchild=CloneTree(root->rchild);
        return croot;
    }
}

void mirrorTree(Node* croot)
{
    if(croot)
    {
        if(croot->lchild||croot->rchild)
        {
            Node *temp=(Node*)malloc(sizeof(Node));
            temp=croot->lchild;
            croot->lchild=croot->rchild;
            croot->rchild=temp;
        }
        mirrorTree(croot->lchild);
        mirrorTree(croot->rchild); 
    }
    else
        return;
}

void lavelOrderTraversal(Node* root)
{
    if(root)
    {
        int rear=0,front=0;
        Node *queue[50];
        queue[++rear]=root;
        while(rear!=front)
        {
            printf("%d ",queue[++front]->data);
            if(queue[front]->lchild) queue[++rear]=queue[front]->lchild;
            if(queue[front]->rchild) queue[++rear]=queue[front]->rchild;
        }
    }
    putchar('\n');
}

void destoryTree(Node* root)
{
    if(root)
    {
        destoryTree(root->lchild);
        destoryTree(root->rchild);
        free(root);
    }
}

int main()
{
    system("chcp 65001");
    int N;
    scanf("%d", &N);
    int* preOrder = (int*)malloc(N * sizeof(int));
    int* inOrder = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
    scanf("%d", &preOrder[i]);
    }
    for (int i = 0; i < N; i++) {
    scanf("%d", &inOrder[i]);
    }
    Node* root = createTree(preOrder, inOrder, N);
    int depth=getTreeHeight(root);
    printf("该树的高度是: %d\n", depth);
    printf("该树的宽度是: %d\n", getTreeWidth(root));
    printf("该树的叶节点个数是: %d\n", countLeafNode(root));
    Node* newTreeRoot = CloneTree(root);
    mirrorTree(newTreeRoot);
    printf("该树的镜像树的层次遍历序列为:\n");
    lavelOrderTraversal(newTreeRoot);
    destoryTree(root);
    destoryTree(newTreeRoot);
    system("pause");
    return 0;
}