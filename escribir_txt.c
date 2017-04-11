/* Como escrbiri sobre un archivo de texto */

#include <stdio.h>
#include <stdlib.h>

void escribir(float *z, int n);

int main()
{
int i,n;
float *z;

n = 10;
z = malloc(n*sizeof(float));

for(i=0;i<n;i++)
	z[i] = i*10;

escribir(z,n);

}


void escribir(float *z, int n)
{
int i;
FILE *fp; // Declaro el puntero que va a ir al archivo (FILE es un tipo)

fp = fopen("my_file.txt","a"); // "r": read  "w": write   "a": append

for(i=0;i<n;i++)
	{
	fprintf(fp,"%f\n",*(z+i));
	}

fclose(fp);
}

