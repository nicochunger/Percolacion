#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main(){

srand(time(NULL));
double X=((double)rand()/(double)RAND_MAX);

printf("%f \n", X);

}
