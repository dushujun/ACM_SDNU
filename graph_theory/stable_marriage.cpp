/**************************************************************************
稳定婚姻
在这种策略中，男孩儿将一轮一轮地去追求他中意的女子，女子可以选择接受或者拒绝他的追求者。
**************************************************************************/
#define N 30
#define inf 1<<29
#define MOD 2007
#define LL long long
using namespace std;
int couple;                  //总共多少对
int malelike[N][N],femalelike[N][N];   //男士对女士的喜欢程度，按降序排列，女士对男士的喜欢程度一一对应
int malechoice[N],femalechoice[N];   //男士的选择，女士的选择
int malename[N],femalename[N];   //name的HASH
char str[N];
queue<int>freemale;   //没有配对的男士
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&couple);
        //清空队列
        while(!freemale.empty())
            freemale.pop();
        //将男士的名字存下，初始都没有配对
        for(int i=0;i<couple;i++){
            scanf("%s",str);
            malename[i]=str[0]-'a';
            freemale.push(malename[i]);
        }
        //将名字排序，便于字典序
        sort(malename,malename+couple);
        for(int i=0;i<couple;i++){
            scanf("%s",str);
            femalename[i]=str[0]-'A';
        }
        //男士对女士的印象，按降序排列
        for(int i=0;i<couple;i++){
            scanf("%s",str);
            for(int j=0;j<couple;j++)
                malelike[i][j]=str[j+2]-'A';
        }
        //女士对男士的打分，添加虚拟人物，编号couple,为女士的初始对象，
        for(int i=0;i<couple;i++){
            scanf("%s",str);
            for(int j=0;j<couple;j++)
                femalelike[i][str[j+2]-'a']=couple-j;
            femalelike[i][couple]=0;
        }
        //一开始男士的期望都是最喜欢的女士
        memset(malechoice,0,sizeof(malechoice));
        //女士先初始一个对象
        for(int i=0;i<couple;i++)
            femalechoice[i]=couple;
        while(!freemale.empty()){
            //找出一个未配对的男士，注意不要习惯性的POP
            int male=freemale.front();
            //男士心仪的女士
            int female=malelike[male][malechoice[male]];
            //如果当前男士比原来的男友更好
            if(femalelike[female][male]>femalelike[female][femalechoice[female]]){
                //成功脱光
                freemale.pop();
                //如果有前男友，则打回光棍，并且考虑下一个对象
                //不要把虚拟的人物加入队列，否则就死循环或者错误
                if(femalechoice[female]!=couple){
                    freemale.push(femalechoice[female]);
                    malechoice[femalechoice[female]]++;
                }
                //当前男友为这位男士
                femalechoice[female]=male;
            }
            else
            //如果被女士拒绝，则要考虑下一个对象
                malechoice[male]++;
        }
        for(int i=0;i<couple;i++)
            printf("%c %c\n",malename[i]+'a',malelike[malename[i]][malechoice[malename[i]]]+'A');
        if(t) puts("");
    }
    return 0;
}
