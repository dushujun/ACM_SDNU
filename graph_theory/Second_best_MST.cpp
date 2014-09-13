/************************************************
次小生成树
首先求出原图最小生成树，记录权值之和为MinST。枚举添加每条不在最小生成树上的边(u,v)，加上以后一定会形成一个环。找到环上权值第二大的边(即除了(u,v)以外的权值最大的边)，把它删掉，计算当前生成树的权值之和。取所有枚举修改的生成树权值之和的最小值，就是次小生成树。
具体实现时，更简单的方法是从每个节点i遍历整个最小生成树，定义F[j]为从i到j的路径上最大边的权值。遍历图求出F[j]的值，然后对于添加每条不在最小生成树中的边(i,j)，新的生成树权值之和就是MinST + w(i,j) - F[j]，记录其最小值，则为次小生成树。
************************************************/
#define maxn 1003
#define inf 1000000000

int x[maxn], y[maxn], p[maxn];
double map[maxn][maxn];
double dis[maxn];
int pre[maxn];
bool vis[maxn];
double mst;
double dp[maxn][maxn];

double maxz(double a, double b)
{
    return a > b ? a : b;
}

int n, m;
double ans;

double Dis(int x1, int y1, int x2, int y2)
{
    return sqrt((x1 - x2) * (x1 - x2) * 1.0 + (y1 - y2) * (y1 - y2) * 1.0);
}

void prim()
{
    int i, j, k;
    memset(dp, 0, sizeof(dp));
    for(i = 1; i < n; i++)
        dis[i] = map[0][i], vis[i] = 0, pre[i] = 0;
    dis[0] = inf, vis[0] = 1, pre[0] = -1;
   
    mst = 0;
    for(i = 0; i < n-1; i++)
    {
        k = 0;
        for(j = 1; j < n; j++)
            if(!vis[j] && dis[k] > dis[j])
                k = j;
        vis[k] = 1;
        mst += dis[k];
        dp[pre[k]][k] = dp[k][pre[k]] = map[k][pre[k]];

        for(j = 1; j < n; j++)
            if(!vis[j] && dis[j] > map[k][j])
                dis[j] = map[k][j], pre[j] = k;
        for(j = 1; j < n; j++) 
             if(vis[j] && j != k) 
                  dp[j][k] = dp[k][j] = maxz(dp[j][pre[k]], dp[pre[k]][k]);
    }
}

void solve()
{
    int i, j;
    double ans = 0;
    for(i = 0; i < n ;i++)
        for(j = 0; j < n; j++)
        {
            if(i == j) continue;
            double tmp = (p[i] + p[j]) * 1.0/ (mst - dp[i][j]);
            if(tmp > ans) ans = tmp;
        }
    printf("%.2f\n", ans);
}

int main()
{
    int i, j, cas;
    scanf("%d", &cas);
    while(cas--)
    {
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%d%d%d", &x[i], &y[i], &p[i]);
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                if(i != j)
                    map[i][j] = map[j][i] = Dis(x[i], y[i], x[j], y[j]);
        prim();
        solve();
    }
    return 0;
}
