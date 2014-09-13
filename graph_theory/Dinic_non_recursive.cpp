/***************************************************
最大流 Dinic算法 非递归实现
一般来说不必如此，如果效率要求很高，可以使用后面的ISAP算法
***************************************************/
void Dinic()
{
    for(;;){
        BFS();
        if(D[T]==-1)break;
        int path_n=0;
        int x=S;
        memcpy(cur,E,sizeof(cur));
        for(;;){
            if(x==T){
                int mink=-1,delta=INT_MAX;
                for(int i=0;i<path_n;++i){
                    if(path[i]->c<delta){
                        delta=path[i]->c;
                        mink=i;
                    }
                }
                for(int i=0;i<path_n;++i){
                    path[i]->c-=delta;
                    path[i]->back->c+=delta;
                }
                path_n=mink;
                x=path[path_n]->x;
            }
            edge* e;
            for(e=cur[x];e;e=e->next){
                if(e->c==0)
                    continue;
                int y=e->y;
                if(D[x]+1==D[y])
                    break;
            }
            cur[x]=e;
            if(e){
                path[path_n++]=e;
                x=e->y;
            }
            else{
                if(path_n==0)
                    break;
                D[x]=-1;
                --path_n;
                x=path[path_n]->x;
            }
        }
    }
}
