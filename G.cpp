#include<bits/stdc++.h>
using namespace std;

int a[100010], b[100010];
typedef long long ll;

int main (){
   int n,t;
   cin >> n >> t;
   for(int i=1;i<=n;i++){
    cin >> a[i] >> b[i];
   }
   if (t == 0){
    cout << 0;
   }
   else if (t >= 3){
    cout << "infinity";
   }
   else if (t == 1){
    ll ans = 0;
    for (int i = 1;i <= n; ++i){
        ans += a[i]*b[i];
    }
    cout <<ans;
   }
   else if (t == 2){
    ll ans = 0;
    for (int i = 1;i <= n; ++i){
        ans += a[i]*b[i];
    }
    if (ans != 0){
        cout << "infinity";
    }
    else{
        ll dox = b[1];
        ll up1 = a[1]*b[1];
        ll up2 = 0;
        for (int i = 2;i <= n; ++i){
            ll xup1 = up1+a[i]*b[i];
            ll xup2 = up1*b[i]+up2+a[i]*b[i]*dox;
            ll xdox = dox+b[i];
            dox = xdox;
            up1 = xup1;
            up2 = xup2;
        }
        if (up2%2 == 0) cout << up2/2;
        else cout << up2 << "/2";
    }
   }

   return 0;
}
