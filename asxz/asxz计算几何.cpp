template<class T>
struct Point {
    T x;
    T y;
    Point(T x_ = 0, T y_ = 0) : x(x_), y(y_) {}
    
    template<class U>
    operator Point<U>() {
        return Point<U>(U(x), U(y));
    }
    Point &operator+=(Point p) & {
        x += p.x;
        y += p.y;
        return *this;
    }
    Point &operator-=(Point p) & {
        x -= p.x;
        y -= p.y;
        return *this;
    }
    Point &operator*=(T v) & {
        x *= v;
        y *= v;
        return *this;
    }
    Point operator-() const {
        return Point(-x, -y);
    }
    friend Point operator+(Point a, Point b) {
        return a += b;
    }
    friend Point operator-(Point a, Point b) {
        return a -= b;
    }
    friend Point operator*(Point a, T b) {
        return a *= b;
    }
    friend Point operator*(T a, Point b) {
        return b *= a;
    }
    friend bool operator==(Point a, Point b) {
        return a.x == b.x && a.y == b.y;
    }
    friend std::istream &operator>>(std::istream &is, Point &p) {
        return is >> p.x >> p.y;
    }
    friend std::ostream &operator<<(std::ostream &os, Point p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

template<class T>
T dot(Point<T> a, Point<T> b) {
    return a.x * b.x + a.y * b.y;
}

template<class T>
T cross(Point<T> a, Point<T> b) {
    return a.x * b.y - a.y * b.x;
}

template<class T>
T square(Point<T> p) {
    return dot(p, p);
}

template<class T>
double length(Point<T> p) {
    return std::sqrt(double(square(p)));
}

long double length(Point<long double> p) {
    return std::sqrt(square(p));
}

template<class T>
double dist(Point<T> a, Point<T> b){
    return length(a-b);
}

template<class T>
Point<T> rotate(Point<T> a) {
    return Point(-a.y, a.x);
}

template<class T>
int quadrant(Point<T> a){
    if (a.y >= 0){
        if (a.x >= 0){
            return 1;
        }
        else{
            return 2;
        }
    }
    else{
        if (a.x<=0){
            return 3;
        }
        else{
            return 4;
        }
    }
}

template<class T>
void psort(std::vector<Point<T>> &p, Point<T> a=Point<T>()){
    auto cmp=[&](Point<T> &fir, Point<T> &sec)->void{
        auto fp=fir-a;
        auto sp=sec-a;
        if (quadrant(fp)==quadrant(sp)){
            auto c=cross(fp, sp);
            if (c==0){
                return square(fp)<square(sp);
            }
            else{
                return c<0;
            }
        }
        else{
            return quadrant(fp)<quadrant(sp);
        }
    };

    std::sort(p.begin(), p.end(), cmp);
}

template<class T>
struct Line {
    Point<T> a;
    Point<T> b;
    Line(Point<T> a_ = Point<T>(), Point<T> b_ = Point<T>()) : a(a_), b(b_) {}
};

template<class T>
bool pointOnLineLeft(Point<T> p, Line<T> l) {
    return cross(l.b - l.a, p - l.a) > 0;
}

template<class T>
bool pointOnLineRight(Point<T> p, Line<T> l) {
    return cross(l.b - l.a, p - l.a) < 0;
}


template<class T>
bool pointOnSegment(Point<T> p, Line<T> l) {
    return cross(p - l.a, l.b - l.a) == 0 && std::min(l.a.x, l.b.x) <= p.x && p.x <= std::max(l.a.x, l.b.x)
        && std::min(l.a.y, l.b.y) <= p.y && p.y <= std::max(l.a.y, l.b.y);
}

template<class T>
double disPointLine(Point<T> p, Line<T> l){
    return double(std::abs(cross(p-l.a, l.b-l.a)))/dist(l.a, l.b);
}

template<class T>
Point<T> pointLineProj(Point<T> p, Line<T> l){
    T k=dot(p-l.a, l.b-l.a)/square(l.b-l.a);
    return l.a+k*(l.b-l.a);
}

template<class T>
Point<T> pointLineSymmetry(Point<T> p, Line<T> l){
    auto pp=pointLineProj(p, l);
    return p+2*(pp-p);
}

template<class T>
double disPointSegment(Point<T> p, Line<T> l){
    auto pp=pointLineProj(p, l);
    if (pointOnSegment(pp, l)){
        return disPointLine(p, l);
    }
    else{
        return std::min(dist(p, l.a), dist(p, l.b));
    }
}

template<class T>
Point<T> lineIntersection(Line<T> l1, Line<T> l2) {
    return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b));
}


// 0 : not intersect
// 1 : strictly intersect
// 2 : overlap
// 3 : intersect at endpoint
template<class T>
std::tuple<int, Point<T>, Point<T>> segmentIntersection(Line<T> l1, Line<T> l2) {
    if (std::max(l1.a.x, l1.b.x) < std::min(l2.a.x, l2.b.x)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::min(l1.a.x, l1.b.x) > std::max(l2.a.x, l2.b.x)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::max(l1.a.y, l1.b.y) < std::min(l2.a.y, l2.b.y)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::min(l1.a.y, l1.b.y) > std::max(l2.a.y, l2.b.y)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (cross(l1.b - l1.a, l2.b - l2.a) == 0) {
        if (cross(l1.b - l1.a, l2.a - l1.a) != 0) {
            return {0, Point<T>(), Point<T>()};
        } else {
            auto maxx1 = std::max(l1.a.x, l1.b.x);
            auto minx1 = std::min(l1.a.x, l1.b.x);
            auto maxy1 = std::max(l1.a.y, l1.b.y);
            auto miny1 = std::min(l1.a.y, l1.b.y);
            auto maxx2 = std::max(l2.a.x, l2.b.x);
            auto minx2 = std::min(l2.a.x, l2.b.x);
            auto maxy2 = std::max(l2.a.y, l2.b.y);
            auto miny2 = std::min(l2.a.y, l2.b.y);
            Point<T> p1(std::max(minx1, minx2), std::max(miny1, miny2));
            Point<T> p2(std::min(maxx1, maxx2), std::min(maxy1, maxy2));
            if (!pointOnSegment(p1, l1)) {
                std::swap(p1.y, p2.y);
            }
            if (p1 == p2) {
                return {3, p1, p2};
            } else {
                return {2, p1, p2};
            }
        }
    }
    auto cp1 = cross(l2.a - l1.a, l2.b - l1.a);
    auto cp2 = cross(l2.a - l1.b, l2.b - l1.b);
    auto cp3 = cross(l1.a - l2.a, l1.b - l2.a);
    auto cp4 = cross(l1.a - l2.b, l1.b - l2.b);
    
    if ((cp1 > 0 && cp2 > 0) || (cp1 < 0 && cp2 < 0) || (cp3 > 0 && cp4 > 0) || (cp3 < 0 && cp4 < 0)) {
        return {0, Point<T>(), Point<T>()};
    }
    
    Point p = lineIntersection(l1, l2);
    if (cp1 != 0 && cp2 != 0 && cp3 != 0 && cp4 != 0) {
        return {1, p, p};
    } else {
        return {3, p, p};
    }
}

template<class T>
bool pointInPolygon(Point<T> a, std::vector<Point<T>> p) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
        if (pointOnSegment(a, Line(p[i], p[(i + 1) % n]))) {
            return true;
        }
    }
    
    int t = 0;
    for (int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        if (u.x < a.x && v.x >= a.x && pointOnLineLeft(a, Line(v, u))) {
            t ^= 1;
        }
        if (u.x >= a.x && v.x < a.x && pointOnLineLeft(a, Line(u, v))) {
            t ^= 1;
        }
    }
    
    return t == 1;
}

template<class T>
T areaPolygon(std::vector<Point<T>> p){
    T res=0;
    int n=p.size();
    for (int i=0; i<n; i++){
        res+=cross(p[i], p[(i+1)%n]);
    }
    return res/2;
}

template<class T>
Point<T> centerPolygon(std::vector<Point<T>> p){
    int n=p.size();
    Point<T> res;
    T area=areaPolygon(p);
    if (area==T(0)){
        return res;
    }
    for (int i=0; i<n; i++){
        res+=(p[i]+p[(i+1)%n])*cross(p[i], p[(i+1)%n]);
    }
    res/=area;
    res/=T(6);
    return res;
}

template<class T>
std::vector<Point<T>> convex(std::vector<Point<T>> p){
    p.erase(std::unique(p.begin(), p.end()), p.end());
    std::sort(p.begin(), p.end(), [&](auto p1, auto p2){
        if (p1.x!=p2.x){
            return p1.x<p2.x;
        }
        else{
            return p1.y<p2.y;
        }
    });

    int n=p.size();
    std::vector<Point<T>> res;
    res.reserve(n);
    int lim=1;
    for (int i=0; i<n; i++){
        while (res.size()>lim && !pointOnLineLeft(p[i], Line(res[res.size()-2], res[res.size()-1]))){
            res.pop_back();
        }
        res.push_back(p[i]);
    }

    lim=res.size();
    for (int i=n-2; i>=0; i--){
        while (res.size()>lim && !pointOnLineLeft(p[i], Line(res[res.size()-2], res[res.size()-1]))){
            res.pop_back();
        }
        res.push_back(p[i]);
    }

    if (n>1){
        res.pop_back();
    }

    return res;
}

template<class T>
T RC(std::vector<Point<T>> p){
    int n=p.size();
    if (n<2){
      return T(0);
    }
    if (n==2){
        return square(p[1]-p[0]);
    }
    int cur=0;
    T res=0;
    for (int i=0; i<n; i++){
        Line l(p[i], p[(i+1)%n]);
        while (disPointLine(p[cur], l)<=disPointLine(p[(cur+1)%n], l)){
            cur=(cur+1)%n;
        }
        res=std::max({res, square(p[i]-p[cur]), square(p[(i+1)%n]-p[cur])});
    }
    return res;
}

template<class T>
struct Circle
{
    Point<T> c;
    T r;
    Circle(Point<T> c_=Point<T>(), T r_=T()):c(c_), r(r_){}
};

//0 在圆内
//1 在圆上
//2 在圆外
template<class T>
int pointInCircle(Point<T> p, Circle<T> cir){
    T r=cir.r*cir.r;
    T dis=square(p-cir.c);
    if (dis<r){
        return 0;
    }
    else if (dis==r){
        return 1;
    }
    else{
        return 2;
    }
}
