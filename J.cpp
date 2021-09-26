#include <bits/stdc++.h>
using namespace std;

int n, m;
int h[510][510], hh[300000];

vector<int> G[300000];
double ans[300000];
int din[300000];

int ct(int i, int j){
    return n*(i-1)+j;
}

int tox[4] = {-1, 0, 1, 0}, toy[4] = {0, 1, 0, -1};

void tupo(){
    queue<int> que;
    for (int i = 1;i <= n*n; ++i) ans[i] = (double)m;
    for (int i = 1;i <= n*n; ++i){
        //cout << i << ' ' << din[i] << endl;
        if (din[i] == 0){
            que.push(i);
        }
    }
    while(!que.empty()){
        int nx = que.front();
        double sum = ans[nx];
        //cout << nx << ' ' << sum << endl;
        que.pop();
        if (G[nx].size() == 0) continue;
        double onep = sum/(double)G[nx].size();
        for (auto x: G[nx]){
            ans[x] += onep;
            //cout << x << ' ' << ans[x] << endl;
            if (--din[x] == 0) que.push(x);
        }
    }
}

int main(){
    freopen("J.in", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1;i <= n; ++i){
        for (int j = 1;j <= n; ++j){
            scanf("%d", &h[i][j]);
            hh[ct(i, j)] = h[i][j];
        }
    }
    for (int i = 1;i <= n; ++i){
        for (int j = 1;j <= n; ++j){
            for (int k = 0;k < 4; ++k){
                int tx = i+tox[k];
                int ty = j+toy[k];
                if (tx < 1 || tx > n || ty < 1 || ty > n) continue;
                if (h[i][j] > h[tx][ty]){
                    G[ct(i, j)].push_back(ct(tx, ty));
                    din[ct(tx, ty)]++;
                    //cout << i << ' ' << j << ' ' << tx << ' ' << ty << endl;
                }
            }
        }
    }
    tupo();
    for (int i = 1;i <= n; ++i){
        for (int j = 1;j <= n; ++j){
            if (h[i][j] != 0) printf("0 ");
            else printf("%.6lf ", ans[ct(i, j)]);
            //cout << i << ' ' << j << ' ' << ans[ct(i, j)] << endl;
        }
        puts("");
    }

    return 0;
}
