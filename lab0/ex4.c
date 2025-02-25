#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  int w, h; // width, height
} Plane;

typedef struct {
  Plane base;
  int d; // depth
} Volume;

typedef union {
  int i;
  char c[10];
  Plane p;
} Mix;

void print_plane(Plane *p) {
  printf("W %d, H %d\n", p->w, p->h);
}

void print_volume(Volume *v) {
  printf("W %d, H %d, D %d\n", v->base.w, v->base.h, v->d);
}

int main() {
  Plane p = {5, 2};
  Volume v = {p, 3};
  print_plane(&p);
  print_plane((Plane *) &v);
  print_volume(&v);

  // Unions reservam o espaço necessário para guardar o maior elemento, permitindo no mesmo espaço de memória guardos dados diferentes, escrever numa union apaga os dados que estavam lá
  printf("sizeof(Mix)=%lu\n", sizeof(Mix));

  Mix m;
  m.p.h = 3;
  m.p.w = 5;
   
  //A union está a guardar o plane, como o i é um inteiro e a union está a guardar um inteiro no plane, o i corresponte à width
  printf("m.i=%d\n", m.i);

  //O plane continua acessivel, pois ele continua a ser o dado guardado na union
  print_plane(&m.p);

  //A union pode também guardar uma string, tendo o plane sido apagado
  strcpy(m.c, "Hello!\n");
  printf("%s", m.c); // %s - string
  
  return 0;
}