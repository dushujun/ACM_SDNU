/**
** 后缀数组
** 给出n个字符串，求出一个最长的串，使得这个串或者这个串的回文在所有n个字符串中都出现。
** 把每个字符串拆为两个串，分别是原字符串和原字符串的回文串，把他们连接起来，中间插入分隔符。
** 再将每个这样的结构都连接起来，中间同样插入分隔符。再转化为二分+判定即可。要熟知height sa数组的定义。
**/

#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int nMax = 200001;

int  num[nMax];
int sa[nMax], rank[nMax], height[nMax];
int wa[nMax], wb[nMax], wv[nMax], wd[nMax];

int cmp(int *r, int a, int b, int l){
    return r[a] == r[b] && r[a+l] == r[b+l];
}

void da(int *r, int n, int m){          //  倍增算法 r为待匹配数组  n为总长度 m为字符范围
    int i, j, p, *x = wa, *y = wb, *t;
    for(i = 0; i < m; i ++) wd[i] = 0;
    for(i = 0; i < n; i ++) wd[x[i]=r[i]] ++;
    for(i = 1; i < m; i ++) wd[i] += wd[i-1];
    for(i = n-1; i >= 0; i --) sa[-- wd[x[i]]] = i;
    for(j = 1, p = 1; p < n; j *= 2, m = p){
        for(p = 0, i = n-j; i < n; i ++) y[p ++] = i;
        for(i = 0; i < n; i ++) if(sa[i] >= j) y[p ++] = sa[i] - j;
        for(i = 0; i < n; i ++) wv[i] = x[y[i]];
        for(i = 0; i < m; i ++) wd[i] = 0;
        for(i = 0; i < n; i ++) wd[wv[i]] ++;
        for(i = 1; i < m; i ++) wd[i] += wd[i-1];
        for(i = n-1; i >= 0; i --) sa[-- wd[wv[i]]] = y[i];
        for(t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i ++){
            x[sa[i]] = cmp(y, sa[i-1], sa[i], j) ? p - 1: p ++;
        }
    }
}

void calHeight(int *r, int n){           //  求height数组。
    int i, j, k = 0;
    for(i = 1; i <= n; i ++) rank[sa[i]] = i;
    for(i = 0; i < n; height[rank[i ++]] = k){
        for(k ? k -- : 0, j = sa[rank[i]-1]; r[i+k] == r[j+k]; k ++);
    }
}

int loc[nMax],m;
char str[nMax],res[nMax];
bool vis[1004];

bool check(int mid,int len){
    int i,j,tot;
    tot=0;
    memset(vis,0,sizeof(vis));
    for(i=2;i<=len;i++){
        if(height[i]<mid){
            memset(vis,0,sizeof(vis));
            tot=0;
        }
        else{
            if(!vis[loc[sa[i-1]]]){
                vis[loc[sa[i-1]]]=1;
                tot++;
            }
            if(!vis[loc[sa[i]]]){
                vis[loc[sa[i]]]=1;
                tot++;
            }
            if(tot==m){
                for(j=0;j<mid;j++){
                    res[j]=num[sa[i]+j];
                }res[mid]='\0';
                return 1;
            }
        }
    }
    return 0;
}

int main(){
    int n,k,i,j,a,b,sp,ans,cas,sl;
    scanf("%d",&cas);
    while(scanf("%d",&m)!=EOF){
        sp=140;    //分隔符
        n=0;
        ans=0;
        for(i=1;i<=m;i++){
            scanf("%s",str);
            sl=strlen(str);
            for(j=0;str[j];j++){
                loc[n]=i;
                num[n++]=str[j];
            }
            loc[n]=sp;
            num[n++]=sp++;
            for(j=0;str[j];j++){
                loc[n]=i;
                num[n++]=str[sl-j-1];
            }
            loc[n]=sp;
            num[n++]=sp++;
        }
     //   for(i=0;i<=n;i++)cout<<loc[i]<<" ";cout<<endl;
        num[n]=0;
        da(num, n + 1, sp);
        calHeight(num,n);
        int left=0,right=strlen(str),mid;//开始二分
        while(right>=left){
            mid=(right+left)/2;
            if(check(mid,n)){         //判断长度为mid的串是否是所有字符串的公共子串
                left=mid+1;
                ans=mid;
            }
            else{
                right=mid-1;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
