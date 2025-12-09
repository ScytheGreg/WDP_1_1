#include "worki.h"
#include <forward_list>
#include <iostream>

using namespace std;
int bag_cnt = -1;
bool INIT = false;
worek *Tree; // Christmas tree (desk)
Elf *Santa;  // Santa is an Elf for the Christmas tree
forward_list<worek *>
    bag_ptrs; // I use list to keep strict O(1) for every operation.
forward_list<przedmiot *> pres_ptrs;

void malloc_error() {
  std::cout << "Malloc error!\nYour presents delivery failed :(\n";
}

// Allocates memory.
template <typename T> T *allocate() {
  T *ptr = (T *)malloc(sizeof(T));
  if (!ptr)
    malloc_error();
  return ptr;
}

// Creates an elf
Elf *new_elf(worek *bag) {
  Elf *elf = allocate<Elf>();
  elf->bag = bag;
  elf->pres_cnt = 0;
  return elf;
}

// New bag!!
worek *new_bag(int nr) {
  worek *bag = allocate<worek>();
  bag->origin = new_elf(bag);
  bag->nr = nr;
  bag->elf = Santa;
  bag_ptrs.push_front(bag);
  return bag;
}

void init() {
  Tree = new_bag(bag_cnt++);
  Santa = Tree->origin;
  INIT = true;
}

// New present under Christmas Tree!
przedmiot *nowy_przedmiot() {
  if (!INIT)
    init();
  przedmiot *pres = allocate<przedmiot>();
  pres->elf = Santa;
  Tree->origin->pres_cnt++;
  pres_ptrs.push_front(pres);
  return pres;
}

// New bag under Christmas Tree!
worek *nowy_worek() {
  if (!INIT)
    init();
  return new_bag(bag_cnt++);
}

// Insert a present to a bag
void wloz(przedmiot *co, worek *gdzie) {
  co->elf = gdzie->origin;
  gdzie->origin->pres_cnt += 1;
}

// Inserts a bag to another bag.
void wloz(worek *co, worek *gdzie) {
  co->elf = gdzie->origin;
  gdzie->origin->pres_cnt += co->origin->pres_cnt;
}

// Pulls a presents from bag lying under Christmas Tree
void wyjmij(przedmiot *p) {
  p->elf->pres_cnt -= 1;
  p->elf = Santa;
}

// Pulls a bag from another bag lying under Christmas Tree
void wyjmij(worek *w) {
  w->elf->pres_cnt -= w->origin->pres_cnt;
  w->elf = Santa;
}

// Returns number of bag in which lie a present
int w_ktorym_worku(przedmiot *p) { return p->elf->bag->nr; }

// Returns number of bag in which lie a bag
int w_ktorym_worku(worek *w) { return w->elf->bag->nr; }

// Returns number of presents inside a bag
int ile_przedmiotow(worek *w) { return w->origin->pres_cnt; }

// Unpack the bag and pack everything else to that bag.
void na_odwrot(worek *w) {
  // In general that function changes proper values and swaps Santa with bag 'w'
  int all_pres = Santa->pres_cnt;
  Santa->pres_cnt = all_pres - w->origin->pres_cnt;
  w->origin->pres_cnt = all_pres;
  swap(Santa->bag, w->origin->bag);
  Santa = w->origin;
  swap(Tree->origin, w->origin);
  w->elf = Santa;
}

// Clean
void gotowe() {
  while (!bag_ptrs.empty()) {
    free(bag_ptrs.front()->origin);
    free(bag_ptrs.front());
    bag_ptrs.pop_front();
  }
  while (!pres_ptrs.empty()) {
    free(pres_ptrs.front());
    pres_ptrs.pop_front();
  }
}
