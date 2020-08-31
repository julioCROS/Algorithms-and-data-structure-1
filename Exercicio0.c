/*
////////////////////////////////////////
Exercício 0 : 
Faça um programa que receba dois números da entrada padrão e imprima a soma deles.
Para fazer a leitura dos números, o programa deverá imprimir na tela uma mensagem com o seguinte comando:
printf("Digite os dois numeros: ");
Após a leitura, o programa deverá somar os números e imprimir a resposta. A saída do programa deve seguir o modelo abaixo, considerando como entrada os números 10 e 5:
///////////////////////////////////////
*/
  
#include <stdio.h>
int main() {
  int num1, num2, soma;
  printf("Digite os dois numeros: ");
  scanf("%d %d", &num1, &num2);
  soma = num1 + num2;
  printf("Resultado = %d \n", soma);
}
