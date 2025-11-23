typedef struct {double x1, y1, x2, y2;} rect;

typedef struct {double x, y, r; } circ;

typedef enum { RECTANGLE, CIRCLE } shape_type;

typedef struct { double x1, y1, x2, y2; } line;

typedef struct {double x, y;} point;

typedef struct {
    shape_type type;
    union {
        rect rectangle;
        circ circle;
    };
    int l_cnt;
    line lines[];
} shape;

void print_shape(const shape* figure);
