#include <bits/stdc++.h>
using namespace std;

constexpr int X = 37;            // Hash polynominal variable
constexpr long long P = 1e9 - 7; // Hash modulo prime
constexpr int MAX_N = 15;
long long X_pow[MAX_N]; // Powers of X

struct stage {
  int move_cnt = 0;
  int emp_cnt = 0; // Empty glasses cnt
  int fll_cnt = 0; // Full glasses cnt
  long long hash;
  vector<int> lvl; //  Water levels
};

struct params {
  int n;
  vector<int> cap; // Capacities
  stage end;       // Configuration at the end
  stage start;     // Start configuraion
};

long long
calc_hash(vector<int> &lvl) {
  long long hash = 0;
  for (int i = 0; i < (int) lvl.size(); ++i) {
    hash += lvl[i] * X_pow[i];
    hash %= P;
  }
  return hash;
}

void read_data(params &p) {
  cin >> p.n;
  if (p.n > MAX_N) {
    cerr << "Data too big!";
    exit(0);
  }
  for (int i = 0; i < p.n; ++i) {
    int c, e;
    cin >> c >> e;
    p.cap.push_back(c);
    p.end.lvl.push_back(e);
    p.start.lvl.push_back(0);
  }
}

void full_emp_cnt(params &p) {
  for (int i = 0; i < p.n; ++i) {
    if (p.end.lvl[i] == 0)
      p.end.emp_cnt++;
    if (p.end.lvl[i] == p.cap[i])
      p.end.fll_cnt++;
  }
  p.start.emp_cnt = p.n;
}

void init_data(params &p) {
  X_pow[0] = 1;
  for (int i = 1; i <= p.n; ++i) { // Calculate powers of X
    X_pow[i] = (X_pow[i - 1] * X) % P;
  }
  p.end.hash = calc_hash(p.end.lvl);
  p.start.hash = calc_hash(p.start.lvl);
  full_emp_cnt(p);
}

vector<stage> all_possible_nexts(params& p, stage curr){
    vector<stage> res;
    stage nex;
    for(int i = 0 ; i < p.n ; ++i){
        res.push_back(modify_stage(p, curr, {i, 0}));       // Pour out
        res.push_back(modify_stage(p, curr, {i, p.cap[i]}));// Pour in
        for(int j = 0 ; j < p.n ; ++j){
            
        }
    }
}


int bfs(params& p, const stage& start, const stage& end){
    std::unordered_set<long long> vis;
    std::queue<stage> next_stgs;
    vis.insert(start.hash);
    next_stgs.push(start);
    while(!next_stgs.empty()){
        stage curr = next_stgs.front(); // Current vertex
        next_stgs.pop();                // Remove from queue
        move_cnt ++;                    // That was a move
        if(curr.hash == end.hash){      // Stop condition
            return curr.move_cnt;
        }
        for(stage next : all_possible_nexts(p, curr)){
            if(vis.count(next.hash) == 0){
                vis.insert(next.hash);
                next_stgs.push(next);
            }
        }
    }
    return -1;
}


void solve() {
  params p;
  read_data(p);
  init_data(p);

  bfs(p,  p.start, p.end);
}

int main() { 
    solve();
    return 0;
}
