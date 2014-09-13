/**
*  左偏树
**/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100100;
int fa[maxn];

struct Monkey
{
    int l, r;
    int dis;
    int strong;
}Ltree[maxn];

int find(int x)
{
    if(x != fa[x])
        fa[x] = find(fa[x]);
    return fa[x];
}

int merge(int x, int y)
{
    if(x == 0)  return y;
    if(y == 0)  return x;
    if(Ltree[x].strong < Ltree[y].strong)
        swap(x, y);
    Ltree[x].r = merge(Ltree[x].r, y);
    int l = Ltree[x].l, r = Ltree[x].r;
    fa[r] = x;
    if(Ltree[l].dis < Ltree[r].dis)
        swap(Ltree[x].l, Ltree[x].r);
    if(Ltree[x].r == 0)
        Ltree[x].dis = 0;
    else
        Ltree[x].dis = Ltree[ Ltree[r].r ].dis + 1;
    return x;
}

int del(int x)
{
    int l, r;
    l = Ltree[x].l;
    r = Ltree[x].r;
    fa[l] = l;
    fa[r] = r;
    Ltree[x].l = Ltree[x].r = Ltree[x].dis = 0;
    return merge(l, r);
}

void solve(int x, int y)
{
    Ltree[x].strong /= 2;
    Ltree[y].strong /= 2;
    int left, right;
    left = del(x);
    right = del(y);
    left = merge(left, x);
    right = merge(right, y);
    left = merge(left, right);
    printf("%d\n", Ltree[left].strong);
}

int main()
{
    int n, m, i, x, y;
    while(scanf("%d", &n) != EOF)
    {
        for(int i = 1; i <= n; i++)
        {
            scanf("%d", &Ltree[i].strong);
            Ltree[i].l = Ltree[i].r = Ltree[i].dis = 0;
            fa[i] = i;
        }
        scanf("%d", &m);
        for(int i = 1; i <= m; i++)
        {
            scanf("%d%d", &x, &y);
            int fx = find(x), fy = find(y);
            if(fx == fy)
            {
                printf("-1\n");
            }
            else
            {
                solve(fx, fy);
            }
        }
    }
    return 0;
}
