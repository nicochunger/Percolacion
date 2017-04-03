#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

/* Declaracion de Funciones*/

void llenar(int *red, int m, int n, float proba);
void imprimir(int *red, int m, int n);

/* Definicion de Funciones */

void llenar(int *red, int m, int n, float proba){

	int i;
	for(i=0;i<n*m;i=i+1){
		srand(time(NULL));
		double rdom=((double)rand()/(double)RAND_MAX);
	
		if(rdom<proba){
			red[i]=1}
		else{
			red[i]=0}
		}

	}

void imprimir(int *red, int m, int n){

	int i, j;
	for(i=0;i<m;i=i+1){
		for(j=0;j<n;j=j+1){
			printf("%d ", red[i]
			}
		}

	}

float* red;
int n,m;
n = 10;
m = 10;
red = malloc(n*m*sizeof(int));

}




