// PROGRAMAÇÃO PARALELA
// Simulação de incêndio em uma floresta.
// Baseada no código proposto por David Joiner.
// Solução 1 - proposta pela aluna: Marinara Rübenich Fumagalli
// Uso: ./firesim <tamanho-do-problema> <nro. experimentos> <probab. maxima> 

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <omp.h>
#include <sys/time.h>
#include "Random.h"
#include "Forest.h"

/*
 * Tempo (wallclock) em microssegundos
 */ 
long wtime()
{
   struct timeval t;
   gettimeofday(&t, NULL);
   return t.tv_sec*1000000 + t.tv_usec;
}

int main(int argc, char* argv[]) 
{
 	// parâmetros dos experimentos
 	int forest_size, n_trials, n_probs;
 	long start_time, end_time;
   
 	if ((argc != 4)) {
 		printf("Uso: %s <tamanho-do-problema> <nro. experimentos> <probab. maxima>", argv[0]);
 		exit(EXIT_FAILURE);
 	}
   
	forest_size = atoi(argv[1]);
	n_trials = atoi(argv[2]);
	n_probs = atoi(argv[3]);
	
	double* percent_burned; // percentuais queimados (saída)
	double* prob_spread;    // probabilidades (entrada)
	double prob_min = 0.0;
	double prob_max = 1.0;
	double prob_step;
	int base_seed = 100;
	    
	try {
		start_time = wtime();
		//Forest* forest = new Forest(forest_size);
		Random rand;
		int ip, it;
		
		prob_spread = new double[n_probs];
		percent_burned = new double[n_probs];
		
		prob_step = (prob_max - prob_min)/(double)(n_probs-1);
		
		printf("Probabilidade, Percentual Queimado\n");
		
		// para cada probabilidade, calcula o percentual de árvores queimadas
		#pragma omp parallel num_threads(2) private(it, ip)
		{
			Forest* forest = new Forest(forest_size);
			
			#pragma omp for schedule(auto)
			for (ip = 0; ip < n_probs; ip++)
			{			
				prob_spread[ip] = prob_min + (double) ip * prob_step;
				percent_burned[ip] = 0.0;
				rand.setSeed(base_seed+ip); // nova seqüência de números aleatórios
				
				// executa vários experimentos
				for (it = 0; it < n_trials; it++) {
					// queima floresta até o fogo apagar
					forest->burnUntilOut(forest->centralTree(), prob_spread[ip], rand);
					percent_burned[ip] += forest->getPercentBurned();
				}
					
				// calcula média dos percentuais de árvores queimadas
				percent_burned[ip] /= n_trials;
					
				// mostra resultado para esta probabilidade
				printf("%lf, %lf\n", prob_spread[ip], percent_burned[ip]);
			}
		}
		delete[] prob_spread;
		delete[] percent_burned;
		      
		end_time = wtime();
		printf("\nTempo em microssegundos: %ld\n", (long) (end_time - start_time));
	}
	catch (std::bad_alloc)
	{
		std::cerr << "Erro: alocacao de memoria" << std::endl;
		return 1;
	}
	
	return 0;
}

