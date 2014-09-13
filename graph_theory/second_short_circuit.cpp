/*************************************************************
次短路
第一种方法：用一个二维数组记录每一个节点距离起始点的最短距离和次短距离，再开一个二维数组记录路径数
第二种方法： 可以分别对1和n进行两次Dijkstra，然后枚举边，产生新的一条路，即两点分别到1和n的距离和加上这条边的距离。
*************************************************************/
using namespace std;
const int maxn = 5010;
const int maxm = 100100;
const int INF = 0x7fffffff;
struct Edge
{
    int v, w;
    int next;
}edges[2*maxm];

int head[maxn], cnt;
int n, m;
int dis[maxn][2], vis[maxn][2];

struct Node
{
    int u, k;
    Node() {}
    Node(int u, int k): u(u), k(k) {}

    bool operator < (const Node& a) const
    {
        return dis[u][k] > dis[ a.u ][ a.k ];
    }
};
void addEdge(int u, int v, int w)
{
    edges[cnt].v = v;
    edges[cnt].w = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

void Dijkstra()
{
    for(int i = 1; i <= n; i++)
    {
        dis[i][0] = dis[i][1] = INF;
        vis[i][0] = vis[i][1] = 0;
    }
    dis[1][0] = 0;
    priority_queue<Node> q;
    q.push(Node(1, 0));
    while(!q.empty())
    {
        Node tmp = q.top(); q.pop();
        int u = tmp.u;      int k = tmp.k;
        if(vis[u][k])
            continue;
        vis[u][k] = 1;
        for(int i = head[u]; i != -1; i = edges[i].next)
        {
            int v = edges[i].v;
            int w = edges[i].w;
            if(dis[u][k] + w < dis[v][0] )
            {
                dis[v][1] = min(dis[v][0], dis[v][1]);
                dis[v][0] = dis[u][k] + w;
                q.push(Node(v, 0));
            }
            else if(dis[u][k] + w != dis[v][0] &&  dis[u][k] + w < dis[v][1])  // 这里避免次短路和最短路一样长的情况
            {
                dis[v][1] = dis[u][k] + w;
                q.push(Node(v, 1));
            }
        }
    }
}

int main()
{
    int v, u, w;
    while(scanf("%d%d", &n, &m)!=EOF)
    {
        cnt = 0;
        memset(head, -1, sizeof(head));
        for(int i = 1; i <= m; i++)
        {
            scanf("%d%d%d", &u, &v, &w);
            addEdge(u, v, w);
            addEdge(v, u, w);
        }
        Dijkstra();
        printf("%d\n", dis[n][1]);
    }
    return 0;
}

using namespace std;
const int maxn = 5010;
const int maxm = 100100;
const int INF = 0x7fffffff;
struct Edge
{
    int v, w;
    int next;
}edges[2*maxm];

int head[maxn], cnt;
int n, m;
int dis1[maxn], disn[maxn];
int inque[maxn];

void addEdge(int u, int v, int w)
{
    edges[cnt].v = v;
    edges[cnt].w = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

void SPFA(int s, int *dis)
{
    for(int i = 1; i <= n; i++)
    {
        dis[i] = INF;
        inque[i] = 0;
    }
    dis[s] = 0;
    inque[s] = 1;
    queue<int> q;
    q.push(s);
    while(!q.empty())
    {
        int u = q.front();      q.pop();
        inque[u] = 0;
        for(int i = head[u]; i != -1; i = edges[i].next)
        {
            int v = edges[i].v;
            int w = edges[i].w;
            if(dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                if(!inque[v])
                {
                    inque[v] = 1;
                    q.push(v);
                }
            }
        }
    }
}

int main()
{
    int v, u, w;
    while(scanf("%d%d", &n, &m)!=EOF)
    {
        cnt = 0;
        memset(head, -1, sizeof(head));
        for(int i = 1; i <= m; i++)
        {
            scanf("%d%d%d", &u, &v, &w);
            addEdge(u, v, w);
            addEdge(v, u, w);
        }
        SPFA(1, dis1);
        SPFA(n, disn);

        int ans = INF;
        for(int i = 1; i <= n; i++)
        {
            for(int e = head[i]; e != -1; e = edges[e].next)
            {
                int j = edges[e].v;
                int w = edges[e].w;
                if(dis1[i] + w + disn[j] > dis1[n])
                {
                    ans = min(ans, dis1[i] + w + disn[j]);
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
