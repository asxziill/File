struct DLX
{
    struct P
    {
        P *L, *R, *U, *D;
        int x, y;
    };

    #define TR(i, D, s) for (P* i=s->D; i!=s; i=i->D)
    static const int INF=1e9;
    static const int M=2e5;
    P pool[M], *h[M], *r[M], *pit;
    int sz[M];
    bool solved;
    std::stack<int> ans;

    DLX(int n=0, int m=0){
        init(n, m);
    }

    void init(int n, int m){
        pit=pool;
        ++n;
        ++m;
        solved=false;
        while (!ans.empty()) ans.pop();
        memset(r, 0, sizeof r);
        for (int i=0; i<n; i++){
            r[i]=0;
        }
        for (int i=0; i<m; i++){
            sz[i]=0;
        }
        for (int i=0; i<m; i++){
            h[i] = new (pit++) P;
        }
        for (int i=0; i<m; i++){
            h[i]->L=h[(i+m-1)%m];
            h[i]->R=h[(i+1)%m];
            h[i]->U=h[i]->D=h[i];
            h[i]->y=i;
        }
    }

    void insert(int x, int y){
        sz[y]++;
        auto p=new (pit++) P;
        p->x=x; p->y=y;
        p->U=h[y]->U; p->D=h[y];
        p->D->U=p->U->D=p;
        if (!r[x]) r[x]=p->L=p->R=p;
        else{
            p->L=r[x]; p->R=r[x]->R;
            p->L->R=p->R->L=p;
        }
    }

    void remove(P* p){
        p->L->R=p->R; p->R->L=p->L;
        TR(i, D, p){
            TR(j, R, i){
                j->D->U=j->U; j->U->D=j->D;
                sz[j->y]--;
            }
        }
    }

    void recall(P* p){
        p->L->R=p->R->L=p;
        TR(i, U, p){
            TR(j, L, i){
                j->D->U=j->U->D=j;
                sz[j->y]++;
            }
        }
    }

    bool dfs(int d){
        if (solved) return true;
        if (h[0]->R==h[0]) return solved=true;
        int m=INF;
        P* c;
        TR(i, R, h[0]){
            if (sz[i->y]<m){
                m=sz[i->y];
                c=i;
            }
        }
        remove(c);
        TR(i, D, c){
            ans.push(i->x);
            TR(j, R, i){
                remove(h[j->y]);
            }
            if (dfs(d+1)){
                return true;
            }
            TR(j, L, i){
                recall(h[j->y]);
            }
            ans.pop();
        }
        recall(c);
        return false;
    }

    bool work(){
        return dfs(0);
    }
}dlx;

/*
TEST:
1.
3 3
0 0 1
1 0 0
0 1 0
A:全选
2.
3 3
1 0 1
1 1 0
0 1 1
A:无解
3.
6 7
0 0 1 0 1 1 0
1 0 0 1 0 0 1
0 1 1 0 0 1 0
1 0 0 1 0 0 0
0 1 0 0 0 0 1
0 0 0 1 1 0 1
自己判断
*/
