template<class Info>
struct SegmentTree {
    int n;
    std::vector<Info> info;
    SegmentTree() : n(0) {}
    SegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    SegmentTree(std::vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        n_ += 1;
        init(std::vector(n_, v_));
    }
    template<class T>
    void init(std::vector<T> init_) {
        n = init_.size();
        info.assign(4 << std::__lg(n), Info());
        n -= 1;
        std::function<void(int, int, int)> build = [&](int p, int pl, int pr) {
            if (pl == pr) {
                info[p] = init_[pl];
                return;
            }
            int m = (pl + pr) / 2;
            build(2 * p, pl, m);
            build(2 * p + 1, m+1, pr);
            pull(p);
        };
        build(1, 1, n);
    }
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void modify(int p, int pl, int pr, int x, const Info &v) {
        if (pl == pr) {
            info[p] = v;
            return;
        }
        int m = (pl + pr) / 2;
        if (x <= m) {
            modify(2 * p, pl, m, x, v);
        } else {
            modify(2 * p + 1, m+1, pr, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) {
        modify(1, 1, n, p, v);
    }
    Info rangeQuery(int p, int pl, int pr, int l, int r) {
        if (pl > r || pr < l) {
            return Info();
        }
        if (pl >= l && pr <= r) {
            return info[p];
        }
        int m = (pl + pr) / 2;
        return rangeQuery(2 * p, pl, m, l, r) + rangeQuery(2 * p + 1, m+1, pr, l, r);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 1, n, l, r);
    }
    template<class F>
    int findFirst(int p, int pl, int pr, int l, int r, F pred) {
        if (pl > r || pr < l || !pred(info[p])) {
            return -1;
        }
        if (pl == pr) {
            return pl;
        }
        int m = (pl + pr) / 2;
        int res = findFirst(2 * p, pl, m, l, r, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m+1, pr, l, r, pred);
        }
        return res;
    }
    template<class F>
    int findFirst(int l, int r, F pred) {
        return findFirst(1, 1, n, l, r, pred);
    }
    template<class F>
    int findLast(int p, int pl, int pr, int l, int r, F pred) {
        if (pl > r || pr < l || !pred(info[p])) {
            return -1;
        }
        if (pl == pr) {
            return pl;
        }
        int m = (pl + pr) / 2;
        int res = findLast(2 * p + 1, m+1, pr, l, r, pred);
        if (res == -1) {
            res = findLast(2 * p, pl, m, l, r, pred);
        }
        return res;
    }
    template<class F>
    int findLast(int l, int r, F pred) {
        return findLast(1, 1, n, l, r, pred);
    }
};
