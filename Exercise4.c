#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE* arquivo;
    char arquivoNOME[20];
    char textoCodificado[2000];
    char str[2000];
    printf("Digite o nome do arquivo: ");
    scanf("%s", arquivoNOME);

    arquivo = fopen(arquivoNOME,"r+");
    if(!arquivo){
      printf("Falha ao abrir o arquivo");
      return 0;
    }
    fgets(str, 200, arquivo);
    strcpy(textoCodificado,str);

    printf("\n--------------------");
    printf("\nMensagem codificada:");
    printf("\n--------------------");
    printf("\n%s\n", textoCodificado);

    char caractere;
    int qntdeLetras = 0;

    rewind(arquivo);
    do{
        caractere = getc(arquivo);
        qntdeLetras++;
    }while(caractere != EOF);

    qntdeLetras--;

    //Re-aplicando a cifra de Cesar de modo inverso, para se voltar ao original
    for(int i = 0; i < qntdeLetras; i++){
        if(textoCodificado[i] != '#'){
            if(textoCodificado[i] == 'a'){
                textoCodificado[i] = 'x';
            }
            else if(textoCodificado[i] == 'A'){
                textoCodificado[i] = 'X';
            }

            else if(textoCodificado[i] == 'b'){
                textoCodificado[i] = 'y';
            }
            else if(textoCodificado[i] == 'B'){
                textoCodificado[i] = 'Y';
            }

            else if(textoCodificado[i] == 'c'){
                textoCodificado[i] = 'z';
            }
            else if(textoCodificado[i] == 'C'){
                textoCodificado[i] = 'Z';
            }

            else{
                textoCodificado[i] = textoCodificado[i] - 3;
            }
        }
    }


    //Fazendo a reflexão de cada bloco (2 letras)
    char aux;
    for(int i = 0; i < qntdeLetras; i = i + 2){
        aux = textoCodificado[i];
        textoCodificado[i] = textoCodificado[i+1];
        textoCodificado[i+1] = aux;
    }

    //Permutação dos "blocos",
    qntdeLetras--;
    qntdeLetras--;
    char aux1;
    char aux2;
    int j = qntdeLetras;


    for(int i = 0; i < qntdeLetras/2; i = i + 4){
      aux1 = textoCodificado[i];
      aux2 = textoCodificado[i+1];

      textoCodificado[i] = textoCodificado[j - 1];
      textoCodificado[i + 1] = textoCodificado[j];

      textoCodificado[j] = aux2;
      textoCodificado[j-1] = aux1;
      j = j - 4;
    }


    //Substituindo # por [ESPAÇO]
    for(int i = 0; i < qntdeLetras; i++){
        if(textoCodificado[i] == '#'){
            textoCodificado[i] = ' ';
        }
    }

    printf("----------------------");
    printf("\nMensagem decodificada:");
    printf("\n----------------------");
    printf("\n%s",textoCodificado);

}
