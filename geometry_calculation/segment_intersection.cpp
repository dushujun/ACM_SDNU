/**
** 计算几何 调整思想
** 把 n 个 黑色点坐标， 分别和 n 个白色点坐标连线，使得没有任何两条线交叉。
** 这题使用了计算几何里的调整思想，先假定了一种组合方式，然后判断是否相交，
** 相交的话，就把相交的两条直线端点互换，直至没有相交为止
** 这是用冒泡排序的思想进行的调整
**/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

int n;

struct Point
{
    double x, y;
    Point(double x = 0, double y = 0):x(x), y(y) {}
};

typedef Point Vector;

Vector operator - (Point A, Point B)
{
    return Vector(A.x-B.x, A.y-B.y);
}

Point trees[110], colony[110];
int match[110];

double Cross(Vector A, Vector B)
{
    return A.x*B.y - A.y*B.x;
}

double eps = 1e-6;
int dcmp(double x)
{
    if( fabs(x) < eps)
        return 0;
    return x < 0 ? -1 : 1;
}

bool segmentIntersection(Point a1, Point a2, Point b1, Point b2)
{
    double c1 = Cross(a2-a1, b1-a1), c2 = Cross(a2-a1, b2-a1);
    double c3 = Cross(b2-b1, a1-b1), c4 = Cross(b2-b1, a2-b1);
    return c1*c2 < 0 && c3*c4 < 0;
}

int main()
{
    while(scanf("%d", &n) != EOF)
    {
        for(int i = 1; i <= n; i++)
            scanf("%lf %lf", &colony[i].x, &colony[i].y);
        for(int i = 1; i <= n; i++)
            scanf("%lf %lf", &trees[i].x, &trees[i].y);

        for(int i = 1; i <= n; i++)
            match[i] = i;

        while(true)
        {
            bool flag = true;
            for(int i = 1; i <= n; i++)
            {
                for(int j = 1; j <= n; j++)
                {
                    if(i == j)
                        continue;
                    if(segmentIntersection(colony[i], trees[match[i]], colony[j], trees[match[j]]))
                    {
                        swap(match[i], match[j]);
                        flag = false;
                    }
                }
            }
            if(flag)
                break;
        }

        for(int i = 1; i <= n; i++)
            printf("%d\n", match[i]);
    }
    return 0;
}
