#ifndef WORKI_H
#define WORKI_H

struct Elf;
struct worek { // A bag full of presents
  int nr;
  Elf *origin;
  Elf *elf;
};

// Elf is a agent between presents and bags
struct Elf {
  int pres_cnt;
  worek *bag;
};

// We call it a present. Every presents indicates for an Elf
struct przedmiot {
  Elf *elf;
};

// New present!
przedmiot *nowy_przedmiot();

// New bag!
worek *nowy_worek();

// Insert a present to a bag
void wloz(przedmiot *co, worek *gdzie);

// Inserts a bag to another bag.
void wloz(worek *co, worek *gdzie);

// Pulls a presents from bag lying under Christmas Tree
void wyjmij(przedmiot *p);

// Pulls a bag from another bag lying under Christmas Tree
void wyjmij(worek *w);

// Returns number of bag in which lie a present
int w_ktorym_worku(przedmiot *p);

// Returns number of bag in which lie a bag
int w_ktorym_worku(worek *w);

// Returns number of presents inside a bag
int ile_przedmiotow(worek *w);

// Unpack the bag and pack everything else to that bag.
void na_odwrot(worek *w);

// Clean
void gotowe();

#endif
