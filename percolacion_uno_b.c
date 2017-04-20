#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define P     1000             // 1/2^P, P=16
#define Z     5000            // iteraciones
#define N     30              // lado de la red simulada


void  llenar(int *red, int n, float proba);
void  imprimir(int* red, int n);
int   hoshen(int *red,int n);
int   actualizar(int *sitio,int *clase,int s,int frag);
void  etiqueta_falsa(int *sitio,int *clase,int s1,int s2);
void  corregir_etiqueta(int *red,int *clase,int n);
int   percola(int *red,int n);
void  guardar_resultados(float *datos, int n, char nombre[15]);
int   intensidad(int *red, int n, int etiqueta);
void  escribir(float p, int z, int n, float pc);

int main(/*int argc,char *argv[]*/)
{
	int    n,z,i,j,*red,count,*masa_perc;
	float  *proba,*intensidades;
	float  *ps;
	float  promedio,sum,disp,p_actual,dif_actual,dif;
	char   nombre[15];

	// ps: Vector con la cantidad de de veces que percolo cada red
	// promedio: Promedio de las probabilidades obtenidas en cada iteracion
	// disp: Dispersion de los pc obtenidos. Desviacion estandar.
	// count: cuenta cuantas veces percola una red con cierta probabilidad p

	//n=N; //Tamano de la red
	z=Z; //Numero de iteraciones

	/*
	if (argc==3) 
	{
		sscanf(argv[1],"%d",&n);
		sscanf(argv[2],"%d",&z);
	}
	*/

	red = (int *)malloc(n*n*sizeof(int)); // Alojo la memoria para la red
	ps = malloc(P*sizeof(float)); // Contador de veces que percola con cierta probabilidad p
	proba = malloc(P*sizeof(float)); // Probabilidades testeadas
	intensidades = malloc(P*sizeof(float)); // Masa promedio del cluster percolante para cada p
	masa_perc = malloc(z*sizeof(int)); // Todas las masas obtenidas para cierta p (se reescribe)
	srand(time(NULL)); // Inicia las seeds para la funcion rand()

	// Creo archivo con el vector de probabilidades
	FILE *fp;
	fp = fopen("vector_probabilidades.txt", "w"); 

	for(i=0;i<P;i++) 
	{
		proba[i] = i*(1.0/P); // Vector con todas las probabilidades
		fprintf(fp,"%f\n",proba[i]);
	}

	fclose(fp);

	for(n=4;n<130;n=n*2) // Itera sobre los tamanos de red
	{	
		for(j=0;j<P;j++) // Itera sobre todos las probabilidades
		{
			count = 0;
			intensidades[j] = 0;
			for(i=0;i<z;i++) // Hace el experiemnto z cantidad de veces
			{
				llenar(red,n,proba[j]);

				hoshen(red,n);
				masa_perc[i] = 0;

				if(percola(red,n))
				{
					count++;
					masa_perc[i] = intensidad(red,n,percola(red,n));
				}
			
				intensidades[j] += masa_perc[i];
			}
			intensidades[j] /= z; // Saco promedio
			intensidades[j] /= (n*n); //Divido por n*n para que este normalizado
			//printf("%f\n",intensidades[j]);
			ps[j] = (float)count/z; // Probabilidad de percolar con probabilidad proba[j]
		}

		dif_actual = 0.5; //Inicializo la diferencia actual para encontrar la menor de todas
		for(i=0;i<P;i++)
		{
			dif = fabs(ps[i] - 0.5);
			if(dif<dif_actual)
			{
				dif_actual = dif;
				p_actual = proba[i];
			}
		}
		
			
		// Guardo los datos de la probabilidad de percolar
		sprintf(nombre, "tp1_1b_%d.txt", n); // Creo el nombre del archivo
		guardar_resultados(ps,P,nombre);
		
		// Guardo las intensidades del cluster percolante
		sprintf(nombre, "tp1_2_%d.txt", n);
		guardar_resultados(intensidades,P,nombre);
		
		printf("Cantidad de iteraciones: %d\n",z); // Imprime la cantidad de iteraciones
		printf("Precision: %f\n", 1.0/P); // Imprime la presicion de p
		printf("pc para red de lado %d: %f\n\n",n,p_actual); // Imprime el pc obtenido

		escribir(1.0/P,z,n,p_actual);
	}

	free(red);
	free(ps);
	free(proba);
	free(intensidades);
	free(masa_perc);


	return 0;
	/*
	llenar(red, n, proba);
	imprimir(red, n);
	hoshen(red, n);
	imprimir(red, n);
	printf("\n%d\n", percola(red, n));
	*/
}

/* Definicion de Funciones */

int hoshen(int *red,int n)
{
	/*
	Esta funcion implementa en algoritmo de Hoshen-Kopelman.
	Recibe el puntero que apunta a la red y asigna etiquetas 
	a cada fragmento de red. 
	*/

	int i,j,k,s1,s2,frag;
	int *clase;

	frag=0; //frag = Fragmento (etiqueta actual de los clusters)

	clase=(int *)malloc(n*n*sizeof(int));

	for(k=0;k<n*n;k++) *(clase+k)=frag;

	// primer elemento de la red

	s1=0;
	frag=1; //Empiezo en 1 para que el primer fragmento sea un 2 (mirar func actualizar)
	if (*red) frag=actualizar(red,clase,s1,frag);

	// primera fila de la red

	for(i=1;i<n;i++) 
	{
		if (*(red+i)) 
		{
			s1=*(red+i-1);  
			frag=actualizar(red+i,clase,s1,frag);
		}
	}


	// el resto de las filas 

	for(i=n;i<n*n;i=i+n)
	{

		// primer elemento de cada fila

		if (*(red+i)) 
		{
			s1=*(red+i-n); 
			frag=actualizar(red+i,clase,s1,frag);
		}

		for(j=1;j<n;j++)
		if (*(red+i+j))
		{
			s1=*(red+i+j-1); 
			s2=*(red+i+j-n);

			if (s1*s2>0)
			{
				etiqueta_falsa(red+i+j,clase,s1,s2);
			}
			else 
			{ if (s1!=0) 
				frag=actualizar(red+i+j,clase,s1,frag);
			else       
				frag=actualizar(red+i+j,clase,s2,frag);
			}
		}
	}

	corregir_etiqueta(red,clase,n);

	free(clase);

	return 0;
}

void llenar(int* red, int n, float proba)
{
	/* 
	Esta funcion toma una red de nxn y la llena con 0s y 1s
	con probabilidad proba 
	*/

	int i;
	//srand(time(NULL));
	for(i=0;i<n*n;i=i+1)
	{
		double rdom = ((double)rand()/(double)RAND_MAX);
	
		if(rdom<proba) 
			red[i]=1;
		else 
			red[i]=0;
	}
}

void imprimir(int* red, int n)
{
	int i, j;
	for(i=0;i<n;i=i+1)
	{
		for(j=0;j<n;j=j+1)
		{
			printf("%d ", red[i*n+j]);
		}
		printf("\n");
	}
	printf("\n");
}

int   actualizar(int *sitio,int *clase,int s,int frag)
{
	/*
	Se fija cual es el valor de s. Si es negativo busca la etiqueta
	verdadera y se la asigna a la posicion actual. Si s es cero, tengo que 
	asignar una etiqueta nueva, para eso
	tengo que aumentar frag en 1, asignar esa eqtiqueta a la posicion y
	y devolver el nuevo valor de frag.
	Si asignaste una etiqueta nueva tiene que actualizar el vector clase con
	esa nueva etiqueta.
	*/

	int s0,frag0;
	s0 = s;
	while(clase[s0]<0)
		s0 = -clase[s0];
	*sitio = s0;

	if(s == 0)
	{
		frag0 = frag + 1;
		*sitio = frag0;

		clase[frag0] = frag0;
		return frag0;
	}

	return frag;
}


void  corregir_etiqueta(int *red,int *clase,int n)
{
	/*
	Despues de hacer el algorimto de Hosher Kopermann, pasa una vez mas por toda
	la red para corregir todas las etiquetas.
	*/
	
	int i,s;	
	for(i=0;i<n*n;i++)
	{
		s = red[i];
		while(clase[s]<0)
			s = -clase[s];
		red[i] = s;
	}
}

void  etiqueta_falsa(int *sitio,int *clase,int s1,int s2)
{
	/*
	Resuelve el conflicto de si los dos s estaban ocupados.
	Primero traquea la etiqueta verdadera de s1 y de s2, despues se fija cual
	de los dos es mas chiquito. Al s mas grande le asigna el valor del s mas
	chiquito pero con una etiqueta falsa, osea le pone un signo negativo.
	Y a la posicion esa de la red le pone la etiqueta que quedo.
	*/

	int s10, s20;
	s10 = s1;
	s20 = s2;
	while(clase[s10]<0)
		s10 = -clase[s10];
	while(clase[s20]<0)
		s20 = -clase[s20];

	if(s10<s20)
	{
		clase[s20] = -s10;
		clase[s10] = s10;
		*sitio = s10;
	}
	else
	{
		clase[s10] = -s20;
		clase[s20] = s20;
		*sitio = s20;
	}
}

int   percola(int *red,int n){

	/*
	Esta funcion se fija si la red percolo o no, La forma en que lo hace es fijandose si unos de los
	clusters se extiende desde el extremo de arriba hasta el extremo de abajo.
	Devuelve un 1 si percolo y un 0 si no percolo.
	*/
	int tamvec = (n*n)/2; //Tamano maximo de etiquetas posibles

	int *arriba;
	int *abajo;
	int i,j;

	arriba = malloc(tamvec*sizeof(int));
	abajo = malloc(tamvec*sizeof(int));

	// Inicializo los dos vectores con todos 0s
	for(i=0;i<tamvec;i++)
	{
		arriba[i] = 0;
		abajo[i] = 0;
	}

	// Recorro la fila de arriba y lleno con un 1 los fragmentos que hay
	i=0;
	for(i=0;i<n;i++){
		if(red[i] != 0)
			arriba[red[i]] = 1;
		}

	// Recorro la fila de abajo y lleno con un 1 los fragmentos que hay
	for(i=n*(n-1);i<n*n;i++)
	{
		if(red[i] != 0) abajo[*(red+i)] = 1;
	}

	// Creo un vector que es el procuto elemento a elemento de arriba y abajo.
	// Si queda algun 1 en el vector producto significa que la red percolo.
	int producto[tamvec];
	for(i=0;i<tamvec;i++)
	{
		producto[i] = arriba[i] * abajo[i];
	}

	// Checkeo si algun fragmento llega de arriba a abajo
	int perc = 0;
	for(i=0;i<tamvec;i++)
	{
		if(producto[i]) perc=i;
	}

	free(abajo);
	free(arriba);

	return perc;
}

void guardar_resultados(float *datos, int n, char nombre[15])
{
	/*
	Esta funcion toma un vector con datos y los guarda todos en un archivo de texto
	*/

	int i;

	FILE *fp; // Declaro el puntero que va a ir al archivo (FILE es un tipo)

	fp = fopen(nombre,"w"); // "r": read  "w": write   "a": append

	for(i=0;i<n;i++)
	{
		fprintf(fp,"%f\n",datos[i]); //Escribo todos los datos en una linea nueva
	}

	fclose(fp);
}

int intensidad(int *red, int n, int etiqueta)
{
	/* Calcula el numero de nodos que hay en el cluster percolante */
	
	int i,cantidad;
	cantidad = 0;
	if(percola(red,n))
	{
		for(i=0;i<n*n;i++)
		{
			if(red[i] == etiqueta)
				cantidad++;
		}
	
		return cantidad;
	}

	else
		return 0;
}

void escribir(float p, int z, int n, float pc)
{
	/* Esta funcion toma los valores obtenidos por la simulacion y los guarda en un archivo de texto
	*/

	int i;
	FILE *fp; // Declaro el puntero que va a ir al archivo (FILE es un tipo)

	fp = fopen("tp1_1b_resultados.txt","a"); // "r": read  "w": write   "a": append

	fprintf(fp,"Tamano de la red: %d\n",n);
	fprintf(fp,"Numero de iteraciones: %d\n",z);
	fprintf(fp,"Precision utilizada: %f\n",p);
	fprintf(fp,"Probabilidad critica obtenida: %f\n",pc);
	fprintf(fp,"\n");

	fclose(fp);
}




