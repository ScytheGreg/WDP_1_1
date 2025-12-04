#include <iostream>
#include <vector>
#include "worki.h"

using namespace std;
int bag_cnt = -1;
worek* desk;
std::vector<przedmiot*> obj_ptrs;
std::vector<worek*> bag_ptrs;

void malloc_error(){
    std::cout << "Malloc error!\n";
}

void is_desk_init(){
    if(bag_cnt == -1)
        desk = nowy_worek(-1);
}

// Nowy przedmiot na biurku
przedmiot *nowy_przedmiot(){
    cout << "Stworz przedmiot!\n";
    is_desk_init();
    przedmiot* obj = (przedmiot*) malloc(sizeof(przedmiot));
    if(obj == nullptr)
        malloc_error();
    obj -> bag = desk;
    desk -> obj_cnt ++;
    obj_ptrs.push_back(obj);
    return obj;
}

worek *nowy_worek(int nr){
    cout << "Stworz worek nr " << nr << "\n";
    worek* bag = (worek*) malloc(sizeof(worek));
    if(bag == nullptr)
        malloc_error();
    bag -> nr = nr;
    bag -> bag = desk;
    bag -> obj_cnt = 0;
    bag_ptrs.push_back(bag);
    return bag;
}
// Nowy worek na biurku; otrzymuje kolejny numer, począwszy od 0.
worek *nowy_worek(){
    is_desk_init();
    return nowy_worek(++bag_cnt);
}

// Wkłada przedmiot co do worka gdzie.
// Założenie: co i gdzie leżą na biurku.
void wloz(przedmiot *co, worek *gdzie){
    co -> bag = gdzie;
    gdzie -> obj_cnt ++;
}

// Wkłada worek co do worka gdzie.
// Założenie: co i gdzie leżą na biurku.
void wloz(worek *co, worek *gdzie){
    co -> bag = gdzie;
    gdzie -> obj_cnt += co -> obj_cnt;
}

// Wyjmuje przedmiot p z worka i kładzie na biurku.
// Założenie: Przedmiot p był w worku leżącym na biurku.
void wyjmij(przedmiot *p){
    p -> bag -> obj_cnt --;
    p -> bag = desk;
}

// Wyjmuje worek w z worka i kładzie na biurku.
// Założenie: Worek w był w worku leżącym na biurku.
void wyjmij(worek *w){
    w -> bag -> obj_cnt -= w -> obj_cnt;
    w -> bag = desk;
}

// Wynik: numer worka, w którym znajduje się przedmiot p (-1 jeśli na biurku).
int w_ktorym_worku(przedmiot *p){
    return p -> bag -> nr;
}

// Wynik: numer worka, w którym znajduje się worek w (-1 jeśli na biurku).
int w_ktorym_worku(worek *w){
    return w -> bag -> nr;
}

// Wynik: liczba przedmiotów zawartych (bezpośrednio i pośrednio) w worku w
int ile_przedmiotow(worek *w){
    return w -> obj_cnt;
}

// Cała zawartość worka w ląduje na biurku, a wszystko, co poza workiem w
// znajdowało się bezpośrednio na biurku, ląduje wewnątrz worka w.
void na_odwrot(worek *w){
    int all_obj = desk -> obj_cnt;
    std::swap(desk -> nr, w -> nr);
    desk -> obj_cnt = all_obj - w -> obj_cnt;
    w -> obj_cnt = all_obj;
    desk -> bag = w;
    w -> bag = w;
    desk = w;
}

// Kończy i zwalnia pamięć
void gotowe(){
    for(przedmiot* obj : obj_ptrs)
        free(obj);
    for(worek* bag : bag_ptrs){
        free(bag);
    }
}
