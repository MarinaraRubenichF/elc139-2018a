/*
 *  Exemplo de cálculo de produto escalar utilizando OpenMP
 	Marinara Rübenich Fumagalli
 	mrfumagalli@inf.ufsm.br
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

typedef struct 
 {
   double *a;
   double *b;
   double c; 
   int wsize;
   int repeat; 
 } dotdata_t;

// Variavel global, acessivel por todas threads
dotdata_t dotdata;

/*
 * Funcao paralelizada com OpenMP
 */
 
void omp_dotprod()
{
	int i, k;
	double *a = dotdata.a;
	double *b = dotdata.b;
	int wsize = dotdata.wsize;    
	double mysum;

	#pragma omp parallel shared (a, b) private (k, i, mysum)
	{
		for (k = 0; k < dotdata.repeat; k++) {
			mysum = 0.0;
			
			for (i = 0; i < wsize ; i++) {
				mysum += (a[i] * b[i]);
			}
		}
		#pragma omp critical
        dotdata.c += mysum;
	}
}

/*
 * Tempo (wallclock) em microssegundos
 */ 
long wtime()
{
   struct timeval t;
   gettimeofday(&t, NULL);
   return t.tv_sec*1000000 + t.tv_usec;
}

/*
 * Preenche vetor
 */ 
void fill(double *a, int size, double value)
{  
   int i;
   for (i = 0; i < size; i++) {
      a[i] = value;
   }
}

/*
 * Funcao principal
 */ 
int main(int argc, char **argv)
{
   int nthreads, wsize, repeat;
   long start_time, end_time;

   if ((argc != 4)) {
      printf("Uso: %s <nthreads> <worksize> <repetitions>\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   nthreads = atoi(argv[1]); 
   wsize = atoi(argv[2]);  // worksize = tamanho do vetor de cada thread
   repeat = atoi(argv[3]); // numero de repeticoes dos calculos (para aumentar carga)

   // Cria vetores
   dotdata.a = (double *) malloc(wsize*nthreads*sizeof(double));
   fill(dotdata.a, wsize*nthreads, 0.01);
   dotdata.b = (double *) malloc(wsize*nthreads*sizeof(double));
   fill(dotdata.b, wsize*nthreads, 1.0);
   dotdata.c = 0.0;
   dotdata.wsize = wsize;
   dotdata.repeat = repeat;
   
   // Calcula c = a . b em nthreads, medindo o tempo
   start_time = wtime();
   omp_dotprod();
   end_time = wtime();

   // Mostra resultado e estatisticas da execucao
   printf("%f\n", dotdata.c);
   printf("%d thread(s), %ld usec\n", nthreads, (long) (end_time - start_time));
   fflush(stdout);

   free(dotdata.a);
   free(dotdata.b);

   return EXIT_SUCCESS;
}
