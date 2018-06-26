#include <complex>
#include <cstdlib>
#include <iostream>
#include <sys/time.h>
#include <omp.h>

using namespace std;

/*
 * Tempo (wallclock) em microssegundos
 */ 
long wtime()
{
   struct timeval t;
   gettimeofday(&t, NULL);
   return t.tv_sec*1000000 + t.tv_usec;
}

int main(int argc, char* argv[]){
	int max_row, max_column, max_n, c, r;
	long start_time, end_time;
	
	if ((argc != 4)) {
 		printf("Uso: %s <Max. linhas> <Max. colunas> <N iteracoes>", argv[0]);
 		exit(EXIT_FAILURE);
 	}
   
	max_row = atoi(argv[1]);
	max_column = atoi(argv[2]);
	max_n = atoi(argv[3]);

	try
	{
		start_time = wtime();

		char **mat = (char**)malloc(sizeof(char*)*max_row);

		for (int i=0; i<max_row;i++)
			mat[i]=(char*)malloc(sizeof(char)*max_column);

		#pragma omp parallel for num_threads(2) private(r, c) schedule(dynamic)
		for(r = 0; r < max_row; ++r){
			for(c = 0; c < max_column; ++c){
				complex<float> z;
				int n = 0;
				while(abs(z) < 2 && ++n < max_n)
					z = pow(z, 2) + decltype(z)(
						(float)c * 2 / max_column - 1.5,
						(float)r * 2 / max_row - 1
					);
				mat[r][c]=(n == max_n ? '#' : '.');
			}
		}

		for(int r = 0; r < max_row; ++r){
			for(int c = 0; c < max_column; ++c)
				std::cout << mat[r][c];
			cout << '\n';
		}
		end_time = wtime();
		printf("\nTempo em microssegundos: %ld\n", (long) (end_time - start_time));
	}
	catch (bad_alloc)
	{
		cerr << "Erro: alocacao de memoria" << endl;
		return 1;
	}
	
	return 0;	
}


