/****************

LAED1 - Projeto (Parte I) - Busca por padrão em lista

Alunos(as): Julio Cesar Rocha e Pablo Felipe 

Data: 28/10/2020

****************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INICIOARRANJO   1
#define MAXTAM          1000

typedef int TipoChave;

typedef int TipoApontador;

typedef struct {
  TipoChave Chave;
  /* outros componentes */
} TipoItem;

typedef struct {
  TipoItem Item[MAXTAM];
  TipoApontador Primeiro, Ultimo;
} TipoLista;

int vetorResposta[5] = {1, 3, 2, 3, 1};

int procuraResposta(TipoLista Lista){
	int Aux;
	int s = 0;	
	for (Aux = Lista.Primeiro; Aux <= (Lista.Ultimo - 1); Aux++){
		if(Lista.Item[Aux].Chave == vetorResposta[s]){
			if(Lista.Item[Aux+1].Chave == vetorResposta[s+1]){
				if(Lista.Item[Aux+2].Chave == vetorResposta[s+2]){
					if(Lista.Item[Aux+3].Chave == vetorResposta[s+3]){
						if(Lista.Item[Aux+4].Chave == vetorResposta[s+4]){
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;    
}

void Insere(TipoItem x, TipoLista *Lista){
	if (Lista -> Ultimo > MAXTAM) printf("Lista esta cheia\n");
  	else {
	  	Lista -> Item[Lista -> Ultimo] = x;
        Lista -> Ultimo++;
    }
}

void Imprime(TipoLista Lista){
	int Aux;
	for (Aux = Lista.Primeiro; Aux <= (Lista.Ultimo - 1); Aux++)
    printf("%d\n", Lista.Item[Aux].Chave);
}

int procuraSegmento(int i, int tamNaoRepetidos, int *vetorValores, int *vetorNaoRepetidos){
	int j;
	for(j = 0; j <= tamNaoRepetidos; j++){
		if(vetorNaoRepetidos[j] == vetorValores[i]){
			return (j+1);
		}
	}
	return 0;
}

int main(){
	FILE *file;
	char fileName[30];
	int qtdeElementos; 			//Variavel para guardar a quantidade N de elementos do vetor
	char string[100000];		//Variavel para guardar leitura do arquivo

	printf("Digite o nome do arquivo: ");
    scanf("%s",fileName);

	file = fopen(fileName,"r+"); //Abre arquivo para leitura
	if(file == NULL){
	    printf("*** FALHA AO ABRIR ARQUIVO ***");
	    return 0;
	}

	//Lendo a 1a linha do arquivo de texto. (Quantidade de elementos N do vetor)
	fgets(string, 100000, file);
	qtdeElementos = atoi(string);

	//Token utilizado para leitura e identificaï¿½ï¿½o do espaï¿½amento entre valores do arquivo ".txt"
	char* token;
	int i = 0;
	int elementoZero;

	fgets(string, 100000, file);
	token = strtok(string, " ");
	elementoZero = atoi(token);
	//printf("\n %d", elementoZero);

	//Vetor com todos os valores do array do arquivo ".txt"
	int *vetorValores = (int*) malloc( 1 * sizeof(int));
	vetorValores[0] = elementoZero;
   	for(i = 1; i < qtdeElementos; i++){
	    vetorValores = (int*) realloc(vetorValores, (i + 1) * sizeof(int));
	    token = strtok(NULL, " ");
	    vetorValores[i] = atoi(token);
	}

	//Vetor criado para armazenar valores do array lido anteriormente, porem sem repetiï¿½ï¿½o de nï¿½meros
	int *vetorNaoRepetidos;
	vetorNaoRepetidos = (int*) malloc(1 * sizeof(int));
	vetorNaoRepetidos[0] = elementoZero;

	int tamNaoRepetidos = 0;
	int j;
	int repetido = 0;

	for(i = 0; i < qtdeElementos; i++){
		repetido = 0;
		for(j = 0; j <= tamNaoRepetidos; j++){
			if(vetorValores[i] == vetorNaoRepetidos[j]){
				repetido++;
			}
		}
		if(repetido == 0){	//Se o valor nï¿½o foi encontrado no vetor de nï¿½meros sem repetiï¿½ï¿½es, entï¿½o esse valor ï¿½ salvo no vetor "vetorNaoRepetidos"
			tamNaoRepetidos++;
			vetorNaoRepetidos = (int*) realloc(vetorNaoRepetidos, (tamNaoRepetidos + 1)* sizeof(int));
			vetorNaoRepetidos[tamNaoRepetidos] = vetorValores[i];
		}
	}

	//Ordenando de forma crescente o vetor sem numeros repetidos (vetorNaoRepetidos)
	int aux;
	for(i = 0; i <= tamNaoRepetidos; i++){
		for(j = 0; j <= tamNaoRepetidos; j++){
			if(vetorNaoRepetidos[i] < vetorNaoRepetidos[j]){
				aux = vetorNaoRepetidos[i];
                vetorNaoRepetidos[i] = vetorNaoRepetidos[j];
                vetorNaoRepetidos[j] = aux;
			}
		}
	}
	

	int k = 0;
	int segmentoAtual = 0;

	int **matrizFinal;
	//Alocando para 2 linhas
	matrizFinal = (int**) malloc(2 * sizeof(int*));

	// No ambiente de programaï¿½ï¿½o Linux compilado com gcc, declarando um vetor de tamanho 5 como:
	// int vetor[5]
	// todo o valor apï¿½s a ultima posiï¿½ï¿½o do vetor, serï¿½ 0
	// com isso, estava tendo erro ao compilar no run.codes / linux
	// Pois chegando em: vetor[4] ao comparar com vetor[5], caso o vetor[4] fosse 0, o
	// programa teria uma interpretaï¿½ï¿½o errada, nï¿½o reconhecendo o fim do segmento que terminava com 0 na ultima posiï¿½ï¿½o do vetor...
	// Adicionando um numero aleatorio diferente de 0 na ultima posiï¿½ï¿½o + 1 do vetor
	// O cï¿½digo passa a funcionar para 4 dos 5 testes.
	int aleatorio = 0;

	// Por exemplo, para o caso de "teste3.txt", se o vetor[680] for igual 0
	// o ultimo segmento (de valor 0) nï¿½o serï¿½ levado em consideraï¿½ï¿½o
	// resultando em uma coluna a menos
	// mas o "for" abaixo, varre os valores que estï¿½o no vetor e compara se o valor aleatorio (no caso 0)
	// ï¿½ igual ï¿½ um valor que estï¿½ no vetor, se sim, entï¿½o ï¿½ somado 1 na variavel "aleatorio"
	// e o loop for ï¿½ reiniciado.
	// Caso comente o "for" abaixo poderï¿½ perceber que o programa funcionarï¿½ apenas para o caso 1

	for(i = 0; i <= tamNaoRepetidos; i++){
		if(vetorNaoRepetidos[i] == aleatorio){
			aleatorio++;
			i = -1;
		}
	}

	// Durante o desenvolvimento percebi que isto ocorria apenas no linux compilando com o "gcc"
	// Programando pelo Windows usando a IDE "Dev C++" o erro nï¿½o ocorria.

	vetorValores[qtdeElementos] = aleatorio;

	//Contar quantas colunas terÃ¡ a matriz
	for(i = 0; i < qtdeElementos; i++){
		//printf("\n %d == %d | %d",vetorValores[i], vetorValores[i+1], i);
		if(vetorValores[i] != vetorValores[i+1]){
			k++;
		}
	}

	//Alocando cada uma das linhas da matriz
	for(i = 0; i < 2; i++){
		matrizFinal[i] = (int*) malloc(k * sizeof(int));
	}

	int posicao = 0;

	//Preenchendo a primeira linha da matriz
	for(i = 0; i < qtdeElementos; i++){
		if(vetorValores[i] != vetorValores[i+1]){
			segmentoAtual = procuraSegmento(i, tamNaoRepetidos, vetorValores, vetorNaoRepetidos);
			matrizFinal[0][posicao] = segmentoAtual;
			//printf(" %d ", matrizFinal[0][posicao]);
			posicao++;
		}
	}

	int contador = 0;
	k = 0;

	//Armazenamento do valor de "numeros de elementos"
	for(i = 0; i <= qtdeElementos; i++){
		contador++;
		if(vetorValores[i] != vetorValores[i+1]){
			matrizFinal[1][k] = contador;
			contador = 0;
			k++;
		}
	}

	 /*
	printf("Matriz:\n");
	for(i = 0; i < 2; i++){
		for(j = 0; j < k - 1; j++){
				printf("%d ",matrizFinal[i][j]);
		}
		if(i == 0)
			printf("\n");
	}
	
	printf("\n\n");
	*/
	TipoLista lista;
	 TipoItem item;
	// * Criaï¿½ï¿½o da lista *
	for (i = 0; i < 2; i++){
		for(j = 0; j < k - 1; j++){
		  item.Chave = matrizFinal[i][j];
	      Insere(item, &lista);
	//      printf("Inseriu: %d \n", item.Chave);
	  }
	}
	
	
	if(procuraResposta(lista)){
		printf("Resultado: Padrao encontrado.");
	}
	else{
		printf("Resultado: Padrao nao encontrado.");
	}
	return 0;
}
