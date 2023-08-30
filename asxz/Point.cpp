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
T dist(Point<T> a, Point<T> b){
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
void psort(Point<T> a, std::vector<Point<T>> &p){
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
