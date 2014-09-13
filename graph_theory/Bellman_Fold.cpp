/*********************************************************
最短路径  Bellman-Ford算法
适用条件&范围：
单源最短路径(从源点s到其它所有顶点v);
有向图&无向图(无向图可以看作(u,v),(v,u)同属于边集E的有向图);
边权可正可负(如有负权回路输出错误提示);
差分约束系统;
**********************************************************/
#define MAX 0x3f3f3f3f
#define N 1010
int nodenum, edgenum, original; //点，边，起点

typedef struct Edge //边
{
	int u, v;
	int cost;
}Edge;

Edge edge[N];
int dis[N], pre[N];

bool Bellman_Ford()
{
	for(int i = 1; i <= nodenum; ++i) //初始化
		dis[i] = (i == original ? 0 : MAX);
	for(int i = 1; i <= nodenum - 1; ++i)
		for(int j = 1; j <= edgenum; ++j)
			if(dis[edge[j].v] > dis[edge[j].u] + edge[j].cost) //松弛（顺序一定不能反~）
			{
				dis[edge[j].v] = dis[edge[j].u] + edge[j].cost;
				pre[edge[j].v] = edge[j].u;
			}
	bool flag = 1; //判断是否含有负权回路
	for(int i = 1; i <= edgenum; ++i)
		if(dis[edge[i].v] > dis[edge[i].u] + edge[i].cost)
		{
			flag = 0;
			break;
		}
	return flag;
}

void print_path(int root) //打印最短路的路径（反向）
{
	while(root != pre[root]) //前驱
	{
		printf("%d-->", root);
		root = pre[root];
	}
	if(root == pre[root])
	printf("%d\n", root);
}

int main()
{
	scanf("%d%d%d", &nodenum, &edgenum, &original);
	pre[original] = original;
	for(int i = 1; i <= edgenum; ++i)
	{
		scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].cost);
	}
	if(Bellman_Ford())
		for(int i = 1; i <= nodenum; ++i) //每个点最短路
		{
			printf("%d\n", dis[i]);
			printf("Path:");
			print_path(i);
		}
	else
		printf("have negative circle\n");
	return 0;
}
