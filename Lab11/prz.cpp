#include <iostream>
#include <vector>
#include <set>
#define ll long long

using namespace std;


struct point{
    ll x, y;
};
using vec = vector<point>;

struct ivl{
    int beg, end;
};
struct params{
    int n;
    ll U;
    vec seq;
}

void read_data(params& par){
    cin >> par.n >> par.U;
    par.seq.push_back({0,0});
    for(int i = 0 ; i < n ; i++){
        ll x, y;
        cin >> x >> y;
        par.seq.push_back({x, y});
    }
}

bool is_U_strict(multiset<ll>& set, const ll U, ll y){
    ll Min = *set.begin();
    ll Max = *set.rbegin();
    assert(Min <= Max);
    if(abs(Min - y) > U || abs(Max - y) > U)
        return false;
    return true;
}

maximize_ivl(const params& p, int& k, multiset>ll>& set){
    while(k < p.n - 1 && is_U_strict(set, p.U, p.seq[k + 1].y)){
        set.insert(p.seq[k + 1].y);
        k++;
    }
}

void add_result(ivl cand, ivl& prev, vector<ivl>& res){
    assert(cand.beg <= cand.end);
    if(cand.end == prev.end)
        res.push_back(prev);
    else{
        res.push_back(cand);
        prev = cand;
    }
}

void set_del(ll y){
    auto it = set.find(y);
    set.erase(it);
}

vector<ivl> dp(const params& p){
    vector<ivl> res(1);
    int k = 1;
    ivl prev = -1;
    multiset<ll> set;
    for(int i = 1 ; i <= p.n ; ++i){
        set.insert(p.seq[i].y);
        maximize_ivl(p, k, set);
        add_result({i, k}, prev, res);
        set_del(p.seq[i].y);
    }
    return res;
}

void solve(){
    params par;
    read_data(par);
    dp(par);
}

int main(){
    solve();
}