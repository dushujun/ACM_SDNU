/***********************************************
最小生成树  Prim算法的堆优化
朴素的Prim算法如果使用邻接矩阵来保存图的话，时间复杂度是O(N^2)，观察代码很容易发现，时间主要浪费在每次都要遍历所有点找一个最小距离的顶点，对于这个操作，我们很容易想到用堆来优化，使得每次可以在log级别的时间找到距离最小的点。下面的代码是一个使用二叉堆实现的堆优化Prim算法，代码使用邻接表来保存图。另外，需要说明的是，为了松弛操作的方便， 堆里面保存的顶点的标号，而不是到顶点的距离，所以我们还需要维护一个映射pos[x]表示顶点x在堆里面的位置。
使用二叉堆优化Prim算法的时间复杂度为O((V + E) log(V)) = O(E log(V))，对于稀疏图相对于朴素算法的优化是巨大的，然而100行左右的二叉堆优化Prim相对于40行左右的并查集优化Kruskal，无论是在效率上，还是编程复杂度上并不具备多大的优势。另外，我们还可以用更高级的堆来进一步优化时间界，比如使用斐波那契堆优化后的时间界为O(E + V log(V))，但编程复杂度也会变得更高。
***********************************************/
#include <iostream>
using namespace std;
const int MAXV = 10001, MAXE = 100001, INF = (~0u)>>2;
struct edge
{
    int t, w, next;
} es[MAXE * 2];
int h[MAXV], cnt, n, m, heap[MAXV], size, pos[MAXV], dist[MAXV];
void addedge(int x, int y, int z)
{
    es[++cnt].t = y;
    es[cnt].next = h[x];
    es[cnt].w = z;
    h[x] = cnt;
}

void heapup(int k)
{
    while(k > 1)
    {
        if(dist[heap[k>>1]] > dist[heap[k]])
        {
            swap(pos[heap[k>>1]], pos[heap[k]]);
            swap(heap[k>>1], heap[k]);
            k>>=1;
        }
        else
            break;
    }
}
void heapdown(int k)
{
    while((k<<1) <= size)
    {
        int j;
        if((k<<1) == size || dist[heap[(k<<1)]] < dist[heap[(k<<1)+1]])
            j = (k<<1);
        else
            j = (k<<1) + 1;
        if(dist[heap[k]] > dist[heap[j]])
        {
            swap(pos[heap[k]], pos[heap[j]]);
            swap(heap[k], heap[j]);
            k=j;
        }
        else
            break;
    }
}
void push(int v, int d)
{
    dist[v] = d;
    heap[++size] = v;
    pos[v] = size;
    heapup(size);
}
int pop()
{
    int ret = heap[1];
    swap(pos[heap[size]], pos[heap[1]]);
    swap(heap[size], heap[1]);
    size--;
    heapdown(1);
    return ret;
}

int prim()
{
    int mst = 0, i, p;
    push(1, 0);
    for(i=2; i<=n; i++)
        push(i, INF);
    for(i=1; i<=n; i++)
    {
        int t = pop();
        mst += dist[t];
        pos[t] = -1;
        for(p = h[t]; p; p = es[p].next)
        {
            int dst = es[p].t;
            if(pos[dst] != -1 && dist[dst] > es[p].w)
            {
                dist[dst] = es[p].w;
                heapup(pos[dst]);
                heapdown(pos[dst]);
            }
        }
    }
    return mst;
}
int main()
{
    cin>>n>>m;
    for(int i=1; i<=m; i++)
    {
        int x, y, z;
        cin>>x>>y>>z;
        addedge(x, y, z);
        addedge(y, x, z);
    }
    cout<<prim()<<endl;
    return 0;
}

