#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

/* Declaracion de Funciones*/

void llenar(int* red, int m, int n, float proba);
void imprimir(int* red, int m, int n);


/* Poblar una red de mxn con 0 y 1 con probablidad "proba" */
int* red;
int n,m;
float proba;
proba = 0.5;
n = 20;
m = 20;
red = malloc(n*m*sizeof(int));

llenar(red, m, n, proba);
imprimir(red, m, n);
}


/* Definicion de Funciones */

void llenar(int* red, int m, int n, float proba){

	int i;
	srand(time(NULL));
	for(i=0;i<n*m;i=i+1){
		
		double rdom = ((double)rand()/(double)RAND_MAX);
	
		if(rdom<proba){
			red[i]=1;
			}
		else{
			red[i]=0;
			}
		}

	}

void imprimir(int* red, int m, int n){

	int i, j;
	for(i=0;i<m;i=i+1){
		for(j=0;j<n;j=j+1){
			printf("%d ", red[i*m+j]);
			}
		printf("\n");
		}
	}



