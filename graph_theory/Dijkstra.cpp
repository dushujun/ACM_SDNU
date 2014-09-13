/**************************************************************
最短路径  Dijkstra算法
其基本原理是：每次新扩展一个距离最短的点，更新与其相邻的点的距离。当所有边权都为正时，由于不会存在一个距离更短的没扩展过的点，所以这个点的距离永远不会再被改变，因而保证了算法的正确性。不过根据这个原理，用Dijkstra求最短路的图不能有负权边，因为扩展到负权边的时候会产生更短的距离，有可能就破坏了已经更新的点距离不会改变的性质。
**************************************************************/
int Dijstra()
{
    for(int i = 1; i <= n; i++)
        dis[i] = INF, vis[i] = 0;
    dis[1] = 0;
    for(int i = 1; i <= n; i++)
    {
        int mindis = INF, k;
        for(int i = 1; i <= n; i++)
            if(!vis[i] && mindis > dis[i])
                mindis = dis[i], k = i;
        if(mindis == INF)
            break;
        vis[k] = 1;
        for(int e =head[k]; e != -1; e = edges[e].next)
        {
            int v = edges[e].v;
            int w = edges[e].w;
            if(!vis[v] && dis[v] > dis[k] + w)
                dis[v] = dis[k] + w;
        }
    }
    return dis[n];
}
