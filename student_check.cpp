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

typedef struct student{
    char sno[20];//学号
    char sname[20];//姓名
    char sex[5];//性别
    char major[20];//专业
};

typedef struct course{
    char cno[20];
    char cname[20];
    int classHours;
};

typedef struct grade{
    char sno[20];
    char cno[20];
    int score;
};

typedef struct allgrade{
    char sno[20];
    char sname[20];
    char major[20];
    char cname[20];
    int score;
    char cno[20];
};

typedef struct allnode{
    allgrade data;
    allnode *next;
};

typedef struct stunode{
    student data;
    stunode *next;
};

typedef struct counode{
    course data;
    counode *next;
};

typedef struct granode{
    grade data;
    granode *next;
};

void delstu(stunode *&shead)
{
    stunode *p=shead;
    while(shead)
    {
        shead=shead->next;
        free(p);
        p=shead;
    }
}

void delcou(counode *&chead)
{
    counode *p=chead;
    while(chead)
    {
        chead=chead->next;
        free(p);
        p=chead;
    }
}

void delgra(granode *&ghead)
{
    granode *p=ghead;
    while(ghead)
    {
        ghead=ghead->next;
        free(p);
        p=ghead;
    }
}

void delall(allnode *&gnhead)
{
    allnode *p=gnhead;
    while(gnhead)
    {
        gnhead=gnhead->next;
        free(p);
        p=gnhead;
    }
}

void stuinit(int sum,stunode *&shead)//输入n个学生
{
    stunode *p=NULL;
    FILE *fp=fopen("student.txt","a");
    for(int i=0;i<sum;++i)
    {
        p=(stunode*)malloc(sizeof(stunode));
        cin>>p->data.sno>>p->data.sname>>p->data.sex>>p->data.major;
        p->next=shead;
        shead=p;
        fprintf(fp,"%s\t%s\t%s\t%s\n",p->data.sno,p->data.sname,p->data.sex,p->data.major);
    }
    fclose(fp);
}

void couinit(counode *&chead)//输入课程
{
    delcou(chead);
    counode *p=NULL;
    FILE *fp=fopen("course.txt","w");
    for(int i=0;i<3;++i)
    {
        p=(counode*)malloc(sizeof(counode));
        cin>>p->data.cno>>p->data.cname>>p->data.classHours;
        p->next=chead;
        chead=p;
        fprintf(fp,"%s\t%s\t%d\n",p->data.cno,p->data.cname,p->data.classHours);
    }
    fclose(fp);
}

void grainit(int sum,granode *&ghead)//输入成绩
{
    granode *p=NULL;
    FILE *fp=fopen("grade.txt","a");
    for(int i=0;i<3*sum;++i)
    {
        p=(granode*)malloc(sizeof(granode));
        cin>>p->data.sno>>p->data.cno>>p->data.score;
        p->next=ghead;
        ghead=p;
        fprintf(fp,"%s\t%s\t%d\n",p->data.sno,p->data.cno,p->data.score);
    }
    fclose(fp);
}

bool cmp1(student a,student b)
{
    if(strlen(a.sno)<strlen(b.sno))
        return true;
    else if(strlen(a.sno)==strlen(b.sno)&&strcmp(a.sno,b.sno)<0)
        return true;
    return false;
}

void stusort(stunode *&shead)
{
    delstu(shead);
    stunode* p=(stunode*)malloc(sizeof(stunode));
    p->next=NULL;
    FILE* fp=fopen("student.txt","r");
    while(!feof(fp))
    {
        fscanf(fp,"%s%s%s%s",p->data.sno,p->data.sname,p->data.sex,p->data.major);
        if(p->data.sno[0]!='f')
        {
            p->next=shead;
            shead=p;
            p=(stunode*)malloc(sizeof(stunode));
            p->data.sno[0]='f';
        }
        else break;
    }
    p=shead;
    int len;
    for(len=0;p;++len)
        p=p->next;
    p=shead;
    student stu[len];
    for(int i=0;i<len;++i)
    {
        stu[i]=p->data;
        p=p->next;
    }
    p=shead;
    sort(stu,stu+len,cmp1);
    for(int i=0;i<len;++i)
    {
        cout<<stu[i].sno<<"\t"<<stu[i].sname<<"\t"<<stu[i].sex<<"\t"<<stu[i].major<<"\n";
        p->data=stu[i];
        p=p->next;
    }
    fclose(fp);
}

bool cmp2(course a,course b)
{
    if(strlen(a.cno)<strlen(b.cno))
        return true;
    else if(strlen(a.cno)==strlen(b.cno)&&strcmp(a.cno,b.cno)<0)
        return true;
    return false;
}

void cousort(counode *&chead)
{
    delcou(chead);
    counode* p=(counode*)malloc(sizeof(counode));
    p->next=NULL;
    FILE* fp=fopen("course.txt","r");
    while(!feof(fp))
    {
        fscanf(fp,"%s%s%d",p->data.cno,p->data.cname,&p->data.classHours);
        if(p->data.cno[0]!='f')
        {
            p->next=chead;
            chead=p;
            p=(counode*)malloc(sizeof(counode));
            p->data.cno[0]='f';
        }
        else break;
    }
    p=chead;
    int len;
    for(len=0;p;++len)
        p=p->next;
    p=chead;
    course cou[len];
    for(int i=0;i<len;++i)
    {
        cou[i]=p->data;
        p=p->next;
    }
    p=chead;
    sort(cou,cou+len,cmp2);
    for(int i=0;i<len;++i)
    {
        cout<<cou[i].cno<<"\t"<<cou[i].cname<<"\t"<<cou[i].classHours<<"\n";
        p->data=cou[i];
        p=p->next;
    }
    fclose(fp);
}

bool cmp3(grade a,grade b)
{
    if(strlen(a.sno)<strlen(b.sno))
        return true;
    if(strlen(a.sno)==strlen(b.sno))
    {
        if(strcmp(a.sno,b.sno)<0)
            return true;
        else if(strcmp(a.sno,b.sno)==0)
        {
            if(strlen(a.cno)<strlen(b.cno))
                return true;
            else if(strlen(a.cno)==strlen(b.cno)&&strcmp(a.cno,b.cno)<0)
                return true;
        }
    }
    return false;
}

void grasort(granode *&ghead)
{
    delgra(ghead);
    granode* p=(granode*)malloc(sizeof(granode));
    p->next=NULL;
    FILE* fp=fopen("grade.txt","r");
    while(!feof(fp))
    {
        fscanf(fp,"%s%s%d",p->data.sno,p->data.cno,&p->data.score);
        if(p->data.sno[0]!='f')
        {
            p->next=ghead;
            ghead=p;
            p=(granode*)malloc(sizeof(granode));
            p->data.sno[0]='f';
        }
        else break;
    }
    p=ghead;
    int len;
    for(len=0;p;++len)
        p=p->next;
    p=ghead;
    grade gra[len];
    for(int i=0;i<len;++i)
    {
        gra[i]=p->data;
        p=p->next;
    }
    sort(gra,gra+len,cmp3);
    p=ghead;
    for(int i=0;i<len;++i)
    {
        cout<<gra[i].sno<<"\t"<<gra[i].cno<<"\t"<<gra[i].score<<"\n";
        p->data=gra[i];
        p=p->next;
    }
    fclose(fp);
}

bool cmp4(grade a,grade b)
{
    if(strlen(a.cno)<strlen(b.cno))
        return true;
    if(strlen(a.cno)==strlen(b.cno))
    {
        if(strcmp(a.cno,b.cno)<0)
            return true;
        else if(!strcmp(a.cno,b.cno))
            if(a.score>b.score)
                return true;
    }
    return false;
}

bool cmp5(grade a,grade b)
{
    if(strcmp(a.cno,b.cno)==0)
        if(a.score<b.score)
            return true;
    return false;
}

void cougrasort(stunode *&shead,counode *&chead,granode *&ghead,allnode* &g1head,allnode* &g2head,allnode* &g3head)
{
    delstu(shead);
    delcou(chead);
    delgra(ghead);
    delall(g1head);
    delall(g2head);
    delall(g3head);
    granode *p=(granode*)malloc(sizeof(granode));
    p->next=NULL;
    FILE *fp=fopen("grade.txt","r");
    while(!feof(fp))
    {
        fscanf(fp,"%s%s%d",p->data.sno,p->data.cno,&p->data.score);
        if(p->data.sno[0]!='f')
        {
            p->next=ghead;
            ghead=p;
            p=(granode*)malloc(sizeof(granode));
            p->data.sno[0]='f';
        }
        else break;
    }
    p=ghead;
    int len;
    for(len=0;p;++len)
        p=p->next;
    p=ghead;
    grade gra[len];
    for(int i=0;i<len;++i)
    {
        gra[i]=p->data;
        p=p->next;
    }
    sort(gra,gra+len,cmp4);
    
    fclose(fp);


    fp=fopen("grade.txt","w");
    for(int i=0;i<len;++i)
    {
        fprintf(fp,"%s\t%s\t%d\n",gra[i].sno,gra[i].cno,gra[i].score);
    }
    stunode *p1=(stunode*)malloc(sizeof(stunode));
    fclose(fp);
    sort(gra,gra+len,cmp5);
    fp=fopen("student.txt","r");
    while(!feof(fp))
    {
        fscanf(fp,"%s%s%s%s",p1->data.sno,p1->data.sname,p1->data.sex,p1->data.major);
        if(p1->data.sno[0]!='f')
        {
            p1->next=shead;
            shead=p1;
            p1=(stunode*)malloc(sizeof(stunode));
            p1->data.sno[0]='f';
        }
        else break;
    }
    p1=shead;
    fclose(fp);
    
    counode *p2=(counode*)malloc(sizeof(counode));
    fp=fopen("course.txt","r");
    while(!feof(fp))
    {
        fscanf(fp,"%s%s%d",p2->data.cno,p2->data.cname,&p2->data.classHours);
        if(p2->data.cno[0]!='f')
        {
            p2->next=chead;
            chead=p2;
            p2=(counode*)malloc(sizeof(counode));
            p2->data.cno[0]='f';
        }
        else break;
    }
    p2=chead;
    
    fclose(fp);


    allnode *g1=(allnode*)malloc(sizeof(allnode));
    g1->next=NULL;
    allnode *g2=(allnode*)malloc(sizeof(allnode));
    g2->next=NULL;
    allnode *g3=(allnode*)malloc(sizeof(allnode));
    g3->next=NULL;
    int i;
    for(i=0;;++i)
    {
        if(strcmp(gra[i].cno,gra[i+1].cno)!=0)
        {
            strcpy(g1->data.sno,gra[i].sno);
            g1->data.score=gra[i].score;
            strcpy(g1->data.cno,gra[i].cno);
            g1head=g1;
            ++i;
            break;
        }
        else
        {
            strcpy(g1->data.sno,gra[i].sno);
            strcpy(g1->data.cno,gra[i].cno);
            g1->data.score=gra[i].score;
            g1head=g1;
            g1=(allnode*)malloc(sizeof(allnode));
            g1->next=g1head;
        }   
    }
    for(;;++i)
    {
        if(strcmp(gra[i].cno,gra[i+1].cno)!=0)
        {
            strcpy(g2->data.sno,gra[i].sno);
            strcpy(g2->data.cno,gra[i].cno);
            g2->data.score=gra[i].score;
            g2head=g2;
            ++i;
            break;
        }
        else
        {
            strcpy(g2->data.sno,gra[i].sno);
            strcpy(g2->data.cno,gra[i].cno);
            g2->data.score=gra[i].score;
            g2head=g2;
            g2=(allnode*)malloc(sizeof(allnode));
            g2->next=g2head;
        } 
    }
    for(;i<len;++i)
    {
            strcpy(g3->data.sno,gra[i].sno);
            strcpy(g3->data.cno,gra[i].cno);
            g3->data.score=gra[i].score;
            g3head=g3;
            g3=(allnode*)malloc(sizeof(allnode));
            g3->next=g3head; 
    }
    free(g3);g3=g3head;
    for(;g1;g1=g1->next)
    {
        cout<<g1->data.sno<<"\t";
        for(;p1;p1=p1->next)
        {
            if(strcmp(p1->data.sno,g1->data.sno)==0)
            {
                cout<<p1->data.sname<<"\t"<<p1->data.major<<"\t";
                strcpy(g1->data.sname,p1->data.sname),strcpy(g1->data.major,p1->data.major);
                p1=shead;
                break;
            }
        }
        for(;p2;p2=p2->next)
        {
            if(strcmp(p2->data.cno,g1->data.cno)==0)
            {
                cout<<p2->data.cname<<"\t";
                strcpy(g1->data.cname,p2->data.cname);
                p2=chead;
                break;
            }
        }
        cout<<g1->data.score<<"\n";
    }
    putchar('\n');

    for(;g2;g2=g2->next)
    {
        cout<<g2->data.sno<<"\t";
        for(;p1;p1=p1->next)
        {
            if(strcmp(p1->data.sno,g2->data.sno)==0)
            {
                cout<<p1->data.sname<<"\t"<<p1->data.major<<"\t";
                strcpy(g2->data.sname,p1->data.sname),strcpy(g2->data.major,p1->data.major);
                p1=shead;
                break;
            }
        }
        for(;p2;p2=p2->next)
        {
            if(strcmp(p2->data.cno,g2->data.cno)==0)
            {
                cout<<p2->data.cname<<"\t";
                strcpy(g2->data.cname,p2->data.cname);
                p2=chead;
                break;
            }
        }
        cout<<g2->data.score<<"\n";
    }
    putchar('\n');

    for(;g3;g3=g3->next)
    {
        cout<<g3->data.sno<<"\t";
        for(;p1;p1=p1->next)
        {
            if(strcmp(p1->data.sno,g3->data.sno)==0)
            {
                cout<<p1->data.sname<<"\t"<<p1->data.major<<"\t";
                strcpy(g3->data.sname,p1->data.sname),strcpy(g3->data.major,p1->data.major);
                p1=shead;
                break;
            }
        }
        for(;p2;p2=p2->next)
        {
            if(strcmp(p2->data.cno,g3->data.cno)==0)
            {
                cout<<p2->data.cname<<"\t";
                strcpy(g3->data.cname,p2->data.cname);
                p2=chead;
                break;
            }
        }
        cout<<g3->data.score<<"\n";
    }
}

void gracheck(allnode *g1head,allnode *g2head,allnode *g3head)
{
    if(g1head&&g2head&&g3head)
    {
        char c[20];
        cin>>c;
        if(!strcmp(c,g1head->data.cno))
        {
            while(g1head)
            {
                cout<<g1head->data.sno<<"\t"<<g1head->data.sname<<"\t"<<g1head->data.major<<"\t"<<g1head->data.cname<<"\t"<<g1head->data.score<<"\n";
                g1head=g1head->next;
            }
        }
        else if(!strcmp(c,g2head->data.cno))
        {
            while(g2head)
            {
                cout<<g2head->data.sno<<"\t"<<g2head->data.sname<<"\t"<<g2head->data.major<<"\t"<<g2head->data.cname<<"\t"<<g2head->data.score<<"\n";
                g2head=g2head->next;
            }
        }
        else if(!strcmp(c,g3head->data.cno))
        {
            while(g3head)
            {
                cout<<g3head->data.sno<<"\t"<<g3head->data.sname<<"\t"<<g3head->data.major<<"\t"<<g3head->data.cname<<"\t"<<g3head->data.score<<"\n";
                g3head=g3head->next;
            }
        }
    }
}

void failcheck(allnode *g1head,allnode *g2head,allnode *g3head)
{
    if(g1head&&g2head&&g3head)
    {
        char c[20];
        cin>>c;
        if(!strcmp(c,g1head->data.cno))
        {
            while(g1head)
            {
                if(g1head->data.score<60)
                    cout<<g1head->data.sno<<"\t"<<g1head->data.sname<<"\t"<<g1head->data.major<<"\t"<<g1head->data.cname<<"\t"<<g1head->data.score<<"\n";
                g1head=g1head->next;
            }
        }
        else if(!strcmp(c,g2head->data.cno))
        {
            while(g2head)
            {
                if(g2head->data.score<60)
                    cout<<g2head->data.sno<<"\t"<<g2head->data.sname<<"\t"<<g2head->data.major<<"\t"<<g2head->data.cname<<"\t"<<g2head->data.score<<"\n";
                g2head=g2head->next;
            }
        }
        else if(!strcmp(c,g3head->data.cno))
        {
            while(g3head)
            {
                if(g3head->data.score<60)
                    cout<<g3head->data.sno<<"\t"<<g3head->data.sname<<"\t"<<g3head->data.major<<"\t"<<g3head->data.cname<<"\t"<<g3head->data.score<<"\n";
                g3head=g3head->next;
            }
        }
    }
}

void stustack(stunode* shead)
{
    stack<student> mystack;
    stunode* p=shead;
    while(p)
    {
        mystack.push(p->data);
        p=p->next;
    }
    p=shead;
    while(!mystack.empty())
    {
        shead->data=mystack.top();
        mystack.pop();
        shead=shead->next;
    }
    while(p)
    {
        cout<<p->data.sno<<"\t"<<p->data.sname<<"\t"<<p->data.sex<<"\t"<<p->data.major<<"\n";
        p=p->next;
    }
}
void qucougrasort(stunode *&shead,counode *&chead,granode *&ghead,allnode* &g1head,allnode* &g2head,allnode* &g3head)
{
    delstu(shead);
    delcou(chead);
    delgra(ghead);
    delall(g1head);
    delall(g2head);
    delall(g3head);
    granode *p=(granode*)malloc(sizeof(granode));
    granode *q;
    p->next=NULL;
    granode *gra_rear=p;
    ghead=p;
    FILE *fp=fopen("grade.txt","r");
    while(!feof(fp))
    {
        fscanf(fp,"%s%s%d",p->data.sno,p->data.cno,&p->data.score);
        if(p->data.sno[0]!='f')
        {
            gra_rear=p;
            p=(granode*)malloc(sizeof(granode));
            gra_rear->next=p;
            p->data.sno[0]='f';
        }
        else break;
    }
    free(p);
    gra_rear->next=NULL;
    p=ghead;
    int len;
    for(len=0;p;++len)
        p=p->next;
    grade gra[len];
    for(int i=0;i<len;++i)
    {
        gra[i]=ghead->data;
        p=ghead;
        ghead=ghead->next;
        free(p);
    }
    sort(gra,gra+len,cmp4);
    
    fclose(fp);


    fp=fopen("grade.txt","w");
    for(int i=0;i<len;++i)
    {
        fprintf(fp,"%s\t%s\t%d\n",gra[i].sno,gra[i].cno,gra[i].score);
    }
    stunode *p1=(stunode*)malloc(sizeof(stunode));
    fclose(fp);
    sort(gra,gra+len,cmp5);
    fp=fopen("student.txt","r");
    while(!feof(fp))
    {
        fscanf(fp,"%s%s%s%s",p1->data.sno,p1->data.sname,p1->data.sex,p1->data.major);
        if(p1->data.sno[0]!='f')
        {
            p1->next=shead;
            shead=p1;
            p1=(stunode*)malloc(sizeof(stunode));
            p1->data.sno[0]='f';
        }
        else break;
    }
    p1=shead;
    fclose(fp);
    
    counode *p2=(counode*)malloc(sizeof(counode));
    fp=fopen("course.txt","r");
    while(!feof(fp))
    {
        fscanf(fp,"%s%s%d",p2->data.cno,p2->data.cname,&p2->data.classHours);
        if(p2->data.cno[0]!='f')
        {
            p2->next=chead;
            chead=p2;
            p2=(counode*)malloc(sizeof(counode));
            p2->data.cno[0]='f';
        }
        else break;
    }
    p2=chead;
    
    fclose(fp);


    allnode *g1=(allnode*)malloc(sizeof(allnode));
    g1->next=NULL;
    allnode *g2=(allnode*)malloc(sizeof(allnode));
    g2->next=NULL;
    allnode *g3=(allnode*)malloc(sizeof(allnode));
    g3->next=NULL;
    int i;
    for(i=0;;++i)
    {
        if(strcmp(gra[i].cno,gra[i+1].cno)!=0)
        {
            strcpy(g1->data.sno,gra[i].sno);
            g1->data.score=gra[i].score;
            strcpy(g1->data.cno,gra[i].cno);
            g1head=g1;
            ++i;
            break;
        }
        else
        {
            strcpy(g1->data.sno,gra[i].sno);
            strcpy(g1->data.cno,gra[i].cno);
            g1->data.score=gra[i].score;
            g1head=g1;
            g1=(allnode*)malloc(sizeof(allnode));
            g1->next=g1head;
        }   
    }
    for(;;++i)
    {
        if(strcmp(gra[i].cno,gra[i+1].cno)!=0)
        {
            strcpy(g2->data.sno,gra[i].sno);
            strcpy(g2->data.cno,gra[i].cno);
            g2->data.score=gra[i].score;
            g2head=g2;
            ++i;
            break;
        }
        else
        {
            strcpy(g2->data.sno,gra[i].sno);
            strcpy(g2->data.cno,gra[i].cno);
            g2->data.score=gra[i].score;
            g2head=g2;
            g2=(allnode*)malloc(sizeof(allnode));
            g2->next=g2head;
        } 
    }
    for(;i<len;++i)
    {
            strcpy(g3->data.sno,gra[i].sno);
            strcpy(g3->data.cno,gra[i].cno);
            g3->data.score=gra[i].score;
            g3head=g3;
            g3=(allnode*)malloc(sizeof(allnode));
            g3->next=g3head; 
    }
    g3=g3head;
    for(;g1;g1=g1->next)
    {
        cout<<g1->data.sno<<"\t";
        for(;p1;p1=p1->next)
        {
            if(strcmp(p1->data.sno,g1->data.sno)==0)
            {
                cout<<p1->data.sname<<"\t"<<p1->data.major<<"\t";
                strcpy(g1->data.sname,p1->data.sname),strcpy(g1->data.major,p1->data.major);
                p1=shead;
                break;
            }
        }
        for(;p2;p2=p2->next)
        {
            if(strcmp(p2->data.cno,g1->data.cno)==0)
            {
                cout<<p2->data.cname<<"\t";
                strcpy(g1->data.cname,p2->data.cname);
                p2=chead;
                break;
            }
        }
        cout<<g1->data.score<<"\n";
    }
    putchar('\n');

    for(;g2;g2=g2->next)
    {
        cout<<g2->data.sno<<"\t";
        for(;p1;p1=p1->next)
        {
            if(strcmp(p1->data.sno,g2->data.sno)==0)
            {
                cout<<p1->data.sname<<"\t"<<p1->data.major<<"\t";
                strcpy(g2->data.sname,p1->data.sname),strcpy(g2->data.major,p1->data.major);
                p1=shead;
                break;
            }
        }
        for(;p2;p2=p2->next)
        {
            if(strcmp(p2->data.cno,g2->data.cno)==0)
            {
                cout<<p2->data.cname<<"\t";
                strcpy(g2->data.cname,p2->data.cname);
                p2=chead;
                break;
            }
        }
        cout<<g2->data.score<<"\n";
    }
    putchar('\n');

    for(;g3;g3=g3->next)
    {
        cout<<g3->data.sno<<"\t";
        for(;p1;p1=p1->next)
        {
            if(strcmp(p1->data.sno,g3->data.sno)==0)
            {
                cout<<p1->data.sname<<"\t"<<p1->data.major<<"\t";
                strcpy(g3->data.sname,p1->data.sname),strcpy(g3->data.major,p1->data.major);
                p1=shead;
                break;
            }
        }
        for(;p2;p2=p2->next)
        {
            if(strcmp(p2->data.cno,g3->data.cno)==0)
            {
                cout<<p2->data.cname<<"\t";
                strcpy(g3->data.cname,p2->data.cname);
                p2=chead;
                break;
            }
        }
        cout<<g3->data.score<<"\n";
    }
}
int main()
{
    system("chcp 65001");
    stunode* shead=NULL;
    counode* chead=NULL;
    granode* ghead=NULL;
    allnode* g1head=NULL;
    allnode* g2head=NULL;
    allnode* g3head=NULL;
    int choice=1;
    int sum;
    while(choice)
    {
        printf("\n\n\n");
        printf("学生课程成绩查询系统\n"
			"*********************************************************\n"
			"1.输入学生记录（学号、姓名、性别、专业）：\n2.输入三门课程信息（课程号、课程名称、课时数）：\n3.输入上述同学的各选修课程成绩（学号、课程号、考试成绩）：\n4.从student.txt读取信息，并生成学号升序链表："
			"\n5.从course.txt读取信息，并生成课程号升序链表：\n6.从grade.txt读取信息，并生成学号和课程号升序链表：\n7.查询所有学生综合信息（学号、学生姓名、专业、课程名、考试成绩），并生成各个课程链表，将信息输入到grade.txt：\n8.完成(7)操作后，查询指定课程号综合信息：\n9.完成操作(7)后，查询指定课程成绩不及格学生的综合信息：\n"
			"10.使用栈将(4)生成的学生信息链表倒序：\n11.用队列完成(7)功能：\n0.退出程序：\n*********************************************************\n"
			"请输入您的选择：");
        cin>>choice;
        switch(choice)
        {
            case 1:printf("请输入添加信息所包含的学生人数："); cin>>sum;stuinit(sum,shead);break;
            case 2:couinit(chead);break;
            case 3:printf("请输入添加信息所包含的学生人数："); cin>>sum;grainit(sum,ghead);break;
            case 4:stusort(shead);break;
            case 5:cousort(chead);break;
            case 6:grasort(ghead);break;
            case 7:cougrasort(shead,chead,ghead,g1head,g2head,g3head);break;
            case 8:gracheck(g1head,g2head,g3head);break;
            case 9:failcheck(g1head,g2head,g3head);break;
            case 10:stustack(shead);break;
            case 11:qucougrasort(shead,chead,ghead,g1head,g2head,g3head);break;
            case 0:break;
        }
        if(!choice) break;
    }
    system("pause");
    return 0;
}