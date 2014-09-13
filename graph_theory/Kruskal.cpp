/**************************************
克鲁斯卡尔（Kruskal）算法因为只与边相关，适合求稀疏图的最小生成树。
算法过程：
1.将图各边按照权值进行排序
2.将图遍历一次，找出权值最小的边，（条件：此次找出的边不能和已加入最小生成树集合的边构成环），若符合条件，则加入最小生成树的集合中。不符合条件则继续遍历图，寻找下一个最小权值的边。
3.递归重复步骤1，直到找出n-1条边为止（设图有n个结点，则最小生成树的边数应为n-1条），算法结束。得到的就是此图的最小生成树。
**************************************/
#define MAX 1000
int father[MAX], son[MAX];
int v, l;

typedef struct Kruskal //存储边的信息
{
     int a;
     int b;
     int value;
};

bool cmp(const Kruskal & a, const Kruskal & b)
{
     return a.value < b.value;
}

int unionsearch(int x) //查找根结点+路径压缩
{
     return x == father[x] ? x : unionsearch(father[x]);
}

bool join(int x, int y) //合并
{
     int root1, root2;
     root1 = unionsearch(x);
     root2 = unionsearch(y);
     if(root1 == root2) //为环
          return false;
     else if(son[root1] >= son[root2])
          {
               father[root2] = root1;
               son[root1] += son[root2];
          }
          else
          {
               father[root1] = root2;
               son[root2] += son[root1];
          }
     return true;
}

int main()
{
     int ncase, ltotal, sum, flag;
     Kruskal edge[MAX];
     scanf("%d", &ncase);
     while(ncase--)
     {
          scanf("%d%d", &v, &l);
          ltotal = 0, sum = 0, flag = 0;
          for(int i = 1; i <= v; ++i) //初始化
          {
               father[i] = i;
               son[i] = 1;
          }
          for(int i = 1; i <= l ; ++i)
          {
               scanf("%d%d%d", &edge[i].a, &edge[i].b, &edge[i].value);
          }
          sort(edge + 1, edge + 1 + l, cmp); //按权值由小到大排序
          for(int i = 1; i <= l; ++i)
          {
               if(join(edge[i].a, edge[i].b))
               {
                    ltotal++; //边数加1
                    sum += edge[i].value; //记录权值之和
                    cout<<edge[i].a<<"->"<<edge[i].b<<endl;
               }
               if(ltotal == v - 1) //最小生成树条件：边数=顶点数-1
               {
                    flag = 1;
                    break;
               }
          }
          if(flag) printf("%d\n", sum);
          else printf("data error.\n");
     }
     return 0;
}
