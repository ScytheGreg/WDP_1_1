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

struct modifier {
  int idx;
  int value;
};

long long calc_hash(vector<int> &lvl) {
  long long hash = 0;
  for (int i = 0; i < (int)lvl.size(); ++i) {
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

void update_fll_empt_cnt(const params &p, stage &res, modifier mod) {
  int old_lvl = res.lvl[mod.idx];                   // Old water level
  int new_lvl = mod.value;                          // New water level
  if (new_lvl != old_lvl) {                         // Only if levels diff
    int cap = p.cap[mod.idx];                       // Capacity of that glass
    res.emp_cnt += (new_lvl == 0) - (old_lvl == 0); // Update counter...
    res.fll_cnt += (new_lvl == cap) - (old_lvl == cap); // in low-lines way
  }
}

void update_hash(stage &res, modifier mod) {
  int old_lvl = res.lvl[mod.idx]; // Old water level
  int new_lvl = mod.value;        // New water level
  long long diff =
      P + new_lvl - old_lvl; // Adding P to force = re positive value
  res.hash += diff * X_pow[mod.idx];
  res.hash %= P;
}

stage modify_stage(const params &p, const stage &father,
                   const vector<modifier> &modified) {
  stage res = father;
  for (modifier mod : modified) {
    update_hash(res, mod);
    update_fll_empt_cnt(p, res, mod);
    res.lvl[mod.idx] = mod.value;
  }
  return res;
}

vector<modifier> pour_glass_to_glass(const params &p, const stage &curr, int i,
                                     int j) {
  int from_lvl = curr.lvl[i];         // Level of water in 'from' glass
  int space = p.cap[j] - curr.lvl[j]; // Empty space in 'to' glass
  modifier from, to;
  from.idx = i;
  to.idx = j;
  if (space >= from_lvl) {             // Whole water fits in another glass
    from.value = 0;                    // Current is empty
    to.value = curr.lvl[j] + from_lvl; // Another get whole water
  } else {
    from.value = from_lvl - space; // Some water was poured out
    to.value = p.cap[j];           // 'To' glass is full
  }
  return {from, to};
}

vector<stage> all_possible_nexts(const params &p, stage curr) {
  vector<stage> res;
  stage nex;
  for (int i = 0; i < p.n; ++i) {
    modifier empty = {.idx = i, .value = 0};
    modifier full = {.idx = i, .value = p.cap[i]};
    res.push_back(modify_stage(p, curr, {empty})); // Pour out
    res.push_back(modify_stage(p, curr, {full}));  // Pour in
    if (curr.lvl[i] != 0) {                        // If there's some water
      for (int j = 0; j < p.n; ++j) { // Pour from current to all other
        if (i != j) {
          auto mods = pour_glass_to_glass(p, curr, i, j);
          res.push_back(modify_stage(p, curr, mods));
        }
      }
    }
  }
  return res;
}

int bfs(params &p, const stage &start, const stage &end) {
  if (start.hash == end.hash)
    return 0;
  std::unordered_set<long long> vis; // Visited set - keeps hashes of stages
  std::queue<stage> next_stgs;       // Bfs queue - that one might be big
  vis.insert(start.hash);            // Mark start as visited
  next_stgs.push(start);             // Add start to queue
  while (!next_stgs.empty()) {       // As long as move is possible
    stage curr = next_stgs.front();  // Current vertex
    next_stgs.pop();                 // Remove from queue
    for (stage next :
         all_possible_nexts(p, curr)) { // Look for all possible moves
      if (vis.count(next.hash) == 0) {  // Make sure it's not visited
        next.move_cnt++;                // Update move counter
        if (next.hash == end.hash)      // Check the end condition
          return next.move_cnt;
        vis.insert(next.hash); // Mark as visited
        next_stgs.push(next);  // Push to bfs queue
      }
    }
  }
  return -1;
}

void solve() {
  params p;
  read_data(p);
  init_data(p);

  cout << bfs(p, p.start, p.end) << '\n';
}

int main() {
  solve();
  return 0;
}
