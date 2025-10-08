// Sprawdzić sinol-make
// Dobre komentarze w miejscach, które są nieoczywiste i ułatwiają przeczytanie programu


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

int max(int a, int b){
    if(a >= b)
         return a;
    return b;
}

void read_data(int* _n, int** _t){

    assert(scanf("%d", _n) == 1); // Read n (assert only for avoiding warning - error)

    *_t = (int*) malloc ((unsigned int)*_n * sizeof(int)); // Allocate memory for array t

    for(int i = 0 ; i < *_n ; i++){
        assert(scanf("%d", &(*_t)[i]) == 1); // Read values of t
    }
}

bool is_x_divisor_y(int a, int b){
    if(a == 0)
        return false; // We assume that 0 never divides
    if(b % a == 0) 
        return true;
    return false;
}

int descending_length_form(int index, const int* t){
    /*
    This function returns length of "divisable
    interval" with the last element at 'index'.
    */

    int length = 1;
    int divised = t[index];
    while(index >= 1){
        index --;
        if(is_x_divisor_y(t[index], divised))
            length ++;
        else
            break;
    }
    return length;
}

int descending_check(int index, const int* t, int* _result){
    /*
    This function updates index of last checked element
    and updates result if better.
    */
    int length = descending_length_form(index, t);
    *_result = max(*_result, length);

    return index - length;
}

int calculate_max_descending(int n, const int* t){
    if(n == 0)
        return 0;// In case n > 0, the legth of required interval must be at least 1.
    /*
    The algorithm starts from the last element of given data.
    As we descend, following 'divisible intervals' are tracked down.
    The length of the longest is the result.
    */    
    int result = 1;
    int k = n - 1;
    while(k >= 1)
        k = descending_check(k, t, &result);

    return result;
}

void print_result(int result){
    printf("%d\n", result);
}

void solve(){
    int n;
    int* t = NULL;
    read_data(&n, &t);

    int result = calculate_max_descending(n, t);

    print_result(result);
    
    free(t);
}


int main() {
    solve();
} 