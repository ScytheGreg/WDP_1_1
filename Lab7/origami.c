#include <stdio.h>

const int FIGURE_LIMIT = 1000;
const int LINE_LIMIT   = 100;

typedef struct {double x1, y1, x2, y2;} rect;

typedef struct {double x, y, r; } circ;

typedef enum { RECTANGLE, CIRCLE } shape_type;

typedef struct { double x1, y1, x2, y2; } line;

typedef struct {
    shape_type type;
    union {
        rect rectangle;
        circ circle;
    };
    line lines[];
    int l_cnt;
} shape;



void read_data(rect* resc[], circ* cirs[]){

}

void solve(){
    shape* figures = (shape*) malloc(FIGURE_LIMIT * sizeof(shape)); 
    assert(figures != NULL);

    int n, q;
    if(scanf("%d %d", *n, *q) != 2){
        printf("Input error\n");
        exit(0);
    }

    read_data(*figures, n);

    for(int i = 0 ; i < q ; ++i){
        int k;
        double x, y;
        if(scanf("%d %lf %lf", k, x, y) != 3){
            printf("Input error\n");
            exit(0);
        }
        printf("%d\n", query(figures[k], x, y));
    }
}
int main(){
    solve();
    return 0;
}

