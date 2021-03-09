/****

LAED1 - Projeto (Parte III) - Estimativa do formato da pista

Alunos(as): Julio Cesar Rocha e Pablo Felipe 

Data: 04/11/2020

****************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INICIOARRANJO   1
#define MAXTAM          1000


int vetorResposta[5] = {1, 3, 2, 3, 1};
int vetorNumPassados[1000];

int valorDir = 0;
int valorEsq = 0;
int valorReto = 0;

int pontoMresultado = 0;
int pontoManterior = 0;
int pontoMatual = 0;

int posicaoPontoM = 0;
int primeiroPontoM = 0;
int ultimoPontoM = 0;

void pontoMedio(int *vetorValores, int *vetorNaoRepetidos, int qtdeElementos, int tamNaoRepetidos, int posicaoPontoM){
	int i = 0;
	int j = 0;
	int posicaoFim = 0;
	int posicaoInicio = 0;
	float pontoM = 0;
	int vetorSeg[qtdeElementos];
	

	
	for(i = 0; i < qtdeElementos; i++){
		for(j = 0; j <= tamNaoRepetidos; j++){
			if(vetorNaoRepetidos[j] == vetorValores[i]){
				vetorSeg[i] = j + 1;
			}
		}
	}
	
	for(i = 0; i < qtdeElementos; i++){
		if(vetorSeg[i] == 2){
			posicaoInicio = i;
			do{
				i++;	
			}while(vetorSeg[i] == 2);
			posicaoFim = i;
		}	
	}
	
	posicaoFim--;	
	pontoM = (posicaoInicio + posicaoFim)/2;	
	
	if(posicaoPontoM == 0){
		primeiroPontoM = pontoM;
	}else{
		ultimoPontoM = pontoM;
	}
	
}


int procuraResposta(int *matrizFinal, int tamMatriz){
	int Aux;
	int s = 0;	
	for (Aux = 0; Aux <= (tamMatriz - 1); Aux++){
		if(matrizFinal[Aux] == vetorResposta[s]){
			if(matrizFinal[Aux+1] == vetorResposta[s+1]){
				if(matrizFinal[Aux+2] == vetorResposta[s+2]){
					if(matrizFinal[Aux+3] == vetorResposta[s+3]){
						if(matrizFinal[Aux+4] == vetorResposta[s+4]){
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;    
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
	int qtdeLinhas;
	int qtdeElementos; 			//Variavel para guardar a quantidade N de elementos do vetor
	char string[10000];		//Variavel para guardar leitura do arquivo
	
	int formatoEstimado = 0;
	int formatoNaoEstimado = 0;
	float estimativaTotal = 0;
	

	printf("Digite o nome do arquivo: ");
    scanf("%s",fileName);

	file = fopen(fileName,"r+"); //Abre arquivo para leitura
	if(file == NULL){
	    printf("*** FALHA AO ABRIR ARQUIVO ***");
	    return 0;
	}

	//Lendo a 1a linha do arquivo de texto. (Quantidade de linhas)
	fgets(string, 10000, file);
	qtdeLinhas = atoi(string);
	
	int contaLinha = 0;
	
	for(contaLinha = 0; contaLinha < qtdeLinhas; contaLinha++){
		
		//Lendo a quantidade de elementos N do vetor
		fgets(string, 10000, file);
		qtdeElementos = atoi(string);
		

		//Token utilizado para leitura e identifica��o do espa�amento entre valores do arquivo ".txt"
		char* token;
		int i = 0;
		int elementoZero;
	
		fgets(string, 10000, file);
		token = strtok(string, " ");
		elementoZero = atoi(token);
		//printf("\n %d", elementoZero);
	
		//Vetor com todos os valores da linha atual
		int *vetorValores = (int*) malloc( 1 * sizeof(int));
		vetorValores[0] = elementoZero;
	   	for(i = 1; i < qtdeElementos; i++){
		    vetorValores = (int*) realloc(vetorValores, (i + 1) * sizeof(int));
		    token = strtok(NULL, " ");
		    vetorValores[i] = atoi(token);
		}
	
		//Vetor criado para armazenar valores do array lido anteriormente, porem sem repeti��o de n�meros
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
			if(repetido == 0){	//Se o valor n�o foi encontrado no vetor de n�meros sem repeti��es, ent�o esse valor � salvo no vetor "vetorNaoRepetidos"
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
		
		//Contar quantas colunas terá a matriz
		int k = 0;
		for(i = 0; i < qtdeElementos; i++){
			if(vetorValores[i] != vetorValores[i+1]){
				k++;
			}
		}
		
		int tamMatriz = k;
			
		int posicao = 0;
		int segmentoAtual = 0;
		int matrizFinal[k];
	
		//Preenchendo a primeira linha da matriz
		for(i = 0; i < qtdeElementos; i++){
			if(vetorValores[i] != vetorValores[i+1]){
				segmentoAtual = procuraSegmento(i, tamNaoRepetidos, vetorValores, vetorNaoRepetidos);
				matrizFinal[posicao] = segmentoAtual;
				posicao++;
			}
		}	
		
		if(procuraResposta(matrizFinal, tamMatriz)){
			pontoMedio(vetorValores, vetorNaoRepetidos, qtdeElementos, tamNaoRepetidos, posicaoPontoM);
			posicaoPontoM++;
			formatoEstimado++;
		}else{
			formatoNaoEstimado++;
		}		
			
	}
	
	estimativaTotal = (float)formatoEstimado/(float)(formatoEstimado + formatoNaoEstimado);
	
//	printf("1. %d L. %d  | %d \n", primeiroPontoM, ultimoPontoM,(primeiroPontoM - ultimoPontoM));
	
	if(estimativaTotal > 0.7){
		if( ((primeiroPontoM - ultimoPontoM) > -25) && ((primeiroPontoM - ultimoPontoM) < 25) ){
			printf("Resultado: Pista em linha reta.");
		}
		else if(primeiroPontoM < ultimoPontoM){
			printf("Resultado: Curva a esquerda.");
		}
		else if(primeiroPontoM > ultimoPontoM){
			printf("Resultado: Curva a direita.");
		}

	}else{
		printf("Resultado: Formato da pista nao estimado.");
	}
	return 0;
}
