#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
int n;
int sgn[100], va[100], vb[100];
int ans[100];
ll low[100], hig[100];

set<int> st;

void cal(int x, int y,int val){
    if (y == 5){
        st.insert(val);
        return;
    }
    cal(x*2, y+1, val+sgn[y]*x);
    cal(x*2, y+1, val);
}

int main(){
    freopen("M.in", "r", stdin);
    scanf("%d", &n);
    for (int i = 1;i <= n; ++i){
        scanf("%d", &sgn[i]);
    }
    for (int i = 1;i <= n; ++i){
        scanf("%d", &va[i]);
    }
    for (int i = 1;i <= n; ++i){
        scanf("%d", &vb[i]);
    }
    int a = 0, b = 0;
    ll tmp = 1;
    for (int i = 1;i <= n; ++i){
        a += va[i]*sgn[i]*tmp;
        tmp *= 2;
    }
    tmp = 1;
    for (int i = 1;i <= n; ++i){
        b += vb[i]*sgn[i]*tmp;
        tmp *= 2;
    }
    //cout << a << ' ' << b << endl;

    tmp = 1;
    for (int i = 1;i <= n; ++i){
        if (sgn[i] < 0){
            low[i] = low[i-1]-tmp;
            hig[i] = hig[i-1];
        }
        else{
            low[i] = low[i-1];
            hig[i] = hig[i-1]+tmp;
        }
        tmp *= 2;
    }
    int c = a+b;
    tmp /= 2;
    for (int i = n;i >= 1; --i){
        if (c >= low[i-1] && c <= hig[i-1]) ans[i] = 0;
        else{
            c -= sgn[i]*tmp;
            ans[i] = 1;
        }
        tmp /= 2;
    }

    for (int i = 1;i <= n; ++i){
        printf("%d", ans[i]);
        if (i != n) printf(" ");
    }
    puts("");

    return 0;
}
