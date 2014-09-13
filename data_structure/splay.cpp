// 伸展树模板
// Problem: NOI2005 sequence
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;
const int MAXN=2850003,MAXL=500001,INF=1001;
struct SplayTree
{
    struct SplayNode
    {
        SplayNode *c[2],*f;
        int value,size,sum,maxsum,mls,mrs;
        bool rev,same;
    }*root,*null,*lb,*rb,SS[MAXN];
    int SC;
    SplayNode * NewNode(int value,SplayNode *f)
    {
        SplayNode *e=SS+ ++SC;
        e->value=value;
        e->size=1;e->f=f;
        e->sum=e->maxsum=e->mls=e->mrs=value;
        e->same=e->rev=false;
        e->c[0]=e->c[1]=null;
        return e;
    }
    inline int max(int a,int b){return a>b?a:b;}
    void update(SplayNode *p)
    {
        if (p==null) return;
        p->size = p->c[0]->size + p->c[1]->size + 1;
        p->sum = p->c[0]->sum + p->c[1]->sum + p->value;
        p->mls = p->c[0]->mls;
        p->mls = max( p->mls , p->c[0]->sum + p->value);
        p->mls = max( p->mls , p->c[0]->sum + p->value + p->c[1]->mls );
        p->mrs = p->c[1]->mrs;
        p->mrs = max( p->mrs , p->c[1]->sum + p->value);
        p->mrs = max( p->mrs , p->c[1]->sum + p->value + p->c[0]->mrs );
        p->maxsum = p->value;
        p->maxsum = max( p->maxsum , p->c[0]->maxsum );
        p->maxsum = max( p->maxsum , p->c[1]->maxsum );
        p->maxsum = max( p->maxsum , p->c[0]->mrs + p->value );
        p->maxsum = max( p->maxsum , p->c[1]->mls + p->value );
        p->maxsum = max( p->maxsum , p->c[0]->mrs + p->c[1]->mls + p->value );
    }
    void pushdown(SplayNode *p)
    {
        if (p==null) return;
        if (p->rev)
        {
            p->rev=false;
            SplayNode *q=p->c[0]; p->c[0]=p->c[1]; p->c[1]=q;
            p->c[0]->rev = !p->c[0]->rev;
            p->c[1]->rev = !p->c[1]->rev;
            int t=p->mls;
            p->mls=p->mrs; p->mrs=t;
        }
        if (p->same)
        {
            p->same=false;
            p->c[0]->same=p->c[1]->same=true;
            p->c[0]->value=p->c[1]->value=p->value;
            p->sum = p->maxsum = p->mls = p->mrs = p->value * p->size;
            if (p->value < 0)
                p->maxsum = p->mls = p->mrs = p->value;
        }
    }
    void rotate(SplayNode *x,int o)//Zig o=0 Zag o=1
    {
        SplayNode *y=x->f;
        pushdown(x->c[0]);
        pushdown(x->c[1]);
        pushdown(y->c[!o]);
        y->c[o] = x->c[!o];
        y->c[o]->f=y;
        x->f = y->f;
        if (y->f->c[0]==y)
            y->f->c[0]=x;
        else
            y->f->c[1]=x;
        y->f=x;
        x->c[!o]=y;
        update(y);
        update(x);
        if (root==y) root=x;
    }
    void splay(SplayNode *x,SplayNode *y)
    {
        pushdown(x);
        while (x->f!=y)
        {
            if (x->f->f==y)
            {
                if (x->f->c[0]==x)
                    rotate(x,0);
                else
                    rotate(x,1);
            }
            else if (x->f->f->c[0] == x->f)
            {
                if (x->f->c[0]==x)
                    rotate(x->f,0),rotate(x,0);
                else
                    rotate(x,1),rotate(x,0);
            }
            else
            {
                if (x->f->c[1]==x)
                    rotate(x->f,1),rotate(x,1);
                else
                    rotate(x,0),rotate(x,1);
            }
        }
    }
    void select(int k,SplayNode *y)
    {
        SplayNode *x=root;
        pushdown(x);
        for (;k != x->c[0]->size + 1;)
        {
            if (k <= x->c[0]->size)
                x=x->c[0];
            else
            {
                k-=x->c[0]->size + 1;
                x=x->c[1];
            }
            pushdown(x);
        }
        splay(x,y);
    }
    void Insert(int pos,int tot,int *C)
    {
        SplayNode *z,*t;
        z=t=NewNode(C[1],null);
        for (int i=2;i<=tot;i++)
            z=z->c[1]=NewNode(C[i],z);
        select(pos+1,null);
        select(pos+2,root);
        root->c[1]->c[0] = t;
        t->f=root->c[1];
        splay(z,null);
    }
    void Delete(int pos,int tot)
    {
        select(pos,null);
        select(pos+tot+1,root);
        root->c[1]->c[0] = null;
        splay(root->c[1],null);
    }
    void MakeSame(int pos,int tot,int value)
    {
        select(pos,null);
        select(pos+tot+1,root);
        root->c[1]->c[0]->same=true;
        root->c[1]->c[0]->value=value;
        splay(root->c[1]->c[0],null);
    }
    void Reverse(int pos,int tot)
    {
        select(pos,null);
        select(pos+tot+1,root);
        root->c[1]->c[0]->rev=!root->c[1]->c[0]->rev;
        splay(root->c[1]->c[0],null);
    }
    int GetSum(int pos,int tot)
    {
        select(pos,null);
        select(pos+tot+1,root);
        pushdown(root->c[1]->c[0]);
        return root->c[1]->c[0]->sum;
    }
    int MaxSum()
    {
        pushdown(root);
        update(root);
        return root->maxsum;
    }
    void init()
    {
        SC=-1;
        null=0;
        null=NewNode(-INF,0);
        null->size=0;
        lb=root=NewNode(-INF,null);
        rb=root->c[1]=NewNode(-INF,root);
        null->sum = lb->sum = rb->sum=0;
        update(root);
    }
}Splay;
int N,M,C[MAXL],pos,i,j,A;
char Ctrl[20];
int main()
{
    freopen("seq2005.in","r",stdin);
    freopen("seq2005.out","w",stdout);
    Splay.init();
    scanf("%d%d",&N,&M);
    for (i=1;i<=N;i++)
        scanf("%d",&C[i]);
    Splay.Insert(0,N,C);
    for (i=1;i<=M;i++)
    {
        scanf("%s",Ctrl);
        switch (Ctrl[0])
        {
            case 'I':
                scanf("%d%d",&pos,&N);
                for (j=1;j<=N;j++)
                    scanf("%d",&C[j]);
                Splay.Insert(pos,N,C);
                break;
            case 'D':
                scanf("%d%d",&pos,&N);
                Splay.Delete(pos,N);
                break;
            case 'R':
                scanf("%d%d",&pos,&N);
                Splay.Reverse(pos,N);
                break;
            case 'G':
                scanf("%d%d",&pos,&N);
                A=Splay.GetSum(pos,N);
                printf("%d\n",A);
                break;
            case 'M':
                if (Ctrl[2]=='K')
                {
                    scanf("%d%d%d",&pos,&N,&C[0]);
                    Splay.MakeSame(pos,N,C[0]);
                }
                else
                    printf("%d\n",Splay.MaxSum());
                break;
        }
    }
    return 0;
}

