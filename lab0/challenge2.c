#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void) {
  char line[64];
  char cmd[10];
  unsigned int op1, op2;
  unsigned int bitpos, bytepos;
  printf("Write a command:\n");
  while (fgets(line, sizeof(line), stdin) != NULL) {
    //Sair do programa se pressionar enter sem nada
    if (sscanf(line, "%s", cmd) != 1) {
        break;
    }
    //Operação and
    if (strcmp(cmd, "and") == 0) {
      if (sscanf(line, "%*s %u %u", &op1, &op2) == 2) { //%*s descarta a primeira palavra, o "and"
        printf("%u\n", op1 & op2);
      }
    } //Operação or
    else if (strcmp(cmd, "or") == 0) {
      if (sscanf(line, "%*s %u %u", &op1, &op2) == 2) {
        printf("%u\n", op1 | op2);
      } 
    } //Operação set
    else if (strcmp(cmd, "set") == 0) {
      if (sscanf(line, "%*s %u %u", &op1, &bitpos) == 2) {
        op1 |= (1 << bitpos);
        printf("%u\n", op1);
      } 
    } //Operação unset
    else if (strcmp(cmd, "unset") == 0) {
      if (sscanf(line, "%*s %u %u", &op1, &bitpos) == 2) {
        op1 &= ~(1 << bitpos);
        printf("%u\n", op1);
      } 
    } //Operação byte
    else if (strcmp(cmd, "byte") == 0) {
      if (sscanf(line, "%*s %u %u", &op1, &bytepos) == 2) {
        unsigned int byte = (op1 >> (8 * bytepos)) & 0xFF; // 8 porque cada byte são 8 bits
        printf("%u\n", byte);                              // FF para ir buscar os últimos 8 bits
      }
    }
  }
  return 0;
}