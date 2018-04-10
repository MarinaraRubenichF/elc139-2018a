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
    * **Particionamento**  
    O ***particionamento*** ocorre quando dividimos o processamento em pequenas tarefas, então a parte do [código](pthreads_dotprod/pthreads_dotprod.c) que faz isso está relacionada a função *dotprod_worker*:
        ``` c
        ...
        void *dotprod_worker(void *arg)
        {
           int i, k;
           long offset = (long) arg;
           double *a = dotdata.a;
           double *b = dotdata.b;     
           int wsize = dotdata.wsize;
           int start = offset*wsize;
           int end = start + wsize;
       double mysum;
       ...
        ``` 
        Ou seja, cada thread vai resolver uma parte do problema e ir se multiplicando até chegar ao valor final. Nesse caso a thread funciona com vetores, inicia no *start* e termina no *end*. 
        
     * **Comunicação**  
     A ***Comunicação*** se dá quando temos estruturas e algoritmos necessários para comunicação. A parte do [código](pthreads_dotprod/pthreads_dotprod.c) que faz isso também está relacionada a função *dotprod_worker*:
     
        ```c
        ...
        pthread_mutex_lock (&mutexsum);
        dotdata.c += mysum;
        pthread_mutex_unlock (&mutexsum);
        ...
        ```
        
    Isso ocorre através da *Exclusão Mútua* ou *Mutex*, que controla a concorrência, ou seja, enquanto uma thread está acessando *x* parte do código e não finalizou a outra thread não pode acessá-lo. Nesse caso a variável *dotdata* recebe os resultados dos cálculos de cada thread, por isso ela se encontra envolta pelos *Mutex*.
    
    * **Aglomeração**  
    A ***Aglomeração***, diferente do particionamento, aglomera (une) as tarefas para melhorar o desempenho. A parte do [código](pthreads_dotprod/pthreads_dotprod.c) que faz isso também está relacionada a função *dotprod_worker*:
    
        ```
        ...
        for (k = 0; k < dotdata.repeat; k++) {
        mysum = 0.0;
            for (i = start; i < end ; i++)  {
                 mysum += (a[i] * b[i]);
            }
        }
        ...
        ``` 
    
    Sua função é se agrupar as multiplicações entre os vetores (que resultam somas parciais que são armazenadas na variável *mysum*) até chegarmos no resultado final.
    
    * **Mapeamento**  
    No ***Mapeamento*** ocorre a distribuição homogênea das tarefas a serem executados pelo processador. A função responsável por isso no [código](pthreads_dotprod/pthreads_dotprod.c) é a *dotprod_threads*:
    
        ```
        ...
        void dotprod_threads(int nthreads)
        {
        ...

        for (i = 0; i < nthreads; i++) {
           pthread_create(&threads[i], &attr, dotprod_worker, (void *) i);
        }
        ... 
        ```
        
    Aqui se fazem as divisões das tarefas por igual, o vetor será dividido conforme o número de threads que o usuário determina.
        

### b. Questão 2

* Considerando o tempo (em segundos) mostrado na saída do programa, qual foi a aceleração com o uso de threads?

    ```
    C:\Users\ASUS\elc139-2018a\trabalhos\t3\pthreads_dotprod>t3 1 1000000 2000
    10000.000000
    1 thread(s), 7364588 usec
    ```
    
    ```
    C:\Users\ASUS\elc139-2018a\trabalhos\t3\pthreads_dotprod>t3 2 500000 2000
    10000.000000
    2 thread(s), 3842238 usec
    ```
    
    SpeedUp (nesse caso) = 1,9167...
    Os mais diversos testes realizados com esses mesmos valores não tiveram grandes variações.

### c. Questão 3
* A aceleração (speedup) se sustenta para outros tamanhos de vetores, números de threads e repetições? Para responder a essa questão, você terá que realizar diversas execuções, variando o tamanho do problema (tamanho dos vetores e número de repetições) e o número de threads (1, 2, 4, 8..., dependendo do número de núcleos). Cada caso deve ser executado várias vezes, para depois calcular-se um tempo de processamento médio para cada caso. Atenção aos fatores que podem interferir na confiabilidade da medição: uso compartilhado do computador, tempos muito pequenos, etc.

### d. Questão 4

* Elabore um gráfico/tabela de aceleração a partir dos dados obtidos no exercício anterior.

### e. Questão 5

* Explique as diferenças entre [pthreads_dotprod.c](pthreads_dotprod/pthreads_dotprod.c) e [pthreads_dotprod2.c](pthreads_dotprod/pthreads_dotprod2.c). Com as linhas removidas, o programa está correto? 
    * No código [pthreads_dotprod2.c](pthreads_dotprod/pthreads_dotprod2.c) foram tiradas as linhas equivalentes ao *Mutex*:
   
   ```c
    ...
    pthread_mutex_lock (&mutexsum);
    //dotdata.c += mysum;
    pthread_mutex_unlock (&mutexsum);
    ...
    ```
    
    Como explicado na questão 1 essas linhas de código garantem os acessos a Região Crítica, então isso garante que mais de uma thread não acesse a masma parte *x* ao mesmo tempo, garantindo a segurança e confiabilidade dos cálculos.

## 2. Implementação OpenMP

### a. Parte 1

* Implemente um programa equivalente a [pthreads_dotprod.c](pthreads_dotprod/pthreads_dotprod.c) usando OpenMP.  
    * Aqui segue o código do programa em OpenMP: [omp_dotprod.c](openmp/omp_dotprod.c).

### b. Parte 2

* Avalie o desempenho do programa em OpenMP, usando os mesmos dados/argumentos do programa com threads POSIX. 

## 3. Referências
- Geyer, Cláudio. OpenMP: Uma Introdução. [ftp://ftp.inf.ufrgs.br/pub/geyer/PDP-CIC-ECP/slidesAlunos/SemestresAnteriores/ProvaP2-2013-1/OpenMP-intro-v5d3-jun2013-mac.pdf](ftp://ftp.inf.ufrgs.br/pub/geyer/PDP-CIC-ECP/slidesAlunos/SemestresAnteriores/ProvaP2-2013-1/OpenMP-intro-v5d3-jun2013-mac.pdf).
- Wilkinson, Barry; Allen, Michael. Parallel Programming. Livro.
- Chandra, Rohit. Parallel Programming in OpenMP. Livro.

