#include <bits/stdc++.h>
using namespace std;

const int PN = 20000;
const int N = 1e5+10;
const int MOD = 998244353;
typedef long long ll;
int phi[PN+2];
int pri[110], isp[110], cnt;

int n, m;
int a[N];

void getp(){

    for (int i = 2;i <= 100; ++i){
        if (isp[i] == 0){
            pri[++cnt] = i;
        }
        for (int j = 1;j <= cnt && i*pri[j] <= 100; ++j){
            isp[i*pri[j]] = 1;
            if (i%pri[j] == 0) break;
        }
    }
    for (int i = 1;i <= cnt; ++i)
        isp[pri[i]] = i;
}



void getPhi(){

    for (int i = 1;i <= PN; ++i) phi[i] = i;
    for (int i = 2;i <= PN; i += 2){
        phi[i] /= 2;
    }
    for (int i = 3;i <= PN; i += 2){
        if (phi[i] == i){
            for (int j = i;j <= PN; j += i){
                phi[j] = phi[j]/i*(i-1);
            }
        }
    }
}

struct Tree
{
    int isMul[26];
    ll sum;
    ll mul;
}tree[N*4];

void up(int rt, int x){
    tree[rt].sum = (tree[rt<<1].sum+tree[rt<<1|1].sum)%MOD;
    if (tree[rt<<1].isMul[x] == 1 && tree[rt<<1|1].isMul[x] == 1) tree[rt].isMul[x] = 1;
    else if (tree[rt<<1].isMul[x] == 0 && tree[rt<<1|1].isMul[x] == 0) tree[rt].isMul[x] = 0;
    else tree[rt].isMul[x] = -1;
}

void dow(int rt, int x){
    if (tree[rt].isMul[x] != -1)
    {
        tree[rt<<1].isMul[x] = tree[rt].isMul[x];

        tree[rt<<1|1].isMul[x] = tree[rt].isMul[x];
    }
    tree[rt<<1].mul = (tree[rt].mul * tree[rt<<1].mul)%MOD;
    tree[rt<<1|1].mul = (tree[rt].mul * tree[rt<<1|1].mul)%MOD;
    tree[rt<<1].sum = (tree[rt].mul * tree[rt<<1].sum)%MOD;
    tree[rt<<1|1].sum = (tree[rt].mul * tree[rt<<1|1].sum)%MOD;
    tree[rt].mul = 1;
}

void build(int rt, int l, int r){
    tree[rt].mul = 1;
    if (l == r){
        tree[rt].sum = phi[a[l]];
        memset(tree[rt].isMul, 0, sizeof(tree[rt].isMul));
        int tmp = a[l];
        for (int i = 1;i <= cnt; ++i){
            if (tmp%pri[i] == 0)
            {
                //cout << i << endl;
                tree[rt].isMul[i] = 1;
                while(tmp%pri[i] == 0) tmp /= pri[i];
            }
        }
        return;
    }
    int mid = (l+r)/2;
    build(rt<<1, l, mid);
    build(rt<<1|1, mid+1, r);
    for (int i = 1;i <= cnt; ++i){
        up(rt, isp[pri[i]]);
    }
}

void upd(int rt, int l, int r, int ql, int qr, ll v){

    if (r < ql || l > qr) return;
    //cout << l << ' ' << r << ' ' << ql << ' ' << qr << endl;
    if (l >= ql && r <= qr && tree[rt].isMul[isp[v]] == 1){
        tree[rt].sum = (tree[rt].sum*v)%MOD;
        tree[rt].mul = (tree[rt].mul*v)%MOD;
        return;
    }
    if (l >= ql && r <= qr && tree[rt].isMul[isp[v]] == 0){
        tree[rt].sum = (tree[rt].sum*(v-1))%MOD;
        tree[rt].mul = (tree[rt].mul*(v-1))%MOD;
        tree[rt].isMul[isp[v]] = 1;
        return;
    }
    //cout << rt << ' ' << l << ' ' << r << ' ' << tree[rt].mul << endl;
    dow(rt, isp[v]);
    //cout << tree[rt].sum << endl;
    int mid = (l+r)/2;
    upd(rt<<1, l, mid, ql, qr, v);
    upd(rt<<1|1, mid+1, r, ql, qr, v);

    up(rt, isp[v]);
}

ll query(int rt, int l, int r, int ql, int qr){
    if (r < ql || l > qr) return 0LL;
    if (l >= ql && r <= qr) return tree[rt].sum;
    int mid = (l+r)/2;
    ll val = (query(rt<<1, l, mid, ql, qr) + query(rt<<1|1, mid+1, r, ql, qr))%MOD;
    return val;
}

int main(){
    freopen("L.in", "r", stdin);
    getPhi();
    getp();
    scanf("%d%d", &n, &m);
    for (int i = 1;i <= n; ++i) scanf("%d", &a[i]);
    //build(1, 1, n);
    int op, l, r, w;
    //cout << phi[2] << endl;
    //m = 0;
    int ok = 0;
    while(m--){
        //cout << tree[8].sum << endl;
        scanf("%d", &op);
        if (op == 0){
            scanf("%d%d%d", &l, &r, &w);
            //cout << l << ' ' << r << ' ' << w << endl;
            for (int i = l;i <= r; ++i) a[i]*=w;
        }
        else{
            scanf("%d%d", &l, &r);
            ll tmp = 0;
            for (int i = l;i <= r; ++i){
                tmp += phi[a[i]];
                cout << a[i] << endl;
            }
            //cout << tmp << endl;
        }
    }


    return 0;
}
