/*******************************************************
强连通 有向图 Tarjan算法
********************************************************/
class Graph
{
public:

    void init()
    {
        size = 0;
        memset(head, -1, sizeof(head));
    }

    void addEdge(int u, int v)
    {
        edges[size].v = v;
        edges[size].next = head[u];
        head[u] = size++;
    }

public:
    int size ;
    int head[maxn];
    struct Edge
    {
        int v;
        int next;
    }edges[EN];

}g;


class Two_Sat
{
public:

    bool check(const Graph& g, const int n)
    {
        scc(g, n);
        for(int i = 0; i < n; i++)
            if(belong[i*2] == belong[i*2+1])
                return false;
        return true;
    }

private:
    int belong[maxn];
    int DFN[maxn], low[maxn];
    bool instack[maxn];
    int sta[maxn]; // 模拟栈
    int top; // 栈顶标识
    int idx; // 时间戳
    int bcnt; // 强连通分量数
    // 求图的强联通分量
    void scc(const Graph& g, const int n)
    {
        memset(DFN, -1, sizeof(DFN));
        memset(instack, 0, sizeof(instack));
        top = bcnt = idx = 0;
        for(int i = 0; i < 2 * n; i++)
            if(DFN[i] == -1)
            {
                tarjan(g, i);
            }
    }

     // tarjan缩点
    void tarjan(const Graph& g,const int u)
    {
        int v;
        low[u] = DFN[u] = ++idx;
        // 这个位置入栈
        instack[u] = true;
        sta[top++] = u;
        for(int e = g.head[u]; e != -1; e = g.edges[e].next)
        {
            v = g.edges[e].v;
            if(DFN[v] == -1)
            {
                tarjan(g, v);
                low[u] = min(low[u], low[v]);
            }else if(instack[v])
            {
                low[u] = min(low[u], DFN[v]);
            }
        }
        if(low[u] == DFN[u])
        {
            ++bcnt;  // 只在这个位置，也就是出栈的时候才能增加分量数
            do
            {
                v = sta[--top];
                instack[v] = false;
                belong[v] = bcnt;
            }while(v != u);
        }
    }
}sat
