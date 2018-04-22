[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2018a) > Trabalhos

# T4: Scheduling com OpenMP

Disciplina: ELC139 - Programação Paralela  
Professora: Andrea Schwertner Charão  
Aluna: Marinara Rübenich Fumagalli

## Sumário
1. [**Casos de teste**](#1-casos-de-teste)   
    a. [Auto](#a-auto)  
    b. [Dynamic](#b-dynamic)  
    c. [Guided](#c-guided)  
    d. [Runtime](#d-runtime)  
    e. [Static](#e-static)  
2. [**Exemplos de Sáida**](#2-exemplos-de-saída)  
   a. [Auto](#a-auto)  
    b. [Dynamic](#b-dynamic)  
    c. [Guided](#c-guided)  
    d. [Runtime](#d-runtime)  
    e. [Static](#e-static)    
3. [**Referências**](#3-referências)  

## 1. Casos de Teste

* O programa em OpenMP se encontra aqui: [OpenMPDemoABC.cpp](Códigos/OpenMPDemoABC.cpp). Nesta seção serão mostradas as partes do código que tratam de cada Schedule, na seção 2 serão mostrados os resultados obtidos em cada tipo. Para cada um deles foi implementado um resultado correto (com exclusão mútua) e um incorreto (sem exclusão mútua), isso nos dá uma melhor visão das diferenças dos tratamentos que o OpenMP faz.  
*\*Schedule: define como as iterações serão divididas entre as threads paralelamente. Existem 5 tipos, são eles:*

### a. Auto

* É o compilador quem decide como será a distribuição das iterações do laço paralelo.
   
    ```c
    void fillArrayConcurrentlyAuto(){
        if(critical){
            #pragma omp parallel for schedule(auto)
            for (int i = 0; i < nThreads * nTimes; ++i)
                #pragma omp critical
                array->addChar('A'+omp_get_thread_num());
        }
        else{
            #pragma omp parallel for schedule(auto)
            for (int i = 0; i < nThreads * nTimes; ++i)
                array->addChar('A'+omp_get_thread_num());
            }
        }
    }
    ```

### b. Dynamic

* A distribuição é feita em tempo de execução, dinamicamente. É o bloco quem decide a quantia de iterações que cada thread receberá.

    ```c
    void fillArrayConcurrentlyDynamic(){
        if(critical){
            #pragma omp parallel for schedule(dynamic)
            for (int i = 0; i < nThreads * nTimes; ++i)
                #pragma omp critical
                array->addChar('A'+omp_get_thread_num());
        }
        else{
            #pragma omp parallel for schedule(dynamic)
            for (int i = 0; i < nThreads * nTimes; ++i)
                array->addChar('A'+omp_get_thread_num());
        }
    }
    ```

### c. Guided

* A distribuição é feita em tempo de execução, dinamicamente. É o bloco quem decide a quantia mínima de iterações que cada bloco receberá, essa quantia diminui até chegar a nTimes.

    ```c
    void fillArrayConcurrentlyGuided(){
		if(critical){
	    	#pragma omp parallel for schedule(guided)
			for (int i = 0; i < nThreads * nTimes; ++i)
				#pragma omp critical
				array->addChar('A'+omp_get_thread_num());
		}
		else{
			#pragma omp parallel for schedule(guided)
			for (int i = 0; i < nThreads * nTimes; ++i)
				array->addChar('A'+omp_get_thread_num());
		}
	}
    ```

### d. Runtime

* A distribuição é feita em tempo de execução, porém dependem das especificações da biblioteca OpenMP.

    ```c
    void fillArrayConcurrentlyRuntime(){
		if(critical){
			#pragma omp parallel for schedule(runtime)
			for (int i = 0; i < nThreads * nTimes; ++i)
				#pragma omp critical
				array->addChar('A'+omp_get_thread_num());
		}
		else{
			#pragma omp parallel for schedule(runtime)
			for (int i = 0; i < nThreads * nTimes; ++i)
				array->addChar('A'+omp_get_thread_num());
		}
	}
    ```

### e. Static

* A distribuição é feita em tempo de compilação, estaticamente. É o bloco quem decide a quantia de iterações que cada thread receberá.

    ```c
    void fillArrayConcurrentlyStatic(){
		if(critical){
			#pragma omp parallel for schedule(static)
			for (int i = 0; i < nThreads * nTimes; ++i)
				#pragma omp critical
				array->addChar('A'+omp_get_thread_num());
		}
		else{
			#pragma omp parallel for schedule(static)
			for (int i = 0; i < nThreads * nTimes; ++i)
				array->addChar('A'+omp_get_thread_num());
		}
	}
    ```

## 2. Exemplos de Saída

* Para compilar:  
 `g++ -std=c++11 -fopenmp -o teste OpenMPDemoABC.cpp`

### a. Auto

    ```
    SCHEDULE AUTO:

    Com critical:
    ABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABC
    A=20 B=20 C=20

    Sem Critical:
    ABCABCAABCABCACBACBACBCABCABCABCABCABCACBCBACBACBACBACB-ABA-
    A=20 B=19 C=19
    ```

### b. Dynamic

    ```
    SCHEDULE DYNAMIC:

    Com critical:
    CBACBACBACBACBACBACBACBACBACBACBACBACBACBACBACBACBACBACBACBA
    A=20 B=20 C=20

    Sem Critical:
    AABCABCABCABCABCAABCABCABCABCABCABCBACBACBACBACBACBACBACBA--
    A=21 B=19 C=18
    ```

### c. Guided

    ```
    SCHEDULE GUIDED:

    Com critical:
    BCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCA
    A=20 B=20 C=20

    Sem Critical:
    AABCABCACBACBABCCABBACBACBACBACBACBACBACBACBACBACBACABACBA--
    A=21 B=19 C=18
    ```

### d. Runtime

    ```
    SCHEDULE RUNTIME:

    Com critical:
    CBACBACBACBACBACBACBACBACBACBACBACBACBACBACBACBACBACBACBACBA
    A=20 B=20 C=20

    Sem Critical:
    AACBABCABCABCABCABCABCABCABCABCAB-CBACBCABCABACBACBACBACBA--
    A=20 B=19 C=18
    ```

### e. Static

    ```
    SCHEDULE STATIC:

    Com critical:
    CBACBACBACBACBACBACBACBACBACBACBACBACBACBACBACBACBACBACBACBA
    A=20 B=20 C=20

    Sem Critical:
    AACBCABCABACBACBABCABCABCABCABCABCABACBCABACBACBACBACABC-BC-
    A=20 B=19 C=19
    ```

## 3. Referências
- Wilkinson, Barry; Allen, Michael. Parallel Programming. Livro.
- Chandra, Rohit. Parallel Programming in OpenMP. Livro.
- Swan, Tom. Aprendendo C++. Livro.
- Barney, Blaise - LNLL. Tutorials OpenMP. [Link](https://computing.llnl.gov/tutorials/openMP/).
- IBM Knowledge Center. OMP_SCHEDULE. [Link](https://www.ibm.com/support/knowledgecenter/SS2MB5_14.1.0/com.ibm.xlf141.bg.doc/proguide/ompsched.html).
