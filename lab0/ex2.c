#include <stdlib.h>
#include <stdio.h>

void print_array(int *p, int n) {
  for (int i = 0; i < n; i++){
    printf("%d ", p[i]);
    printf("\n");
  }
}

int main() {

  int n = 5;
  int *p = &n; // pointer para a posição de memória onde está guardado o n
  printf("n=%d\n", n); // %d - inteiros 
  printf("p=%d\n", *p);

  int **pp = &p; //pointer para a posição da memória do pointer p
  printf("p=%u\n", p); // %u - inteiros sem sinal
  printf("*pp=%u\n", *pp); //valor do pointer pp que é a posição de memória do pointer p

  int s[100] = { 0 };  //Array estático, inicializado a 0s
  int *d = malloc(100 * sizeof(int)); //Array dinâmico
  memset(d, 0, 100); //Inicializar a 0s o array dinâmico

  s[1] = 1;
  printf("s[0]=%d\n", s[0]);
  printf("*s=%d\n", *s);
  printf("s[1]=%d\n", s[1]);
  printf("*(s+1)=%d\n", *(s+1)); //Podemos somar e subtrair aos pointers para avançar ou recuar

  printf("*p=%d\n", *p);
  printf("p[0]=%d\n", p[0]);

  printf("sizeof(s)=%u\n", sizeof(s));//S guarda a memoria para os 100 elementos em compile time
  printf("sizeof(d)=%u\n", sizeof(d));//Em compile time d ainda só tem 2 elementos guardados

  *p = 0;
  char *cp = (char *)p; //pointers podem fazer cast para pointers de outros tipos de dados
  cp[0] = 'A';
  printf("*cp=%c\n", *cp); // %c - char
  printf("*p=%d\n", *p);

  print_array(s,3);
  print_array(d,3);
  print_array(p,1);

  free(d);//Libertar memória alocada dinâmicamente
  return 0;
}