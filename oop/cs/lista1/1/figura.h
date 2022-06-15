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

Figura* new_square(float x, float y, float side);
Figura* new_triangle(float x, float y, float a, float b, float c);
Figura* new_circle(float x, float y, float r);
float area(Figura *f);
void move(Figura *f, float x, float y);
void show(Figura *f);
float sum_of_areas(Figura* f[], int size);
