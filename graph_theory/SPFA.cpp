/**********************************************************
最短路径  SPFA算法(Bellman-Ford算法的一种队列实现) 
每次迭代，取出队头的点v，依次枚举从v出发的边v->u，设边的长度为len，判断Dist[v]+len是否小于Dist[u]，若小于则改进Dist[u]，将Fa[u]记为v，并且由于S到u的最短距离变小了，有可能u可以改进其它的点，所以若u不在队列中，就将它放入队尾。这样一直迭代下去直到队列变空，也就是S到所有的最短距离都确定下来，结束算法。若一个点入队次数超过n，则有负权环。
**********************************************************/
int SPFA()
{
    queue<int> Q;
    memset(inqueue, 0, sizeof(inqueue));
    memset(times, 0, sizeof(times));
    for(int i = 1; i <= n; i++)
        dis[i] = INF;
    dis[1] = 0;
    inqueue[1] = true;
    times[1]++;
    Q.push(1);
    while(!Q.empty())
    {
        int u = Q.front();  Q.pop();
        inqueue[u] = false;
        for(int e = head[u]; e != -1; e = edges[e].next)
        {
            int v = edges[e].v;
            int w = edges[e].w;
            if(dis[u] + w < dis[v])
            {
                dis[v] = dis[u] + w;
                if(!inqueue[v])
                {
                    Q.push(v);
                    inqueue[v] = true;
                }
                times[v]++;
                if(times[v] >= n)  // 松弛过大于等于 n 次就可判定有负环
                        return -1;   // 这时说明不存在这样的情况

            }
        }
    }
    return dis[n];
}
