#include <stdio.h>

int Digitos (int N){
  int cont = 1;

  if(N >= 10){
    N = N /10;
    cont = cont + Digitos(N);
  }

  return cont;
}

int main() {
  int numero;
  printf("Digite um numero inteiro: ");
  scanf("%d", &numero);
  printf("Resultado: %d ", Digitos(numero));
  return 0;
}
