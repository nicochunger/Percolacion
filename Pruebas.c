#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main(){

int i;
srand(time(NULL));
for(i=0;i<10;i=i+1){

double X = ((double)rand()/(double)RAND_MAX);

printf("%f \n", X);
}

}
