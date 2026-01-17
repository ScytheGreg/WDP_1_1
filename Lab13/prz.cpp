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
  int fll_emp_sum() { return emp_cnt + fll_cnt; }
};

struct params {
  int n;
  vector<int> cap; // Capacities
  int cap_gcd;
  stage end;   // Configuration at the end
  stage start; // Start configuraion
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
  int zeros = 0;
  for (int i = 0; i < p.n; ++i) {
    int c, e;
    cin >> c >> e;
    if (c != 0) {
      p.cap.push_back(c);
      p.end.lvl.push_back(e);
      p.start.lvl.push_back(0);
    } else
      zeros++;
  }
  p.n -= zeros;
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

int calc_gcd(const vector<int> &cap) {
  assert(cap.size() != 0);
  int gcd = cap[0];
  for (int i = 1; i < (int)cap.size(); ++i) {
    gcd = __gcd(gcd, cap[i]);
  }
  return gcd;
}

void init_data(params &p) {
  X_pow[0] = 1;
  for (int i = 1; i <= p.n; ++i) { // Calculate powers of X
    X_pow[i] = (X_pow[i - 1] * X) % P;
  }
  p.end.hash = calc_hash(p.end.lvl);
  p.start.hash = calc_hash(p.start.lvl);
  full_emp_cnt(p);
  p.cap_gcd = calc_gcd(p.cap);
}

bool check_if_reachable(const params &p, stage end) {
  bool reachable = true;
  if (end.fll_emp_sum() == 0)
    reachable = false;
  for (int i = 0; i < p.n; ++i) {
    if (end.lvl[i] > p.cap[i])
      reachable = false;
    if (p.cap_gcd != 0) {
      if (end.lvl[i] % p.cap_gcd != 0)
        reachable = false;
    }
  }
  return reachable;
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

vector<stage> all_possible_nexts(const params &p, const stage &curr) {
  vector<stage> res;
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

void add_moves_from_empty(const params &p, const stage &curr,
                          vector<stage> &res, int i) {
  for (int lvl = p.cap_gcd; lvl <= p.cap[i];
       lvl += p.cap_gcd) {                       // Pour to that glass
    modifier pour_in = {.idx = i, .value = lvl}; //(Reversed pouring out)
    res.push_back(modify_stage(p, curr, {pour_in}));
  }
  for (int j = 0; j < p.n; ++j) { // Pour from any glass to that one
    if (i != j) {                 // (Reveresed case of glass to glass)
      for (int lvl = curr.lvl[j]; lvl > 0; lvl -= p.cap_gcd) {
        modifier to = {.idx = i, .value = lvl};
        modifier from = {.idx = j, .value = curr.lvl[j] - lvl};
        res.push_back(modify_stage(p, curr, {to, from}));
      }
    }
  }
}

void add_moves_from_full(const params &p, const stage &curr, vector<stage> &res,
                         int i) {
  for (int lvl = p.cap[i]; lvl > 0; lvl -= p.cap_gcd) {
    modifier pour_out = {.idx = i, .value = p.cap[i] - lvl};
    res.push_back(modify_stage(p, curr, {pour_out}));
  }
  for (int j = 0; j < p.n; ++j) {
    int max_lvl = p.cap[j] - curr.lvl[j];
    for (int lvl = max_lvl; lvl > 0; lvl -= p.cap_gcd) {
      modifier from = {.idx = i, .value = p.cap[i] - lvl};
      modifier to = {.idx = j, .value = curr.lvl[j] + lvl};
      res.push_back(modify_stage(p, curr, {from, to}));
    }
  }
}

vector<stage> all_possible_prevs(const params &p, const stage &curr) {
  vector<stage> res;
  for (int i = 0; i < p.n; ++i) {
    if (curr.lvl[i] == 0) {
      add_moves_from_empty(p, curr, res, i);
    }
    if (curr.lvl[i] == p.cap[i]) {
      add_moves_from_full(p, curr, res, i);
    }
  }
  return res;
}

using nexts_func = function<vector<stage>(const params &, const stage &)>;

class bfs_params {
  long long end_hash;

public:
  std::unordered_set<long long> vis; // Visited set - keeps hashes of stages
  std::queue<stage> next_stgs;       // Bfs queue - that one might be big
  nexts_func all_possible_nexts;
  int result = -1;
  bfs_params(long long hash, nexts_func possible_nexts) {
    this->end_hash = hash;
    this->all_possible_nexts = possible_nexts;
  }
  long long get_end_hash() { return end_hash; }
};

void bfs_step(bfs_params &bp, const params &p) {
  stage curr = bp.next_stgs.front(); // Current vertex
  bp.next_stgs.pop();                // Remove from queue
  for (stage next :
       bp.all_possible_nexts(p, curr)) { // Look for all possible moves
    if (bp.vis.count(next.hash) == 0 &&
        next.fll_emp_sum() >
            0) { // Make sure it's not visited and have an full or empty glass
      next.move_cnt++;                      // Update move counter
      if (next.hash == bp.get_end_hash()) { // Check the end condition
        bp.result = next.move_cnt;
      }
      bp.vis.insert(next.hash); // Mark as visited
      bp.next_stgs.push(next);  // Push to bfs queue
    }
  }
}

int bfs(params &p, const stage &start, const stage &end,
        nexts_func possible_nexts) {
  if (start.hash == end.hash)
    return 0;
  bfs_params bp(end.hash, possible_nexts);
  bp.vis.insert(start.hash); // Mark start as visited
  bp.next_stgs.push(start);  // Add start to queue
  while (!bp.next_stgs.empty() &&
         bp.result == -1) { // As long as move is possible
    bfs_step(bp, p);
  }
  return bp.result;
}

void solve() {
  params p;
  read_data(p);
  if (p.n == 0) {
    cout << 0 << '\n';
    return;
  }
  init_data(p);
  if (!check_if_reachable(p, p.end)) {
    cout << -1 << '\n';
    return;
  }
  // cout << bfs(p, p.start, p.end, all_possible_nexts) << '\n';
  cout << bfs(p, p.end, p.start, all_possible_prevs) << '\n';
}

int main() {
  solve();
  return 0;
}
