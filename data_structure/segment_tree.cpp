// 线段树 扫描线 长方形面积并

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 20100
using namespace std;

struct Node
{
    int L, R;
    int ml, mr;
    int level;
}nodes[100*N];

int n;
int x[100*N], y[100*N];
int visible[100*N];

void build(int i, int left, int right)
{
    nodes[i].L = left;
    nodes[i].R = right;
    nodes[i].ml = y[left];
    nodes[i].mr = y[right];
    nodes[i].level = 0;

    if(left == right)
        return;

    int mid = (left+right)>>1;
    build(2*i, left, mid);
    build(2*i+1, mid+1, right);
}

void update(int i, int left, int right, int level)
{
    if(nodes[i].ml >= left && nodes[i].mr <= right)
    {
        nodes[i].level = level;
        return;
    }
    if(nodes[i].level != 0)
    {
        nodes[i*2].level = nodes[i*2+1].level = nodes[i].level;
        nodes[i].level = 0;
    }
    int mid = (nodes[i].L + nodes[i].R)>>1;
    if(y[mid] >= right)
    {
        update(2*i, left, right, level);
    }
    else if(y[mid+1] <= left)
    {
        update(2*i+1, left, right, level);
    }
    else
    {
        update(2*i, left, y[mid], level);
        update(2*i+1, y[mid+1], right, level);
    }
    return;
}

void query(int i, int *vis)
{
    //if(nodes[i].L == nodes[i].R)
    //{
     //   vis[ nodes[i].level ] = 1;
       // return;
    //}
    if(nodes[i].level != 0)
    {
        vis[ nodes[i].level ] = 1;
    }
    else
    {
        query(2*i, vis);
        query(2*i+1, vis);
    }
}

int main()
{
    int T, x1, x2;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        int k = 1;
        for(int i = 1; i <= n; i++)
        {
            scanf("%d %d", &x1, &x2);
            x[k] = y[k] = x1;
            k++;
            x[k] = y[k] = x2;
            k++;
        }
        sort(y+1, y+k);
        int m = 2;
        for(int i = 2; i < k; i++)
        {
            if(y[i] != y[i-1])
            {
                y[m++] = y[i];
            }
        }

        for(int i = k-2; i >= 1; i--)
        {
            if(y[i] + 1 < y[i+1] )
            {
                y[m++] = y[i] + 1;
            }
        }
        sort(y+1, y+m);
        build(1, 1, m-1);
        for(int i = 1; i <= n; i++)
        {
            update(1, x[2*i-1], x[2*i], i);
        }

        memset(visible, 0, sizeof(visible));
        query(1, visible);
        int counts = 0;
        for(int i = 1; i <= n; i++)
        {
            if(visible[i])
                counts++;
        }
        printf("%d\n", counts);
    }
    return 0;
}
