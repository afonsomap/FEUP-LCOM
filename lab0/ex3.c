#include <stdlib.h>
#include <stdio.h>

#define BIT(n) (1 << (n))

int main() {

  int n = 0;
  printf("n=%d\n", n);

  //OR
  n = n | 1;
  printf("n|1=%d\n", n);

  //XOR e soma
  printf("0b101^0b10=%d\n", 0b101^0b10);
  printf("0xF+1=%d\n", 0xF+1);

  //Representação em hexadecimal é mostrada no terminal como decimal
  int k = 0xE;
  printf("k=%d\n", k);

  //Dar print apenas ao 4º bit (bit 3 porque começa em 0)
  printf("Bit 3 of k is %d\n", (k >> 3) & 1);
  printf("Bit 3 of k is %d\n", (k & 0b1000) >> 3);

  k |= (1 << 3); //Colocar o 4º bit a 1
  printf("k=%d\n", k);

  k &= ~(1 << 3); //Colocar o 4º bit a 0
  printf("k=%d\n", k);

  //Usar uma bitmask torna as operações mais claras
  k |= BIT(3); //Colocar 4ªbit a 1
  k &= ~BIT(3); //Colocar 4ªbit a 0
  if (k & BIT(3)){} //Verificar se o 4º bit é 1

  //Negativos são representados em complemento de 2
  n = -1;
  printf("n=%d\n", n);
  printf("~n=%d\n", ~n);

  //Shift à direita em negativos coloca 1 no bit mais significativo ficando negativo na mesma
  printf("n>>1=%d\n", n>>1); 
  //Shift à esquerda já coloca 0 pois não influencia no sinal
  printf("n<<1=%d\n", n<<1);
  
  printf("(((unsigned int)n)>>1=%d\n", (((unsigned int)n)>>1));
  printf("(((unsigned int)n)<<1=%d\n", (((unsigned int)n)<<1));

  return 0;
}
