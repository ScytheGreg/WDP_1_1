#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


int suma(int a, int b){
    return a + b;
}

int roznica(int a, int b){
    return a - b;
}

typedef int (*suma_albo_roznica)(int, int);

suma_albo_roznica suma_czy_roznica(bool x){
    if(x)
        return suma;
    return roznica;
}

int suma_trzech(int (*Function_Ptr)(int, int), int a, int b, int c){

    int a_plus_b = Function_Ptr(a, b);

    int a_plus_b_plus_c = Function_Ptr(a_plus_b, c);

    return a_plus_b_plus_c;
}

int main(){

    suma_albo_roznica funkcja = suma_czy_roznica(false);

    int a = suma_trzech(funkcja, 22, 0, 11);

    printf("Nasza suma: %d \n", a);

    return 0;
}