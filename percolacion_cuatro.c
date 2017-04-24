#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define P     200             // 1/2^P, P=16
#define Z     1000            // iteraciones
#define N     64               // lado de la red simulada

void  llenar(int *red, int n, float proba);
void  imprimir(int* red, int n);
int   hoshen(int *red,int n);
int   actualizar(int *sitio,int *clase,int s,int frag);
void  etiqueta_falsa(int *sitio,int *clase,int s1,int s2);
void  corregir_etiqueta(int *red,int *clase,int n);
int   percola(int *red,int n);
void  guardar_resultados(float *datos, int n, char nombre[20]);
void  numero_s(int *red, int n, float *ns);

int main()
{

	int    n,z,i,j,s,*red;
	float  *proba,*ns,tau,sigma,*ns_critico,*f_de_z,*ns_p;
	char   nombre[20];

	n=N; //Tamano de red L=64
	z=Z; //Iteraciones

	//proba = 0.59251; //Probabilidad critica para L=64
	tau = -1.739; //Tau obtenido para L=64 en el ejercicio 1d
	sigma = (float)36/91; //Sigma para L=infinito
	s = 200; //Tamano de cluster que voy a analizar

	red = (int *)malloc(n*n*sizeof(int));
	ns = (float *)malloc(P*sizeof(float)); // ns para un s particular en funcion de p
	ns_p = (float *)malloc(n*n*sizeof(float)); // ns para cierto p
	proba = (float *)malloc(P*sizeof(float)); // Vector de probabilidades
	ns_critico = (float *)malloc(n*n*sizeof(float)); // ns en pc para todos los s
	f_de_z = (float *)malloc(P*sizeof(float)); // Funcion f(z)

	FILE *fp;
	fp = fopen("ns_64_100000.txt","r"); //Abro el archivo
	i=0;
    float num;
    while(fscanf(fp, "%f", &num) > 0) 
	{
        ns_critico[i] = num;
        i++;
    }
    fclose(fp);

	for(j=0;j<P;j++) proba[j] = (float)j/P; //Vector de todos los p

	srand(time(NULL));
		
	for(j=0;j<P;j++)
	{
		printf("%d\n",j);
		for(i=0;i<n*n;i++) ns_p[i] = 0; //reseteo el ns_p
		for(i=0;i<z;i++)
		{
			llenar(red,n,proba[j]);
			hoshen(red,n);
			numero_s(red,n,ns_p);
		}
		ns[j] = ns_p[s]/(float)z;
		
	}

	for(i=0;i<P;i++) f_de_z[i] = ns[i]/ns_critico[s];
	guardar_resultados(f_de_z,P,"tp1_4_fz_s200.txt");
	guardar_resultados(proba,P,"tp1_4_probas.txt");

	free(red);
	free(ns);
	free(proba);
	free(ns_p);
	free(ns_critico);
	free(f_de_z);

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

void numero_s(int *red, int n, float *ns)
{
	/*
	Esta funcion calcula el ns para cierta red. Toma una red con el algoritmo de hoshen ya aplicado,
	es decir los clusters estan identificados. Calcula el tamano de todos los fragmentos que hay
	y si encuentra un fragmento de tamano s, le suma un uno a la posicion s del vector ns.
	De esa forma el vector ns va guardando cuantos clusters de cada tamano hay.
	Despues de muchas iteraciones se divide todo por la cantidad de iteraciones para obtener la
	probabilidad de tener un fragmento de tamano s.
	*/ 

	int *fragmentos;
	int i,j,cantidad_frag,contador,etiqueta;
	
	fragmentos = (int *)malloc(n*n*sizeof(int));
	etiqueta = 1;
	cantidad_frag = 0;
	for(i=0;i<n*n;i++)
	{
		if(red[i]>etiqueta)
		{
			fragmentos[cantidad_frag] = red[i];
			etiqueta = red[i];
			cantidad_frag++;
		}
	}
	
	for(i=0;i<cantidad_frag;i++)
	{
		contador = 0;
		for(j=0;j<n*n;j++)
		{
			if(red[j]==fragmentos[i]) contador++;
		}
		ns[contador] += 1.0;
	}
	
	free(fragmentos);
	

}
