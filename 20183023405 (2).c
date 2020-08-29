#include <stdio.h>

void dec2bin(int dec){
  int novoNumero = 0;
  int divisao = 0;

  if(dec >= 1){
    novoNumero = dec/2;
    divisao = dec%2;
    dec2bin(novoNumero);
    printf("%d", divisao);
  }

}

int main(){
  int dec;
  printf("Digite um numero inteiro: ");
  scanf("%d", &dec);
  printf("Resultado: ");
  if(dec != 0)
  dec2bin(dec);
  else{
    printf("0");
  }

    printf("\n");
}
