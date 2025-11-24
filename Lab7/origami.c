//#include "debug.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned FIGURE_LIMIT = 1000;
const unsigned LINE_LIMIT = 22;
const double ZERO = 1e-6;

typedef struct {
  double x1, y1, x2, y2;
} rect;

typedef struct {
  double x, y, r;
} circ;

typedef enum { RECTANGLE, CIRCLE } shape_type;

typedef struct {
  double x1, y1, x2, y2;
} line;

typedef struct {
  double x, y;
} point;

typedef struct {
  shape_type type;
  union {
    rect rectangle;
    circ circle;
  };
  int l_cnt;
  line lines[];
} shape;

void input_error() {
  printf("Input error\n");
  exit(0);
}

shape *init_shape(shape_type fig_type, shape *prev_fig) {
  // printf("Init_shape\n");
  shape *figure = (shape *)malloc(sizeof(shape) + LINE_LIMIT * sizeof(line));
  assert(figure != NULL);
  if (prev_fig != NULL)
    figure =
        memcpy(figure, prev_fig, sizeof(shape) + LINE_LIMIT * sizeof(line));

  figure->type = fig_type;
  // printf("Init_shape_end\n");
  return figure;
}

void read_circle(shape *figures[], int k) {
  // printf("Read_circle\n");
  circ rc;
  if (scanf("%lf %lf %lf", &rc.x, &rc.y, &rc.r) != 3)
    input_error();

  figures[k] = init_shape(CIRCLE, NULL);
  figures[k]->circle = rc;
  // printf("Read_circle_end %d\n", k);
}

void read_rectangle(shape *figures[], int k) {
  // printf("Read_rectangle\n");
  rect rr;
  if (scanf("%lf %lf %lf %lf", &rr.x1, &rr.y1, &rr.x2, &rr.y2) != 4)
    input_error();

  figures[k] = init_shape(RECTANGLE, NULL);
  figures[k]->rectangle = rr;
  // printf("Read_rectangle_end %d\n", k);
}

void read_line(shape *figures[], int k) {
  line rl;
  int idx;
  if (scanf("%d %lf %lf %lf %lf", &idx, &rl.x1, &rl.y1, &rl.x2, &rl.y2) != 5)
    input_error();
  assert(1 <= idx && idx < k);
  shape *prev_fig = figures[idx];
  figures[k] = init_shape(prev_fig->type, prev_fig);
  int cnt = prev_fig->l_cnt;
  figures[k]->lines[cnt] = rl;
  figures[k]->l_cnt = cnt + 1;

  // print_shape(figures[idx]);
}

typedef void (*read_object)(shape **, int);

void read_data(shape *figures[], int n) {
  for (int i = 1; i <= n; ++i) {
    char object_type;
    if (scanf("\n%c", &object_type) != 1)
      input_error();
    assert((object_type == 'P' || object_type == 'K') || object_type == 'Z');

    read_object read_func[256] = {NULL};
    read_func['P'] = read_rectangle;
    read_func['K'] = read_circle;
    read_func['Z'] = read_line;

    if (read_func[(unsigned char)object_type] == NULL)
      input_error();
    read_func[(unsigned char)object_type](figures, i);
  }
}
double dist(point A, point B) {
  return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
}

int is_inside(shape *figure, double x, double y) {
  //printf("Sprawdzamy punkt (%lf, %lf): ", x, y);
  if (figure->type == CIRCLE) {
    circ fc = figure->circle;
   // printf("Czy jest: %d\n", dist((point){x, y}, (point){fc.x, fc.y}) <= fc.r * fc.r);
    return dist((point){x, y}, (point){fc.x, fc.y}) <= fc.r * fc.r + ZERO;
  }
  rect fr = figure->rectangle;
  return (fr.x1 <= x + ZERO && x <= fr.x2 +ZERO && fr.y1 <= y + ZERO && y <= fr.y2 + ZERO);
}

point reflect(point P, line L) {
  //printf("Prosta: (%lf, %lf) , (%lf, %lf)\n", L.x1, L.y1, L.x2, L.y2);
  double dx = L.x2 - L.x1, dy = L.y2 - L.y1, a = dy, b = -dx,
         c = dx * L.y1 - dy * L.x1;
  double d = (a * P.x + b * P.y + c) / (a * a + b * b);
  //printf("Odbicie punktu (%lf, %lf): (%lf, %lf)\n", P.x, P.y, P.x - 2 * a * d, P.y - 2 * b * d);
  return (point){P.x - 2 * a * d, P.y - 2 * b * d};
}

int proper_side(point P, line L) {
  double cross_product =
      (L.x2 - L.x1) * (P.y - L.y1) - (L.y2 - L.y1) * (P.x - L.x1);

  //printf("Cross product: %lf\n", cross_product);
  if (cross_product > ZERO){
    //printf("Croos > 0\n");
    return 1; // prawa strona
  }
  if (cross_product < -ZERO){
    //printf("Cross < 0\n");
    return -1; // lewa strona
  }
  //printf("Na prostej\n");
  return 0;    // na prostej
}

int rec(shape *figure, double x, double y, int l_ix) {
  if (l_ix < 0)
    return (is_inside(figure, x, y));

  line our_line = figure->lines[l_ix];
  point p = reflect((point){x, y}, our_line);
  if (proper_side((point){x, y}, our_line) == 1)
    return rec(figure, x, y, l_ix - 1) + rec(figure, p.x, p.y, l_ix - 1);

  else if (proper_side((point){x, y}, our_line) == 0){
    return (rec(figure, x, y, l_ix - 1));
  }

  return 0; // if proper_side(x, y, our_line) == -1
}

void solve() {
  int n, q;
  if (scanf("%d %d", &n, &q) != 2)
    input_error();

  shape **figures = (shape **)malloc((unsigned)(n + 1) * sizeof(shape *));
  assert(figures != NULL);
  for (int i = 0; i <= n; i++)
    figures[i] = NULL;

  read_data(figures, n);

  for (int i = 0; i < q; ++i) {
    int k;
    double x, y;
    if (scanf("%d %lf %lf", &k, &x, &y) != 3)
      input_error();

    // printf("K: %d\n", k);
    assert(figures[k] != NULL);
    printf("%d\n", rec(figures[k], x, y, figures[k]->l_cnt - 1));
  }
  for (int i = 0; i <= n; i++)
    free(figures[i]);
  free(figures);
}

int main() {
  solve();
  return 0;
}