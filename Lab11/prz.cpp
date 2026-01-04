#include <bits/stdc++.h>
#define ll long long

using namespace std;


struct point{
    ll x, y;
};
using vec = vector<point>;

struct ivl{
    int beg, end;
    double quality;
    ivl(int b, int e, const vec& seq){
        beg = b; end = e;
        quality = ((double) (seq[e].x - seq[b].x)) / sqrt(e - b + 1);
    }
    bool operator<(const ivl& other) const {
        constexpr double eps = 1e-6;

        if (quality < other.quality - eps) return true;
        if (quality > other.quality + eps) return false;

        return beg > other.beg;
    }
};

void print_set(const std::multiset<ll>& s) {
    for (ll v : s)
        std::cout << v << ' ';
    std::cout << '\n';
}

struct params{
    int n;
    ll U;
    vec seq;
};

void read_data(params& p){
    cin >> p.n >> p.U;
    p.seq.push_back({0,0});
    for(int i = 0 ; i < p.n ; i++){
        ll x, y;
        cin >> x >> y;
        p.seq.push_back({x, y});
    }
}

bool is_U_strict(multiset<ll>& set, const ll U, ll y){
    if(set.size() == 0)
        return true;
    ll Min = *set.begin();
    ll Max = *set.rbegin();
    assert(Min <= Max);
    if(abs(Min - y) > U || abs(Max - y) > U)
        return false;
    return true;
}

void maximize_ivl(const params& p, int& k, multiset<ll>& set){
    while(k < p.n  && is_U_strict(set, p.U, p.seq[k + 1].y)){
        set.insert(p.seq[k + 1].y);
        k++;
    }
}

void set_del(ll y, multiset<ll>& set){
    auto it = set.find(y);
    assert(it != set.end());
    set.erase(it);
}

void add_ivl(ivl cand, ivl& prev, priority_queue<ivl>& res){
    assert(cand.beg <= cand.end);
    if(cand.end == prev.end)
        res.push(prev);
    else{
        res.push(cand);
        prev = cand;
    }
}

void print_res(int i, priority_queue<ivl>& res){
    while(res.top().end < i){
        res.pop();
        assert(!res.empty());
    }
    cout << res.top().beg << ' ' << res.top().end << '\n';
}


void dp(const params& p){
    priority_queue<ivl> res;
    int k = 1;
    ivl prev = ivl(0, 0, p.seq);
    multiset<ll> set;
    set.insert(p.seq[1].y);
    for(int i = 1 ; i <= p.n ; ++i){
        maximize_ivl(p, k, set);
        set_del(p.seq[i].y, set);
        add_ivl(ivl(i, k, p.seq), prev, res);
        print_res(i, res);
    }
}

void solve(){
    params par;
    read_data(par);
    dp(par);
}

int main(){
    solve();
}