#include <stdlib.h>
#include <stdio.h>

int suma(int a, int b){
    return a + b;
}

int suma_trzech(int (*Function_Ptr)(int, int), int a, int b, int c){

    int a_plus_b = Function_Ptr(a, b);

    int a_plus_b_plus_c = Function_Ptr(a_plus_b, c);

    return a_plus_b_plus_c;
}

int main(){


    int a = suma_trzech(suma, 22, 0, 22);

    printf("Nasza suma: %d \n", a);

    return 0;
}