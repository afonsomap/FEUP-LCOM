#include <stdlib.h>
#include <stdio.h>

void print_all_bits(int n){
  for (int i=31; i>=0; i--) {
    printf("%d",(n >> i) & 1);
  }
  printf("\n");
}

int main(){
  int n = 12;
  print_all_bits(n);
  n = 2104;
  print_all_bits(n);
  n = 1;
  print_all_bits(n);
  n = -5;
  print_all_bits(n);
  n = 130493076;
  print_all_bits(n);
  return 0;
}