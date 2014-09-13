 /**********************************************************************
 LCA：Least Common Ancestors（最近公共祖先），对于一棵有根树T的任意两个节点u，v，求出LCA(T, u, v)，
即离跟最远的节点x，使得x同时是u和v的祖先。
 在线算法：用比较长的时间做预处理，但是等信息充足以后每次回答询问只需要用比较少的时间。
 离线算法：先把所有的询问读入，然后一起把所有询问回答完成。
在线算法描述：
1）DFS：从树T的根开始，进行深度优先遍历，并记录下每次到达的顶点。第一个的结点是root(T)，每经过一条边都记录它的端点。由于每条边恰好经过2次，因此一共记录了2n-1个结点，用E[1, ... , 2n-1]来表示。
      （2）计算R：用R[i]表示E数组中第一个值为i的元素下标，即如果R[u] < R[v]时，DFS访问的顺序是E[R[u], R[u]+1, ..., R[v]]。虽然其中包含u的后代，但深度最小的还是u与v的公共祖先。
      （3）RMQ：当R[u] ≥ R[v]时，LCA[T, u, v] = RMQ(L, R[v], R[u])；否则LCA[T, u, v] = RMQ(L, R[u], R[v])，计算RMQ。
**********************************************************************/
#define N 100010
#define MAXK 10010
using namespace std;

struct Edge1
{
    int v, w;
    int next;
}edges1[N];

struct Edge2
{
    int v, qid;
    int next;
}edges2[2*MAXK];

int head1[N], head2[N], cnt1, cnt2;
int n, m, fa[N], depth[N], dis[N], vis[N];
int result[2*MAXK];

void initGraph()
{
    memset(head1, -1, sizeof(head1));
    cnt1 = 0;
    memset(head2, -1, sizeof(head2));
    cnt2 = 0;
}

void addEdge1(int u, int v, int w)
{
    edges1[cnt1].v = v;
    edges1[cnt1].w = w;
    edges1[cnt1].next = head1[u];
    head1[u] = cnt1++;
}

void addEdge2(int u, int v, int id)
{
    edges2[cnt2].v = v;
    edges2[cnt2].qid = id;
    edges2[cnt2].next = head2[u];
    head2[u] = cnt2++;
}

int findFather(int a)
{
    if(a == fa[a])
        return a;

    return fa[a] = findFather(fa[a]);
}

// u 表示目前搜索的子树的根， len 表示到 root 的距离
void tarjan_lca(int u, int len)
{
    dis[u] = len;
    vis[u] = 1;
    fa[u] = u;
    for(int i = head1[u]; i != -1; i = edges1[i].next)
    {
        int v = edges1[i].v;
        int w = edges1[i].w;
        if(!vis[v])
        {
            tarjan_lca(v, len+w);
            fa[v] = u;
        }
    }

    for(int i = head2[u]; i != -1; i = edges2[i].next)
    {
        int v = edges2[i].v;
        int id = edges2[i].qid;
        if(vis[v])
        {
            int ancestor = findFather(v);
            result[id] = dis[u] + dis[v] - dis[ancestor]*2;
        }
    }
}

int main()
{
    int k, u, v, w;
    char str[5];
    while(scanf("%d%d", &n, &m) != EOF)
    {
        initGraph();
        for(int i = 0; i < m; i++)
        {
            scanf("%d%d%d%s", &u, &v, &w, str);
            addEdge1(u, v, w);  addEdge1(v, u, w);
        }
        scanf("%d", &k);
        for(int i = 0; i < k; i++)
        {
            scanf("%d %d", &u, &v);
            addEdge2(u, v, i); addEdge2(v, u, i);
        }

        memset(vis, 0, sizeof(vis));
        tarjan_lca(1, 0);
        for(int i = 0; i < k; i++)
            printf("%d\n", result[i]);
    }
    return 0;
}
