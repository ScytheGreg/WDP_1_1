// Solution for "Origami" task. Grzegorz Kaczmarek
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned FIGURE_LIMIT = 1e5;
const unsigned LINE_LIMIT = 22;
const double ZERO = 1e-6; // Accepted calculation accuracy

typedef struct {
  double x, y;
} point;

typedef struct {
  point p1, p2;
} rect; // Rectangle

typedef struct {
  point p;  // Center
  double r; // Radius
} circ;     // Circle

typedef enum { RECTANGLE, CIRCLE } shape_type;

typedef struct {
  point p1, p2;
} line;

typedef struct {
  shape_type type;
  union {
    rect rectangle;
    circ circle;
  };
  int l_cnt;
  line lines[];
} shape; // Shape consists of a figure and batch of lines, along which figure
         // was creased

void input_error() {
  printf("Input error\n");
  exit(0);
}

// Allocates memory for new figure. If it is formed form existing sheet, copies
// all elements
shape *init_shape(shape_type fig_type, shape *prev_fig) {
  shape *figure = (shape *)malloc(sizeof(shape) + LINE_LIMIT * sizeof(line));
  assert(figure != NULL);
  if (prev_fig != NULL)
    figure =
        memcpy(figure, prev_fig, sizeof(shape) + LINE_LIMIT * sizeof(line));

  figure->type = fig_type; // Attribute type of figure.
  return figure;
}

// Reads a circle data, creates a sheet
void read_circle(shape *figures[], int k) {
  circ rc;
  if (scanf("%lf %lf %lf", &rc.p.x, &rc.p.y, &rc.r) != 3)
    input_error();

  figures[k] = init_shape(CIRCLE, NULL);
  figures[k]->circle = rc;
}

// Reads a rectangle data, creates a sheet
void read_rectangle(shape *figures[], int k) {
  rect rr;
  if (scanf("%lf %lf %lf %lf", &rr.p1.x, &rr.p1.y, &rr.p2.x, &rr.p2.y) != 4)
    input_error();

  figures[k] = init_shape(RECTANGLE, NULL);
  figures[k]->rectangle = rr;
}

// Reads crease data, creates copy of a sheet with new crease
void read_line(shape *figures[], int k) {
  line rl;
  int idx;
  if (scanf("%d %lf %lf %lf %lf", &idx, &rl.p1.x, &rl.p1.y, &rl.p2.x,
            &rl.p2.y) != 5)
    input_error();
  assert(1 <= idx && idx < k);
  shape *prev_fig = figures[idx];                    // Get dependent figure
  figures[k] = init_shape(prev_fig->type, prev_fig); // Copy it
  int cnt = prev_fig->l_cnt;
  figures[k]->lines[cnt] = rl; // Update lines
  figures[k]->l_cnt = cnt + 1;
}

typedef void (*read_object)(shape **, int);

// Reads figures data
void read_data(shape *figures[], int n) {
  for (int i = 1; i <= n; ++i) {
    char object_type;
    if (scanf("\n%c", &object_type) != 1)
      input_error();
    assert(object_type == 'P' || object_type == 'K' || object_type == 'Z');

    read_object read_func[256] = {NULL}; // Table of functions for every char
    read_func['P'] = read_rectangle;
    read_func['K'] = read_circle;
    read_func['Z'] = read_line;

    if (read_func[(unsigned char)object_type] == NULL)
      input_error();
    read_func[(unsigned char)object_type](
        figures, i); // For given char execute respective function.
  }
}

// Calculates distance form A to B
double dist(point A, point B) {
  return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
}

// Checks whether the point is inside a figure
int is_inside(shape *figure, double x, double y) {
  if (figure->type == CIRCLE) {
    circ fc = figure->circle;
    return dist((point){x, y}, (point){fc.p.x, fc.p.y}) <= fc.r * fc.r + ZERO;
  }
  rect fr = figure->rectangle;
  return (fr.p1.x <= x + ZERO && x <= fr.p2.x + ZERO && fr.p1.y <= y + ZERO &&
          y <= fr.p2.y + ZERO);
}

// Return reflected point to P by line L
point reflect(point P, line L) {
  double dx = L.p2.x - L.p1.x, dy = L.p2.y - L.p1.y, a = dy, b = -dx,
         c = dx * L.p1.y - dy * L.p1.x;
  double d = (a * P.x + b * P.y + c) / (a * a + b * b);
  return (point){P.x - 2 * a * d, P.y - 2 * b * d};
}

// Checks whether a point lies on the left (-1) or right (1) side of a line or
// on the line (0)
int proper_side(point P, line L) {
  double cross_product =
      (L.p2.x - L.p1.x) * (P.y - L.p1.y) - (L.p2.y - L.p1.y) * (P.x - L.p1.x);

  if (cross_product > ZERO)
    return 1; // Right side

  if (cross_product < -ZERO)
    return -1; // Left side

  return 0; // On the line
}

// Recursion function. Returns number of layers under given point after l_ix
// crease
int rec(shape *figure, double x, double y, int l_ix) {
  if (l_ix < 0) // If no more lines, just return whether it belongs
    return (is_inside(figure, x, y));

  line our_line = figure->lines[l_ix];
  point p = reflect((point){x, y}, our_line);
  if (proper_side((point){x, y}, our_line) ==
      1) // Trigger function from this point and it's reflection
    return rec(figure, x, y, l_ix - 1) + rec(figure, p.x, p.y, l_ix - 1);

  else if (proper_side((point){x, y}, our_line) ==
           0) { // If lies on the line trigger just from this point
    return (rec(figure, x, y, l_ix - 1));
  }

  return 0; // If lies on bad side of the line, just return 0
}

// Main function pinning whole solution
void solve() {
  int n, q;
  if (scanf("%d %d", &n, &q) != 2)
    input_error();

  shape **figures = (shape **)malloc((unsigned)(n + 1) *
                                     sizeof(shape *)); // Main table of figures
  assert(figures != NULL);
  for (int i = 0; i <= n; i++) // Set every pointer to null
    figures[i] = NULL;

  read_data(figures, n);

  for (int i = 0; i < q; ++i) { // Answering enquirers
    int k;
    double x, y;
    if (scanf("%d %lf %lf", &k, &x, &y) != 3)
      input_error();

    assert(figures[k] != NULL);
    printf("%d\n", rec(figures[k], x, y, figures[k]->l_cnt - 1));
  }

  for (int i = 0; i <= n; i++) // Clean works
    free(figures[i]);
  free(figures);
}

int main() {
  solve();
  return 0;
}