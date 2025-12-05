#include <iostream>
#include <forward_list>
#include "worki.h"

using namespace std;
int bag_cnt = -1;
bool INIT = false;
worek* Tree; // Christmas tree
Elf* Santa; // Santa is an Elf for the Christmas tree
forward_list<worek*> bag_ptrs;
forward_list<przedmiot*> pres_ptrs;


void malloc_error(){
    std::cout << "Malloc error!\nYour presents delivery unsucceed :(\n";
}

template<typename T>
T* allocate(){
    T* ptr = (T*) malloc(sizeof(T));
    if(!ptr)
        malloc_error();
    return ptr;
}


Elf *new_elf(worek* bag){
    Elf* elf = allocate<Elf>();
    elf -> bag = bag;
    elf -> pres_cnt = 0;
    return elf;
}

worek *new_bag(int nr){
    worek* bag = allocate<worek>();
    bag -> origin = new_elf(bag);
    bag -> nr = nr;
    bag -> elf = Santa;
    bag_ptrs.push_front(bag);
    return bag;
}

void init(){
    Tree = new_bag(bag_cnt++);
    Santa = Tree -> origin;
    INIT = true;
}

// New present under Christmas Tree!
przedmiot *nowy_przedmiot(){
    if(!INIT) init();
    przedmiot* pres = allocate<przedmiot>();
    pres -> elf = Santa;
    Tree -> origin -> pres_cnt ++;
    pres_ptrs.push_front(pres);
    return pres;
}

// New bag under Christmas Tree! 
worek *nowy_worek(){
    return new_bag(bag_cnt++);
}

// Wkłada przedmiot co do worka gdzie.
// Założenie: co i gdzie leżą na biurku.
void wloz(przedmiot *co, worek *gdzie){
    co -> elf = gdzie -> origin;
    gdzie -> origin -> pres_cnt += 1;
}

// Wkłada worek co do worka gdzie.
// Założenie: co i gdzie leżą na biurku.
void wloz(worek *co, worek *gdzie){
    co -> elf = gdzie -> origin;
    gdzie -> origin -> pres_cnt += co -> origin -> pres_cnt;
}

// Wyjmuje przedmiot p z worka i kładzie na biurku.
// Założenie: Przedmiot p był w worku leżącym na biurku.
void wyjmij(przedmiot *p){
    p -> elf -> pres_cnt -= 1;
    p -> elf = Santa;
}

// Wyjmuje worek w z worka i kładzie na biurku.
// Założenie: Worek w był w worku leżącym na biurku.
void wyjmij(worek *w){
    w -> elf -> pres_cnt -= w -> origin -> pres_cnt;
    w -> elf = Santa;
}

// Wynik: numer worka, w którym znajduje się przedmiot p (-1 jeśli na biurku).
int w_ktorym_worku(przedmiot *p){
    return p -> elf -> bag -> nr;
}

// Wynik: numer worka, w którym znajduje się worek w (-1 jeśli na biurku).
int w_ktorym_worku(worek *w){
    return w -> elf -> bag -> nr;
}

// Wynik: liczba przedmiotów zawartych (bezpośrednio i pośrednio) w worku w
int ile_przedmiotow(worek *w){
    return w -> origin -> pres_cnt;
}

// Cała zawartość worka w ląduje na biurku, a wszystko, co poza workiem w
// znajdowało się bezpośrednio na biurku, ląduje wewnątrz worka w.
void na_odwrot(worek *w){
    int all_pres = Santa -> pres_cnt;
    Santa -> pres_cnt = all_pres - w -> origin -> pres_cnt;
    w -> origin -> pres_cnt = all_pres;
    swap(Santa -> bag, w -> origin -> bag);
    Santa = w -> origin;
    swap(Tree -> origin, w -> origin);
    w -> elf = Santa;
}

// Kończy i zwalnia pamięć
void gotowe(){
    while(!bag_ptrs.empty()){
        free(bag_ptrs.front() -> origin);
        free(bag_ptrs.front());
        bag_ptrs.pop_front();
    }
    while(!pres_ptrs.empty()){
        free(pres_ptrs.front());
        pres_ptrs.pop_front();
    }
}
