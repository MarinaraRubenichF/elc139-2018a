[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2018a) > Trabalhos

# T2: Experiências com Profilers

Disciplina: ELC139 - Programação Paralela <br/>Professora: Andrea Schwertner Charão<br/> Aluna: Marinara Rübenich Fumagalli
## Sumário
1. [**Parte 1**](Entrega.md#1-parte-1)   
    a. [Perfil de Execução - Alteração](Entrega.md#a-perfil-de-execução---alteração)  
    b. [Perfil de Execução - Paralelização](Entrega.md#b-perfil-de-execução---paralelização)
2. [**Parte 2**](Entrega.md#1-parte-1)  
    a. [Profilers - Particularidades e Curiosidades](Entrega.md#a-profilers---particularidades)  
    b. [Profilers - Dúvidas e Dificuldades](Entrega.md#b-profilers---dúvidas-e-dificuldades)  
    c. [Profilers - Resultados](Entrega.md#c-profilers---resultados)  
3. [**Anexos**](Entrega.md#3-anexos)  
    a. [Parte 1](Entrega.md#a-parte-1)  
    b. [Parte 2](Entrega.md#b-parte-2)  
4. [**Referências**](Entrega.md#4-referências)  
## 1. Parte 1
### a. Perfil de Execução - Alteração
 #### O perfil é afetado pelas opções de configuração?
 Sim. (analisando melhor antes de responder).
### b. Perfil de Execução - Paralelização
#### Pelo perfil de execução, há alguma função que poderia ser candidata a paralelização? Por quê?
Sim, esta função é a 'dot_product', pois pude pra notar através das minhas tentativas que ele chegou a tomar 100x mais de tempo do que as outras funções [[Vide Screenshots](Parte 1/Screenshots)]. Como o tempo total de execução do programa em si não é influenciado por entradas (que são dadas apenas no início) mas sim pelo processador, paralelizar esta função nos daria um ganho extremamente considerável no desempenho.
## 2. Parte 2
### a. Profilers - Particularidades
#### Particularidades de instalação, recursos ou funcionamento dos profilers
### b. Profilers - Dúvidas e Dificuldades
#### Dúvidas e/ou dificuldades encontradas
### c. Profilers - Resultados
#### Resultados obtidos 
## 3. Anexos
### a. Parte 1
### b. Parte 2
## 4. Referências
- Mattos, Luís Felipe de Souza. Cap. 2: Programação Paralela. [Link](http://www.ic.unicamp.br/~cortes/mo601/trabalho_mo601/luis_felipe_matos_cap2/Trabalho-MC852-ra107822.pdf).
- Falcão, Djalma M. Introdução ao Desenvolvimento de Aplicações Paralelas e Distribuídas. [Link](http://slideplayer.com.br/slide/1600688/).
