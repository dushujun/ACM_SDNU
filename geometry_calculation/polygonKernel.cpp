//半平面交 多边形核
struct Point
{
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
};

typedef Point Vector;
Vector operator - (Point A, Point B)
{
    return Vector(A.x-B.x, A.y-B.y);
}
Vector operator + (Vector A, Vector B)
{
    return Vector(A.x+B.x, A.y+B.y);
}

Vector operator * (Vector A, double p)
{
    return Vector(A.x*p, A.y*p);
}

struct Polygon
{
    Point p[110];
    int size;
};

struct Line
{
    Point first, second;
    Line(Point a = Point(), Point b = Point())
    {
        first = a;
        second = b;
    }
};

double Dot(Vector A, Vector B)
{
    return A.x*B.x + A.y*B.y;
}

double Cross(Vector A, Vector B)
{
    return A.x*B.y - A.y*B.x;
}

Point GetLineIntersection(Point P, Vector v, Point Q, Vector w)
{
    Vector u = P - Q;
    double t = Cross(w, u) / Cross(v, w);
    return P + v * t;
}

Polygon halfPlaneIntersection(Polygon& poly, Line& ln)
{
    int m = 0;
    Polygon hull;
    Point p1 = ln.first, p2 = ln.second;

    for(int i = 0; i < poly.size; i++)
    {
        double c = Cross(p2 - p1, poly.p[i] - p1);
        double d = Cross(p2 - p1, poly.p[(i+1)%poly.size] - p1);
        if( c >= 0)
            hull.p[m++] = poly.p[i];
        if(c*d < 0)
        {
            hull.p[m++] = GetLineIntersection(p1, p2 - p1, poly.p[i], poly.p[(i+1) % poly.size] - poly.p[i]);
        }
    }

    hull.size = m;
    return hull;
}

bool polygonKernel(Polygon& poly, Polygon& knl)
{
    knl.p[0] = Point(-INF, -INF);
    knl.p[1] = Point(INF, -INF);
    knl.p[2] = Point(INF, INF);
    knl.p[3] = Point(-INF, INF);
    knl.size = 4;
    Line ln;
    for(int i = 1; i <= poly.size; i++)
    {
        ln.first = poly.p[ i % poly.size];
        ln.second = poly.p[i-1];
        knl = halfPlaneIntersection(knl, ln);
        if(knl.size == 0)
            return false;
    }
    return true;
}

int main()
{
    int t, n;
    Polygon poly, knl;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
        {
            scanf("%lf%lf", &poly.p[i].x, &poly.p[i].y);
        }
        poly.size = n;
        if(polygonKernel(poly, knl))
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
