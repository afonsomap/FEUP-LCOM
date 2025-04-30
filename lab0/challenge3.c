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

Plane* create_plane() {
  Plane* plane = (Plane*)malloc(sizeof(Plane));
  plane->h=2;
  plane->w=1;
  return plane;
}

int main() {
  Plane* plane = create_plane();
  printf("Width is %d", plane->w);
  free(plane);
  return 0;
}