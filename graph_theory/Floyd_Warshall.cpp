/*******************************************************
最短路径  Floyd-Warshall算法
通常可以在任何图中使用，包括有向图、带负权边的图。
********************************************************/
for(int k=1;k<=n;k++)
 for(int i=1;i<=n;i++)
  for(int j=1;j<=n;j++){
   if( map[i][k] != maxint && map[k][j] != maxint )
    if( map[i][k] + map[k][j] < map[i][j] )
     map[i][j] = map[i][k] + map[k][j];
  }
