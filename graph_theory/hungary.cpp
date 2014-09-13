/*************************************************************
二分图匹配 匈牙利算法
*************************************************************/
int grid[N][N];
int mat[N], n, k;
bool used[N];

bool dfs(int u)
{
    for(int i = 1; i <= n; i++)
    {
        if(grid[u][i] && !used[i])
        {
            used[i] = 1;
            if(mat[i] == -1 || dfs(mat[i]) )
            {
                mat[i] = u;
                return true;
            }
        }
    }
    return false;
}

int hungary()
{
    int match = 0;
    memset(mat, -1, sizeof(mat));
    for(int i = 1; i <= n; i++)
    {
        memset(used, 0, sizeof(used));
        if(dfs(i))
            match++;
    }
    return match;
}
