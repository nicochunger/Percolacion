/* Como escrbiri sobre un archivo de texto */

void escribir(float *z, int n)
{
int i;
FILE *fp; // Declaro el puntero que va a ir al archivo (FILE es un tipo)

fp = fopen("my_file.txt","a"); // "r": read  "w": write   "a": append

for(i=0;i<n;i++)
	{
	fprintf(fp,"%f\n",*(z+i)
	}

fclose(fp);
}

