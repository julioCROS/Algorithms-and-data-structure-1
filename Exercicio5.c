/****************
LAED1 - Problema da Mochila
Alunos(as): Julio Cesar Rocha e Pablo Felipe
Data: 01/10/2020
****************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){

    FILE *file;
    char fileName[30], string[5];
    float bpWeight; //Backpack Weight - Peso da mochila
    int qItems; //Quantify Items - Quantidade de items

    float resultWeight = 0;
    float resultCost = 0;

	//Token utilizado para leitura e sepração da linha do arquivo ".txt"  
    char* token;

    printf("Digite o nome do arquivo: ");
    scanf("%s",fileName);

    file = fopen(fileName,"r+"); //Abre arquivo para leitura
    if(file == NULL){
        printf("Unable to open the file. Sorry...");
        exit(0);
    }

    //Reconhecendo o peso maximo suportado pela mochila
    fgets(string, 10, file);
    bpWeight = strtof(string, NULL);

    //Lendo a quantidade de items
    fgets(string, 10, file);
    qItems = strtof(string, NULL);

    //Criando vetor de peso e valor de items da lista
    float iLWeight[qItems];
    float iLCost[qItems];

    //Vetor com o valor de item selecionado (1) ou não-selecionado (0)
    int select[qItems];

    //Lendo as proximas N linhas com os items e seus respectivos valores
    int i = 0;
    for(i = 0; i < qItems; i++){
        fgets(string, 100, file);
        token = strtok(string, " ");
        iLWeight[i]= strtof(token, NULL);
        token = strtok(NULL, " ");
        iLCost[i]= strtof(token, NULL);
    }

	//Calculo do peso total de todos itens e valores que estão na mochila.
    for(i = 0; i < qItems; i++){
        fgets(string, 100, file);
        select[i] = atoi(string);
        if(select[i] == 1){
            resultWeight = resultWeight + iLWeight[i];
            resultCost = resultCost + iLCost[i];
        }
    }
    
    //Se o resultado do peso dos itens, for maior que o peso suportado pela mochila
	//então a solução já pode ser considerada inviavel
	if(resultWeight > bpWeight){
        printf("Solucao inviavel.");
        return 0;
    }

    int j = 0,k = 0;
    float pesoAtual = 0;
    float valorOtimo = 0;
    
	//Implementação criada para varrer todas as possibilidades de itens e pesos na mochila
	//para calcular o valor otimo
    for(i = 0; i < qItems; i++){
        pesoAtual += iLWeight[i];
        for(k = 0; k < qItems; k++){
            pesoAtual += iLWeight[k];
            for(j = 0; j < qItems; j++){
                pesoAtual = pesoAtual + iLWeight[j];
                if(pesoAtual > bpWeight)					// Para não repetir um mesmo item 
                    continue;								// no calculo das possibilidades
                if((iLCost[i] + iLCost[j] + iLCost[k]) >= valorOtimo){
                    valorOtimo = iLCost[i] + iLCost[j] + iLCost[k];
                }
            }
        }
    }
	
    //Se a soma de valores dos itens que se encontram na mochila for igual ao valor otimo
    //então a solução é otima
    if(resultCost == valorOtimo){
        printf("Solucao otima.");
        return 0;
    }
    //Se não, a solução é viavel mas não otima
    else{
        printf("Solucao viavel mas nao otima.");
        return 0;
    }
}
