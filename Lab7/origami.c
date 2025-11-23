#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "debug.h"

const unsigned FIGURE_LIMIT = 1000;
const unsigned LINE_LIMIT   = 22;


void input_error(){
    printf("Input error\n");
    exit(0);
}

shape* init_shape(shape_type fig_type){
    printf("Init_shape\n");
    shape* figure = (shape*) malloc(sizeof(shape) + LINE_LIMIT * sizeof(line));
    assert(figure != NULL);
    figure -> type  = fig_type;
    figure -> l_cnt = 0;
    printf("Init_shape_end\n");
    return figure;
}

void read_circle(shape* figures[], int k){
    printf("Read_circle\n");
    circ rc;
    if(scanf("%lf %lf %lf", &rc.x, &rc.y, &rc.r) != 3)
        input_error();
    
    figures[k] = init_shape(CIRCLE);
    figures[k] -> circle = rc;
    printf("Read_circle_end\n");
}

void read_rectangle(shape* figures[], int k){
    printf("Read_rectangle\n");
    rect rr;
    if(scanf("%lf %lf %lf %lf", &rr.x1, &rr.y1, &rr.x2, &rr.y2) != 4)
        input_error();

    figures[k] = init_shape(RECTANGLE);
    figures[k] -> rectangle = rr;
    printf("Read_rectangle_end\n");
}

void read_line(shape* figures[], int k){
    line rl;
    int idx;
    if(scanf("%d %lf %lf %lf %lf", &idx, &rl.x1, &rl.y1, &rl.x2, &rl.y2) != 5)
        input_error();
    assert(1 <= idx && idx < k);
    int cnt = figures[idx] -> l_cnt;
    figures[idx] -> lines[cnt] = rl;
    figures[idx] -> l_cnt ++;

    print_shape(figures[idx]);
}

typedef void (*read_object)(shape**, int);

void read_data(shape* figures[], int n){
    for(int i = 1 ; i <= n ; ++i){
        char object_type;
        if(scanf("\n%c", &object_type) != 1)
            input_error();
        assert((object_type == 'P' || object_type == 'K') || object_type == 'Z');

        read_object read_func[256] = {NULL};
        read_func['P'] = read_rectangle;
        read_func['K'] = read_circle;
        read_func['Z'] = read_line;

        if(read_func[(unsigned char) object_type] == NULL)
            input_error();
        read_func[(unsigned char) object_type](figures, i);
    }

}

int is_inside(shape* figure, double x, double y){

}

int proper_side(double x, double y, line our_line){

}


int rec(shape* figure, double x, double y, int l_ix){
    if(l_ix < 0)
        return(is_inside(figure, x, y));

    line our_line = figure->lines[l_ix];
    point p;
    p = sym(x, y, our_line);
    if(proper_side(x, y, our_line) == 1)
        return rec(figure, x, y, l_ix - 1) + rec(figure, p.x, p.y, l_ix - 1);

    else if(proper_side(x, y, our_line) == 0)
        return(rec(figure, x, y, l_ix - 1));

    return 0;// if proper_side(x, y, our_line) == -1
}

int query(shape* figure, double x, double y){
    return rec(figure, x, y, figure->l_cnt);
}

void solve(){
    int n, q;
    if(scanf("%d %d", &n, &q) != 2)
        input_error();

    shape** figures = (shape**) malloc((unsigned)(n + 1) * sizeof(shape));
    assert(figures != NULL);

    read_data(figures, n);

    for(int i = 0 ; i < q ; ++i){
        int k;
        double x, y;
        if(scanf("%d %lf %lf", &k, &x, &y) != 3)
            input_error();

        printf("%d\n", rec(figures[k], x, y, figures[k]->l_cnt));
    }
}

int main(){
    solve();
    return 0;
}