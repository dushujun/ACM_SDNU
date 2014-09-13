/***************************************************************

所谓A*就是启发是搜索..说白了就是给BFS搜索一个顺序使得搜索更加合理减少无谓的搜索..如何来确定搜索的顺序？..
也就是用一个值来表示这个值为f[x]..每次搜索取f[x]最小的拓展...那么这个f[x]=h[x]+g[x]其中这个h[x]就是当前搜索时的代价..
如求K段路这个就是前一个点的h[x']+边的长度...而g[x]是一个估价函数..估价函数要小于是对当前点到目标的代价的估计..
这个估计必须小于等于实际值~~否则会出错...A*的关键也就是构造g[x]..而这里要说的求K短路一种方法..
就是用BFS+A*来搜索的过程...g[x]的设定为到这个点到目标点的最短路径...显然其实小于等于实际值的...
h[x]就是搜索到这个点的代价..用一个优先队列来做..每次取出h[x]+g[x]最小的点来拓展...拓展也就是通过
这点来更新其能直接经过一条边到达的点..这里做好一个新点就丢进优先队列里去..反正总会从对首弹出h[x]+g[x]
最小的点..可以想一下...如果当前取出的优先队列头是一个点e并且是第一次取出h..那么就找到了一条从源点到h的最短路径..
这里其实很djikstra的感觉差不多..如果第二次在对头取出了e..则是找到了一条从源点到h的第二短路径..依次类推..第几次从对头弹出e..
则找到了从源点到e的第几短路径..那要是本身就不存在K短路呢？？那就是e拓展不到K但是其他点很有可能一直打圈圈无限下去...
这里就要用个条件来判断一下...首先在找某个点作为优先队列头出现了几次就用了一个计数器times[]..所求的点times[e]==k就代表得到了解..
如果当前想拓展的点times[]>k就没必要拓展了..因为这个点已经是求到k+1短路了..从这个点继续往下搜肯定得到的是大于等于k+1短路的路径...
就像1->2有3条路..2->3有2条路..那1->3有6条路的概念差不多..没必要对其进行拓展了..
还有一点要特别注意的就是题目要求必须要走..也就是s==e时..k++....

这里有几个需要注意的地方， A*算法的关键就是求 函数 f[x] = h[x] + g[x]  。 h[x] 的构建为当前搜索的代价， f[x] 的构建为当前点到目标点的估价.
每次选取f[x] 值最小的扩展，所以需要一个优先队列。 
计数器times[] 的作用一方面是寻找第k最短路， 还可以借助 times[] 计数器进行优化，减少不必要的搜索！。
***************************************************************/
#define INF 0x7fffffff
using namespace std;
const int maxn = 1010;
const int maxm = 100010;

struct Edge
{
    int u, v;
    int w;
    int next;
}edges[maxm], redges[maxm];  // 因为下表写成了maxn WA了两次，下次要谨记

int cnt, head[maxn], recnt, rehead[maxn];
int n, m;
int S, T, K;
int g[maxn];
bool vis[maxn];
int times[maxn]; 
// 搜索到的节点结构体
struct Node
{
    int pos;
    int g, h;
    bool operator < (const Node& a) const
    {
        return a.g + a.h < g + h;
    }
};


void addEdge(int u, int v, int w)
{
    edges[cnt].u = u;
    edges[cnt].v = v;
    edges[cnt].w = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

// 存反图，为构建g[x]
void addEdge2(int u, int v, int w)
{
    redges[recnt].u = u;
    redges[recnt].v = v;
    redges[recnt].w = w;
    redges[recnt].next = rehead[u];
    rehead[u] = recnt++;
}

// 构建 g[x]
void Dijkstra()
{
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i <= n; i++)
    {
        g[i] = INF;
    }
    g[T] = 0;
    for(int i = 1; i <= n; i++)
    {
        int mindis = INF, minnode;
        for(int i = 1; i <= n; i++)
        {
            if(!vis[i] && g[i] < mindis)
            {
                mindis = g[i];
                minnode = i;
            }
        }

        vis[minnode] = true;
        for(int e = rehead[minnode]; e != -1 ;e = redges[e].next)
        {
            int v = redges[e].v;
            int w = redges[e].w;
            if(!vis[v] && g[v] > g[minnode] + w)
            {
                g[v] = g[minnode] + w;
            }
        }
    }

}
// 算法的主题
int Astar()
{
    memset(times, 0, sizeof(times));   // 计数器
    priority_queue<Node> myqueue;  // 优先队列
    Node first, second;
    first.pos = S, first.g = 0, first.h = 0;
    myqueue.push(first);
    while(!myqueue.empty())
    {
        Node now = myqueue.top();   myqueue.pop();
        int pos = now.pos, gg = now.g, hh = now.h;
        times[pos]++;
        if(times[pos] == K && pos == T)   // 找到了
            return gg + hh;
        if(times[pos] > K)   // 不必要的搜索
            continue;

        for(int e = head[pos]; e != -1; e = edges[e].next)
        {
            int v = edges[e].v;
            int w = edges[e].w;

            second.pos = v;
            second.g = g[v];
            second.h = hh + w;
            myqueue.push(second);
        }
    }
    return -1;
}

int main()
{
    int u, v, w;
    while(scanf("%d %d", &n, &m) != EOF)
    {
        cnt = 0;
        recnt = 0;
        memset(head, -1, sizeof(head));
        memset(rehead, -1, sizeof(rehead));
        for(int i = 0; i < m; i++)
        {
            scanf("%d %d %d", &u, &v, &w);
            addEdge(u, v, w);
            addEdge2(v, u, w);
        }

        scanf("%d %d %d", &S, &T, &K);
        Dijkstra();
        if(S == T)  K++; // 当起点终点重合的时候， k需要加1
        printf("%d\n", Astar());
    }
}
