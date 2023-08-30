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
    std::vector<Point<T>> res(n);
    int cnt=0;
    int lim=1;
    for (int i=0; i<n; i++){
        while (cnt>lim && !pointOnLineLeft(p[i], Line(res[cnt-2], res[cnt-1]))){
            cnt--;
        }
        res[cnt++]=p[i];
    }

    lim=cnt;
    for (int i=n-2; i>=0; i--){
        while (cnt>lim && !pointOnLineLeft(p[i], Line(res[cnt-2], res[cnt-1]))){
            cnt--;
        }
        res[cnt++]=p[i];
    }

    if (n>1){
        cnt--;
    }

    return std::vector(res.begin(), res.begin()+cnt);
}
