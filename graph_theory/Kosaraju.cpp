/******************************************************
强连通 有向图 Kosaraju算法
这个算法的较为普遍的版本是：
1.对原图进行DFS并将出栈顺序进行逆序，得到的顺序就是拓扑顺序
2.将原图每条边进行反向
3.按照1中生成顺序再进行DFS染色染成同色的是一个强连通块
合理性：如果是强连通子图，那么反向没有任何影响，依然是强连通子图。
但如果是单向的边连通，反向后再按原序就无法访问了（因此反向处理是对非强连通块的过滤）
******************************************************/
#include <iostream>
using namespace std;
const int MAXV = 1024;
int g[MAXV][MAXV], dfn[MAXV], num[MAXV], n, m, scc, cnt;
void dfs(int k)
{
    num[k] = 1;
    for(int i=1; i<=n; i++)
        if(g[k][i] && !num[i])
            dfs(i);
    dfn[++cnt] = k;    //记录第cnt个出栈的顶点为k
}
void ndfs(int k)
{
    num[k] = scc;      //本次DFS染色的点，都属于同一个scc，用num数组做记录
    for(int i=1; i<=n; i++)
        if(g[i][k] && !num[i])          //注意我们访问的原矩阵的对称矩阵
            ndfs(i);
}
void kosaraju()
{
    int i, j;
    for(i=1; i<=n; i++)    //DFS求得拓扑排序
        if(!num[i])
            dfs(i);
    memset(num, 0, sizeof num);
    /*    我们本需对原图的边反向，但由于我们使用邻接矩阵储存图，所以反向的图的邻接矩阵
      即原图邻接矩阵的对角线对称矩阵，所以我们什么都不用做，只需访问对称矩阵即可*/
    for(i=n; i>=1; i--)
        if(!num[dfn[i]])   //按照拓扑序进行第二次DFS
        {
            scc++;
            ndfs(dfn[i]);
        }
    cout<<"Found: "<<scc<<endl;
}
int main()
{
    int i, j;
    cin>>n>>m;
    for(i=1; i<=m; i++)
    {
        int x, y, z;
        cin>>x>>y>>z;
        g[x][y] = z;
    }
    kosaraju();
    return 0;
}
