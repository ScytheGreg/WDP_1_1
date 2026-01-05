// Solution of task "Ścisłe przedziały".
// Author: Grzegorz Kaczmarek. License: MIT

#include <bits/stdc++.h>
#define ll long long

using namespace std;

struct point {
  ll x, y;
};

// Intervals
struct ivl {
  int beg, end;
  double quality;
  ivl(int b, int e, const vector<point> &seq) {
    beg = b;
    end = e;
    quality = ((double)(seq[e].x - seq[b].x)) / sqrt(e - b + 1);
  }
  bool operator<(const ivl &other) const {
    constexpr double eps = 1e-6;

    if (quality < other.quality - eps)
      return true;
    if (quality > other.quality + eps)
      return false;

    return beg > other.beg;
  }
};

// Task parameters
struct params {
  int n;
  ll U;
  vector<point> seq;
};

void read_data(params &p) {
  cin >> p.n >> p.U;
  p.seq.push_back({0, 0}); // Push an "empty" point for indentation
  for (int i = 0; i < p.n; i++) {
    ll x, y;
    cin >> x >> y;
    p.seq.push_back({x, y});
  }
}

// Checks if set will be U-strict after adding a point
bool is_U_strict(multiset<ll> &set, const ll U, point pnt) {
  if (set.size() == 0)
    return true;
  ll Min = *set.begin();
  ll Max = *set.rbegin();
  if (abs(Min - pnt.y) > U || abs(Max - pnt.y) > U) // Condition check
    return false;
  return true;
}

// Increases 'k' as long as set is U-strict
void maximize_ivl(const params &p, int &k, multiset<ll> &set) {
  while (k < p.n && is_U_strict(set, p.U, p.seq[k + 1])) {
    set.insert(p.seq[k + 1].y);
    k++;
  }
}

// Deletes a value from the set
void set_del(ll y, multiset<ll> &set) {
  auto it = set.find(y);
  assert(it != set.end());
  set.erase(it);
}

// Adds interval to result queue. If ivl cand has the same and as prev, prefers
// prev.
void add_ivl(ivl cand, ivl &prev, priority_queue<ivl> &res) {
  assert(cand.beg <= cand.end);
  if (cand.end == prev.end)
    res.push(prev);
  else {
    res.push(cand);
    prev = cand;
  }
}

// As only ivl from queue contain 'i', prints result for 'i'.
void print_res(int i, priority_queue<ivl> &res) {
  while (res.top().end < i) {
    res.pop();
    assert(!res.empty());
  }
  cout << res.top().beg << ' ' << res.top().end << '\n';
}

// Dynamic solution. Using only one previous result. O(nlogn)
void dp(const params &p) {
  priority_queue<ivl> res;     // Sorts by quality, then by beginning
  int k = 1;                   // Indicator for last added point to set
  ivl prev = ivl(0, 0, p.seq); // Keeps previous added interval to result
  multiset<ll> set;            // Keeps y coordinate of added points from ivls.
  set.insert(p.seq[1].y);
  for (int i = 1; i <= p.n; ++i) {
    maximize_ivl(p, k, set);              // Go with 'k' as far as possible
    add_ivl(ivl(i, k, p.seq), prev, res); // Add this or prev ivl to result
    print_res(i, res);                    // Print optimal ivl
    set_del(p.seq[i].y, set);             // Remove current point from set
  }
}

void solve() {
  params par;
  read_data(par);
  dp(par);
}

int main() { solve(); }