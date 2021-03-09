#include <stdlib.h>
#include <stdio.h>

int procuraHeap(int *vetor, int tamVetor){
	int i;
	int valorAtual;
	
	if((vetor[0] < vetor[1]) || (vetor[0] < vetor[2])){
		return 0;
	}
	for(i = 1; i < tamVetor; i++){
		valorAtual = vetor[i];
		if((2*i) + 1 <= tamVetor){
			if((valorAtual >= vetor[2*i]) && (valorAtual >= vetor[(2*i) + 1])){
				continue;
			}
			else if(((2*i)+1) > tamVetor){
				return 0;
			}
			else{
				continue;
			}
		}
	}
	
	return 1;
}

int main(){
	int *vetor;
	int tamVetor;
	int i = 0;
	int numVetor;
	printf("Digite o tamanho do vetor: ");
	scanf("%d", &tamVetor);
	
	vetor = (int*) malloc(tamVetor * sizeof(int));
	
	
	printf("Insira cada item do vetor a seguir:\n");
	for(i = 0; i < tamVetor; i++){
		scanf("%d", &numVetor);
		vetor[i] = numVetor;
	}
	
	if(procuraHeap(vetor, tamVetor))
		printf("\nResposta: O vetor e um heap.");
	else{
		printf("\nResposta: O vetor nao e um heap.");
	}

}
