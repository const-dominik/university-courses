#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum typfig {
    TRIANGLE,
    CIRCLE,
    SQUARE
};

typedef struct {
    float x;
    float y;
    float a;
    float b;
    float c;
    enum typfig type;
} Figura;

Figura* new_square(float x, float y, float side)
{
    if (side < 0)
    {
        fprintf(stderr, "długość boku nie może być ujemna");
        exit(EXIT_FAILURE);
    }
    Figura* shape = malloc(sizeof(Figura));
    shape->x = x;
    shape->y = y;
    shape->a = side;
    shape->type = SQUARE;
    return shape;
}

Figura* new_triangle(float x, float y, float a, float b, float c)
{
    if (a < 0 || b < 0 || c < 0)
    {
        fprintf(stderr, "długość boku nie może być ujemna");
        exit(EXIT_FAILURE);
    }
    float longest = fmax(fmax(a, b), c);
    if (longest >= a + b + c - longest)
    {
        fprintf(stderr, "najdłuższy bok trójkąta musi być krótszy niż suma długości dwóch pozostałych boków");
        exit(EXIT_FAILURE);
    }
    Figura* shape = malloc(sizeof(Figura));
    shape->x = x;
    shape->y = y;
    shape->a = a;
    shape->b = b;
    shape->c = c;
    shape->type = TRIANGLE;
    return shape;
}

Figura* new_circle(float x, float y, float r)
{
    if (r < 0)
    {
        fprintf(stderr, "promień nie może być ujemny");
        exit(EXIT_FAILURE);
    }
    Figura* shape = malloc(sizeof(Figura));
    shape->x = x;
    shape->y = y;
    shape->a = r;
    shape->type = CIRCLE;
    return shape;
}

float area(Figura *f)
{
    enum typfig type = f->type;
    float shape_area = 0;
    if (type == SQUARE)
    {
        shape_area = f->a*f->a;
    }
    if (type == TRIANGLE)
    {
        float p = (f->a+f->b+f->c)/2;
        shape_area = sqrt(p*(p-f->a)*(p-f->b)*(p-f->c));
    }
    if (type == CIRCLE)
        shape_area = f->a*f->a*3.14;
    return shape_area;
}

void move(Figura *f, float x, float y)
{
    f->x += x;
    f->y += y;
}

void show(Figura *f)
{
    printf("Położenie: (%.2f, %.2f), typ: ", f->x, f->y);
    if (f->type == TRIANGLE) printf("trójkąt, długości boków: %.2f %.2f %.2f\n", f->a, f->b, f->c);
    if (f->type == CIRCLE) printf("koło, długość promienia: %.2f\n", f->a);
    if (f->type == SQUARE) printf("kwadrat, długość boku: %.2f\n", f->a);
}

float sum_of_areas(Figura* f[], int size)
{
    float sum = 0;
    for (int i = 0; i < size; i++) sum += area(f[i]);
    return sum;
}
