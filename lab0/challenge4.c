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

Plane *new_plane(int w, int h) {
  Plane *p = malloc(sizeof(Plane));
  p->w = w;
  p->h = h;
  return p;
}

Volume *new_volume(Plane *p, int d) {
  Volume *v = malloc(sizeof(Volume));
  v->base.w = p->w;
  v->base.h = p->h;
  v->d = d;
  return v;
}

void print_plane(Plane *p) {
  printf("W %d, H %d\n", p->w, p->h);
}

void print_volume(Volume *v) {
  printf("W %d, H %d, D %d\n", v->base.w, v->base.h, v->d);
}

int main(){
  Plane* a = new_plane(5,5);
  Plane* b = new_plane(2,3);
  Volume* c = new_volume(b,4);
  print_plane(a);
  print_plane(b);
  print_volume(c);
  free(a);
  free(b);
  free(c);
}