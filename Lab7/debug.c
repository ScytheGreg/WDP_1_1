#include <stdlib.h>
#include <stdio.h>
#include "debug.h"
void print_shape(const shape* figure) {
    if (figure == NULL) {
        printf("NULL shape\n");
        return; 
    }

    switch (figure->type) {
        case RECTANGLE:
            printf("Rectangle: ");
            printf("(%.2f, %.2f) to (%.2f, %.2f)\n",
                   figure->rectangle.x1, figure->rectangle.y1,
                   figure->rectangle.x2, figure->rectangle.y2);
            break;

        case CIRCLE:
            printf("Circle: ");
            printf("center (%.2f, %.2f), radius %.2f\n",
                   figure->circle.x, figure->circle.y,
                   figure->circle.r);
            break;

        default:
            printf("Unknown shape type: %d\n", figure->type);
            return;
    }

    // Wypisanie linii jeśli istnieją
    printf("  Lines count: %d\n", figure->l_cnt);
    for (int i = 0; i < figure->l_cnt; i++) {
        printf("  Line %d: (%.2f, %.2f) to (%.2f, %.2f)\n", i,
               figure->lines[i].x1, figure->lines[i].y1,
               figure->lines[i].x2, figure->lines[i].y2);
    }
    printf("\n");
}