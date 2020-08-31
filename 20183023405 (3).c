//Algoritmo de Dijkstra em C
//Fonte : https://www.thecrazyprogrammer.com/2014/03/dijkstra-algorithm-for-finding-shortest-path-of-a-graph.html

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

int numCidades = 0;
int numArestas = 0;

#define INFINITE 9999

void dijkstra(int G[numCidades][numCidades],int n,int startnode, int cidadeFinal, char cidades[numCidades][20]){

int cost[numCidades][numCidades],distance[numCidades],pred[numCidades];
int visited[numCidades],count,mindistance,nextnode,i,j;

//pred[] stores the predecessor of each node
//count gives the number of nodes seen so far
//create the cost matrix
  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++)
      if(G[i][j] == 0)
        cost[i][j] = INFINITE;
      else
        cost[i][j] = G[i][j];

  //initialize pred[],distance[] and visited[]
  for(i = 0; i < n; i++){
    distance[i] = cost[startnode][i];
    pred[i] = startnode;
    visited[i] = 0;
  }

  distance[startnode] = 0;
  visited[startnode] = 1;
  count = 1;

  while(count < n-1){
    mindistance = INFINITE;

    //nextnode gives the node at minimum distance
    for(i=0;i<n;i++)
      if(distance[i] < mindistance&&!visited[i]){
          mindistance = distance[i];
          nextnode = i;
        }

    //check if a better path exists through nextnode
    visited[nextnode] = 1;
    for(i=0;i<n;i++)
      if(!visited[i])
        if(mindistance + cost[nextnode][i] < distance[i]){
          distance[i] = mindistance + cost[nextnode][i];
          pred[i]=nextnode;
        }
    count++;
  }

  //print the path and distance of each node
  i = cidadeFinal;
  int m = 0;

  if(i != startnode){
    printf("Menor percurso:");
    j = i;
    do{
      j = pred[j];
      m++;
    }while(j != startnode);
  }

  char percursoFinal[m][20];
  m = 0;
  i = cidadeFinal;

  if(i != startnode){
    strcpy(percursoFinal[m], cidades[i]);
    j = i;
    do{
      j = pred[j];
      m++;
      strcpy(percursoFinal[m], cidades[j]);
    }while(j != startnode);
  }

  for(int i = m; i >= 0; i--){
          printf(" %s", percursoFinal[i]);
  }

  printf("\nDistancia total: %d Km\n",distance[cidadeFinal]);
  }

int main(){
    FILE *arquivo;
    char arquivoNOME[20];
    char origemDestino[41], cOrigem[20], cDestino[20], cidadeAtual[20], cidades[100][20];
    char str[100];
    int numArestas = 0;
    int numCOrigem = 0;
    int numCDestino = 0;
    char* token;

    int cidadeJaRegistrada = 0;

    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s", arquivoNOME);

    arquivo = fopen(arquivoNOME,"r+");
    if(!arquivo){
      printf("Falha ao abrir o arquivo :(");
      return 0;
    }

    //Leitura e reconhecomento do numero de arestas
    numArestas = atoi(fgets(str, 100, arquivo));
    char origem[numArestas][20];
    char destino[numArestas][20];
    char distanciaRotas[numArestas][100];

    //Leitura e reconhecimento da distancia em cada cidade
    char linha[numArestas][100];


    for(int i = 0; i < numArestas; i++){
        fgets(str, 100, arquivo);
        strcpy(linha[i],str);
        token = strtok(str, " ");
        strcpy(origem[i],token);
        token = strtok(NULL, " ");
        strcpy(destino[i],token);
        token = strtok(NULL, "\n");
        strcpy(distanciaRotas[i],token);

    }

    int l = 0;

    for(int i = 0; i < numArestas; i++){
        strcpy(cidadeAtual,origem[i]);
        if(i == 0){
            strcpy(cidades[l],cidadeAtual);
            l++;
            numCidades++;
        }
        else{
            for(int j = 0; j < i; j++){
                if((strcmp(cidadeAtual, origem[j]) == 0)){
                    cidadeJaRegistrada = 1;
                }
            }
            if(cidadeJaRegistrada == 0){
                strcpy(cidades[l],cidadeAtual);
                l++;
                numCidades++;
            }
            cidadeJaRegistrada = 0;
        }
    }

    for(int i = 0; i < numArestas; i++){
        strcpy(cidadeAtual, destino[i]);
        for(int j = 0; j < l; j++){
            if((strcmp(cidadeAtual,cidades[j]) == 0)){
                cidadeJaRegistrada = 1;
            }
        }
        if(cidadeJaRegistrada == 0){
                strcpy(cidades[l],cidadeAtual);
                l++;
                numCidades++;
            }
        cidadeJaRegistrada = 0;
    }


    rewind(arquivo);
    fgets(str, 100, arquivo);

    for(int i = 0; i < numArestas; i++){
      fgets(str, 100, arquivo);
      strcpy(linha[i],str);
      token = strtok(str, " ");
    }

    int vDist[numCidades][numCidades];

    for(int i = 0; i < numCidades; i++){
        for(int j = 0; j < numCidades; j++){
            vDist[i][j] = INFINITE;
        }
    }

    int posicaoCidade = 0;

    for(int i = 0; i < numCidades; i++){
      for(int j = i; j < numArestas; j++){
            if(i == j){
                vDist[i][j] = 0;
            }
            if(strcmp(cidades[i], origem[j]) == 0){
                for(int k = 0; k < numCidades; k++){
                    if(strcmp(cidades[k], destino[j]) == 0){
                        posicaoCidade = k;
                        vDist[i][posicaoCidade] = vDist[posicaoCidade][i] = atoi(distanciaRotas[j]);
                    }
                }
            }
      }
    }

    //Leitura e reconhecimento da cidade origem x destino
    fgets(str, 100, arquivo);
    strcpy(origemDestino,str);

    token = strtok(origemDestino, " ");
    strcpy(cOrigem, token);
    token = strtok(NULL,"\n");
    strcpy(cDestino, token);


    for(int i = 0; i < numCidades; i++){
        if((strcmp(cidades[i], cOrigem)) == 0){
            numCOrigem = i;
        }
    }

    for(int i = 0; i < numCidades; i++){
        if((strcmp(cidades[i], cDestino)) == 0){
            numCDestino = i;
        }
    }

    dijkstra(vDist,numCidades,numCOrigem, numCDestino, cidades);

    fclose(arquivo);

}
