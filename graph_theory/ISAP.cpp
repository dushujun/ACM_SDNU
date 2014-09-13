/********************************************************
最大流 ISAP算法
********************************************************/
const int INF = 0x6fffffff ;   //权值上限
const int MAXPT = 300 ;           //顶点数上限
const int MAXEG = MAXPT*MAXPT*2 ; //边数上限
const int MAXQUE = MAXPT*2 ;           // 队列长度

/*
    s = 1 ; // 源点
    t = n ; // 汇点
*/
class MNF_SAP
{
private:

    //int m,n;
    int s,t;
    int dis[MAXPT];   //距离标号
    int pre[MAXPT];   //前置顶点
    int flow[MAXPT];  //到当前点为止，所有弧的最小值
    int curedge[MAXPT];   //当前弧cur
    int cnt[MAXPT];   //k标号出现次数
    int queue[MAXQUE],front,rear;
    bool vis[MAXPT];

    void BFS ()
    {
        int i,u;
        memset(vis,false,sizeof(vis));
        front=rear=0;
        dis[t]=0;
        vis[t]=true;
        queue[++rear]=t;
        while (front!=rear)
        {
            u=queue[(++front)%MAXQUE];
            for (i=head[u];i!=0;i=edges[i].next)
                if (vis[edges[i].v]==false && !edges[i].cap)
                {
                    dis[edges[i].v]=dis[u]+1;
                    vis[edges[i].v]=true;
                    queue[(++rear)%MAXQUE]=edges[i].v;
                }
        }
          for (i=1;i<=n;i++)
               cnt[dis[i]]++;
    }
public:

    struct Node
    {
        int v,cap,next;
          Node(){}
          Node (int _v,int _cap,int _next)
          {
               v=_v;
               cap=_cap;
               next=_next;
          }
    }edges[MAXEG];
    int n;      //总节点数
     int e;
    int head[MAXPT];
//    MNF_SAP(){}
//    ~MNF_SAP(){}

     void init (int temp)
     {
          n=temp;
          e=2;
          memset (head,0,sizeof(head));
     }

     void Add (int u,int v,int cap)   //始,终,量
     {
          edges[e]=Node(v,cap,head[u]);
          head[u]=e++;
          edges[e]=Node(u,0,head[v]);
          head[v]=e++;
     }

    int SAP ()
    {
        int u,v,i,maxflow=0;   //总最大流
        s=1;
        t=n;
        u=s;
        flow[s]=INF;
        for (i=1;i<=n;i++)
               curedge[i]=head[i];     //当前弧初始化
        BFS ();
        cnt[0]=n;
        while (dis[s]<n)
        {
            for (i=curedge[u];i!=0;i=edges[i].next)        //找允许弧
                if (edges[i].cap && dis[edges[i].v]+1==dis[u])
                         break;
            if (i!=0)      //存在允许弧
            {
                curedge[u]=i;         //设置当前弧
                v=edges[i].v;
                if (edges[i].cap<flow[u])
                         flow[v]=edges[i].cap;
                else
                         flow[v]=flow[u];  //标记当前顶点为止经过的最小弧
                u=v;
                pre[v]=i;  //前置顶点边号
                if (u==t)
                {
                    do
                    {
                        edges[pre[u]].cap-=flow[t];          //正向弧减a[t]
                        edges[pre[u]^1].cap+=flow[t];        //通过异或操作找反向弧
                        u=edges[pre[u]^1].v;
                    }
                    while (u!=s);
                    maxflow+=flow[t];
                    //memset(flow,0,sizeof(flow));
                    flow[s]=INF;
                }
            }
            else   //不存在允许弧
            {
                if (--cnt[dis[u]]==0)
                         break;     //间隙优化
                dis[u]=n;
                curedge[u]=head[u];
                for (i=head[u];i!=0;i=edges[i].next)
                    if (edges[i].cap && dis[edges[i].v]+1<dis[u])
                        dis[u]=dis[edges[i].v]+1;       //修改距离标号为 最小的非允许弧加1
                cnt[dis[u]]++;
                if (u!=s)
                         u=edges[pre[u]^1].v;
            }
        }
        return maxflow;
    }
};

MNF_SAP ob;

int main ()
{
    int n,m;
    int x,y,z;
    while (~scanf("%d%d",&n,&m))
    {
          ob.init(m);
        for (int i=0;i<n;i++)
        {
            scanf("%d%d%d",&x,&y,&z);
               ob.Add(x,y,z);
        }
          printf("%d\n",ob.SAP());
    }
    return 0;
}
