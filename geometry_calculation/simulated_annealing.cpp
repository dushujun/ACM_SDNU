// 多边形费马点 模拟退火(simulated annealing)
// 要求在多边形内选一个点，使得此点到所有顶点的距离和最小。 也就是多边形的费马点
// 使用随机化变步长贪心法（模拟退火算法）解决。 可以算是 模拟退火的模板题了。
// 任意选一个步长然后往 四个方向走，如果更优的话就继续走，否则减小步长。直到满足题目要求的精度

struct Point
{
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
}points[110];

int n;
double step;

int dir[4][2] = {1,0, 0,1, 0,-1, -1,0};

double dis(Point A, Point B)
{
    return sqrt((A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y));
}

double disAll(Point center)
{
    double sum = 0;
    for(int i = 0; i < n; i++)
    {
        sum += dis(points[i], center);
    }
    return sum;
}

int main()
{
    while(scanf("%d", &n) != EOF)
    {
        for(int i = 0; i < n; i++)
        {
            scanf("%lf %lf", &points[i].x, &points[i].y);
        }
        step = 100;     // 步长选的是100！！！

        double bestDis = disAll(Point());
        Point now = Point(0, 0);
        // 如果更优就进一步，否则减小步长
        while(step > 0.2)  // 此时再减小步长对精度下的最小值没影响了
        {
            bool ok = true;
            while(ok)
            {
                ok = false;
                Point temp;
                for(int i = 0; i < 4; i++)
                {
                    // 此处原先是用的 temp.x += dir[i][0]*temp WA了两次
                    temp.x = dir[i][0]*step + now.x;
                    temp.y = dir[i][1]*step + now.y;
                    double tempDis = disAll(temp);
                    if(tempDis < bestDis)
                    {
                        now = temp;
                        bestDis = tempDis;
                        ok = true;
                    }
                }
            }
            step /= 2.0;
        }
        printf("%d\n", (int)(bestDis+0.5));
    }
    return 0;
}
