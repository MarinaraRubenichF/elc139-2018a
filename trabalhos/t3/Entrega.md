[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2018a) > Trabalhos

# T3: Programação Paralela Multithread

Disciplina: ELC139 - Programação Paralela  
Professora: Andrea Schwertner Charão  
Aluna: Marinara Rübenich Fumagalli

## Sumário
1. [**Questões Pthreads**](#1-questões-pthreads)   
    a. [Questão 1](#a-questão-1)  
    b. [Questão 2](#b-questão-2)  
    c. [Questão 3](#c-questão-3)  
    d. [Questão 4](#d-questão-4)  
    e. [Questão 5](#e-questão-5)  
2. [**Implementação OpenMP**](#2-implementação-openmp)  
    a. [Parte 1](#a-parte-1)  
    b. [Parte 2](#b-parte-2)  
3. [**Referências**](#3-referências)  

## 1. Questões Pthreads

### a. Questão 1

* Explique como se encontram implementadas as 4 etapas de projeto: particionamento, comunicação, aglomeração, mapeamento (use trechos de código para ilustrar a explicação).

### b. Questão 2

* Considerando o tempo (em segundos) mostrado na saída do programa, qual foi a aceleração com o uso de threads?

### c. Questão 3
* A aceleração (speedup) se sustenta para outros tamanhos de vetores, números de threads e repetições? Para responder a essa questão, você terá que realizar diversas execuções, variando o tamanho do problema (tamanho dos vetores e número de repetições) e o número de threads (1, 2, 4, 8..., dependendo do número de núcleos). Cada caso deve ser executado várias vezes, para depois calcular-se um tempo de processamento médio para cada caso. Atenção aos fatores que podem interferir na confiabilidade da medição: uso compartilhado do computador, tempos muito pequenos, etc.

### d. Questão 4

* Elabore um gráfico/tabela de aceleração a partir dos dados obtidos no exercício anterior.

### e. Questão 5

* Explique as diferenças entre [pthreads_dotprod.c](pthreads_dotprod/pthreads_dotprod.c) e [pthreads_dotprod2.c](pthreads_dotprod/pthreads_dotprod2.c). Com as linhas removidas, o programa está correto? 

## 2. Implementação OpenMP

### a. Parte 1

* Implemente um programa equivalente a [pthreads_dotprod.c](pthreads_dotprod/pthreads_dotprod.c) usando OpenMP.  
    * Aqui segue o código do programa [openmp](openmp/omp_dotprod.c).

### b. Parte 2

* Avalie o desempenho do programa em OpenMP, usando os mesmos dados/argumentos do programa com threads POSIX. 

## 3. Referências
- Geyer, Cláudio. OpenMP: Uma Introdução. [Link](ftp://ftp.inf.ufrgs.br/pub/geyer/PDP-CIC-ECP/slidesAlunos/SemestresAnteriores/ProvaP2-2013-1/OpenMP-intro-v5d3-jun2013-mac.pdf).
- Wilkinson, Barry; Allen, Michael. Parallel Programming. Livro.
- Chandra, Rohit. Parallel Programming in OpenMP. Livro.

