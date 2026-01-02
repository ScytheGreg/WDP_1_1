#include <iostream>
#include <vector>
#define ll long long

using namespace std;


struct point{
    ll x, y;
};

class interval{
    // Constructor
    interval(int ind = 0, point p = {0, 0}){
        Min = Max = p.y;
        beg = end = ind;
    }
    bool extend(point p){
        end++;
        Min = min(Min, p.y);
        Max = max(Max, p.y);
    }
public:
    ll Min, Max;
    int beg, end;
}

using vec = vector<point>;

void read_data(int& n, ll& U, vec& seq){
    cin >> n >> U;
    for(int i = 0 ; i < n ; i++){
        ll x, y;
        cin >> x >> y;
        seq.push_back({x, y});
    }
}

void dp(int n, int U, const vec& seq){
    for(int i = 1 ; i <= n ; ++i){
        interval res(1, seq[1]);

    }
}

void solve(){
    int n;
    ll U;
    vec seq;
    seq.push_back({0, 0});
    read_data(n, U, seq);
    seq.push_back({0, 0});
    dp(n, U, seq);
}

int main(){

}