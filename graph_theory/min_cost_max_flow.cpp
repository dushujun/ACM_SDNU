/********************************************************
最小费用最大流
********************************************************/
int cap[maxn][maxn], cost[maxn][maxn];
int S, T, n, m, k;
int que[maxn], inque[maxn], dis[maxn];
int mincost, head, tail, path[maxn];

bool SPFA()
{
    head = tail = 0;
    for(int i = 0; i <= T; i++)
    {
        dis[i] = INF, path[i] = -1, inque[i] = 0;
    }
    dis[S] = 0;
    que[tail++] = S;
    inque[S] = 1;
    while(head != tail)
    {
        int u = que[head++];
        if(head == maxn)
            head = 0;
        inque[u] = 0;
        for(int i = 0; i <= T; i++)
        {
            if(cap[u][i] && dis[i] > dis[u]+cost[u][i])
            {
                dis[i] = dis[u] + cost[u][i];
                path[i] = u;
                if(!inque[i])
                {
                    inque[i] = 1;
                    que[tail++] = i;
                    if(tail == maxn)
                        tail = 0;
                }
            }
        }
    }
    return dis[T] != INF;
}

int getMaxFlow()
{
    int maxFlow = 0, now;
    while(SPFA())
    {
        int flow = INF;
        now = T;
        while(now != S)
        {
            flow = min(flow, cap[path[now]][now] );
            now = path[now];
        }
        now = T;
        while(now != S)
        {
            cap[ path[now] ][now] -= flow;
            cap[now][ path[now] ] += flow;
            maxFlow += flow * cost[ path[now] ][now];
            now = path[now];
        }
    }
    return maxFlow;
}


int main()
{
    int need[maxn][maxn], needK[maxn], have[maxn][maxn], haveK[maxn];
    while(scanf("%d%d%d", &n, &m, &k))
    {
        if(!n && !m &&!k)
            break;
        memset(have, 0, sizeof(have));
        memset(haveK, 0, sizeof(haveK));
        memset(need, 0, sizeof(need));
        memset(needK, 0, sizeof(needK));
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= k; j++)
            {
                scanf("%d", &need[i][j]);
                needK[j] += need[i][j];
            }
        }

        for(int i = 1; i <= m; i++)
        {
            for(int j = 1; j <= k; j++)
            {
                scanf("%d", &have[i][j]);
                haveK[j] += have[i][j];
            }
        }
        bool flag = true;
        for(int i = 1; i <= k; i++)
        {
            if(needK[i] > haveK[i])
            {
                flag = false;
                break;
            }
        }
        S = 0, T = n + m + 1;
        mincost = 0;
        for(int goods = 1; goods <= k; goods++)
        {
            memset(cap, 0, sizeof(cap));
            memset(cost, 0, sizeof(cost));
            for(int i = 1; i <= n; i++)
            {
                for(int j = 1; j <= m; j++)
                {
                    scanf("%d", &cost[i][j+n]);
                    cost[j+n][i] = -cost[i][j+n];
                    cap[i][j+n] = INF;
                }
            }
            if(!flag)
                continue;

            for(int i = 1; i <= n; i++)
            {
                cap[S][i] = need[i][goods];
            }
            for(int j = 1; j <= m; j++)
                cap[j+n][T] = have[j][goods];

            mincost += getMaxFlow();
        }
        if(!flag)
            printf("-1\n");
        else
            printf("%d\n", mincost);
    }
    return 0;
}
