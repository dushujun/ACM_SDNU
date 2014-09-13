/**
*2-SAT算法
*/
int n,tot,head[N];
struct edge
{
    int v,next;
} e[M];
vector<int>ver[N];
vector<int>ans;
queue<int>que;
int dfn[N],low[N],belong[N],stack[N],dcnt,bcnt,top;
bool ins[N];
int inde[N],opp[N],color[N];

inline void add(int u,int v)
{
    e[tot].v = v;
    e[tot].next = head[u];
    head[u] = tot++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++dcnt;
    stack[++top] = u;
    ins[u] = true;
    for(int k = head[u]; k != -1; k = e[k].next)
    {
        int v = e[k].v;
        if(!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u],low[v]);
        }
        else if(ins[v])
            low[u] = min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u])
    {
        ++bcnt;
        while(true)
        {
            int x = stack[top--];
            ins[x] = false;
            belong[x] = bcnt;
            if(x == u) break;
        }
    }
}

void scc()
{
    dcnt = bcnt = top = 0;
    cl(dfn,0,sizeof(dfn));
    cl(ins,false,sizeof(ins));
    for(int i = 0; i < 2*n; i++)
        if(!dfn[i])
            tarjan(i);
}

bool check()
{
    for(int i = 0; i < n ; i++)
    {
        if(belong[i<<1] == belong[i<<1|1])
            return false;
        opp[belong[i<<1]] = belong[i<<1|1];
        opp[belong[i<<1|1]] = belong[i<<1];
    }
    return true;
}

void rebuild()
{
    for(int i = 1; i <= bcnt; i++)
    {
        ver[i].clear();
        inde[i] = 0;
    }
    for(int i = 0; i < 2*n; i++)
        for(int k = head[i]; k != -1; k = e[k].next)
        {
            int u = belong[i] , v = belong[e[k].v];
            if(u == v) continue;
            ver[v].pb(u);
            inde[u]++; //建逆图
        }
}

void topsort()
{
    cl(color,0,sizeof(color));
    while(!que.empty()) que.pop();
    for(int i = 1; i <= bcnt; i++)
        if(inde[i] == 0)
            que.push(i);
    while(!que.empty())
    {
        int u,v;
        u = que.front();
        que.pop();
        if(!color[u])
        {
            color[u] = 1;
            color[opp[u]] = 2;
        }
        for(int i = 0; i < ver[u].size(); i++)
        {
            v = ver[u][i];
            inde[v]--;
            if(inde[v] == 0) que.push(v);
        }
    }
}

void Find_Ans()
{
    for(int i = 2; i < 2*n; i++)
        if(color[belong[i]] == color[belong[0]])
        {
            printf("%d%c ", i>>1 , (i&1) ? 'h' : 'w');
        }
    printf("\n");

}
