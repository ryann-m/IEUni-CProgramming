#ifndef MYRECTANGLE_H
#define MYRECTANGLE_H

typedef struct {
    // Attributes of Rectangle
    int length;
    int width;
} Rectangle;

int area(Rectangle r);

void grow(Rectangle *r, int dw, int dl);

int invalidCounter(int *invalidCount);

#endif // MYRECTANGLE_H