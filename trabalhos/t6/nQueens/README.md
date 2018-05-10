# T6: N-Rainhas com OpenMP

## Pastas

1. A [Pasta 1](1.nQueens_Seq) contém o programa original, sequencial.

2. A [Pasta 2](2.nQueens_OpenmMP) contém a 1ª e a 2ª solução paralelizada do programa, basta modificar as linhas das diretivas.

## Detalhes sobre o ambiente

**Sistema Operacional:**  
Windows 10

**Ferramentas:**  
Dev-C++ 5.11  
Cygwin 2.10.0  
gcc (GCC) 6.4.0

**Arquitetura:**  
Intel® Core™ i5-6200U  
2,2 GHz até 2,7 GHz  
2 núcleos, 2 threads por núcleo  
4GB RAM, 1TB HD  
3MB Cache L3
Mais detalhes [aqui](https://ark.intel.com/products/85212/Intel-Core-i5-5200U-Processor-3M-Cache-up-to-2_70-GHz).

## Resultados

### Solução 1

* Realizar a paralelização das soluções para cada posição inicial das n rainhas. Schedule dynamic, a distribuição é feita em tempo de execução e é o bloco quem decide a quantia de iterações que cada thread receberá.

  * Para N de 10 a 15 (modifica N no código): `./nqueens`  

    | Nº Threads | Rainhas | Tempo      | SpeedUp |  
    | :--------: | :-----: | :--------: | :-----: |  
    | 1          | 10      | 0,011613s  | -       |  
    | 1          | 11      | 0,058876s  | -       |  
    | 1          | 12      | 0,327562s  | -       |  
    | 1          | 13      | 1,988893s  | -       |  
    | 1          | 14      | 12,606894s | -       |  
    | 1          | 15      | 1,4926448m | -       |  
    | 2          | 10      | 0,010230s  | 1,135   |  
    | 2          | 11      | 0,050263s  | 1,171   |  
    | 2          | 12      | 0,234470s  | 1,397   |
    | 2          | 13      | 1,478098s  | 1,345   |
    | 2          | 14      | 9,624598s  | 1,309   |
    | 2          | 15      | 1,2728904m | 1,172   |
    | 4          | 10      | 0,009305s  | 1,248   |
    | 4          | 11      | 0,048408s  | 1,216   |
    | 4          | 12      | 0,179981s  | 1,819   |
    | 4          | 13      | 1,083951s  | 1,834   |
    | 4          | 14      | 8,392339s  | 1,502   |
    | 4          | 15      | 1,2241139m | 1,219   |
  
### Solução 2

* Realizar a paralelização das soluções para cada posição inicial das n rainhas. Schedule guided, a distribuição é feita em tempo de execução e é o bloco quem decide a quantia de iterações que cada thread receberá, essa quantia diminui até chegar a size.

  * Para N de 10 a 15 (modifica N no código): `./nqueens`  

    | Nº Threads | Rainhas | Tempo      | SpeedUp |  
    | :--------: | :-----: | :--------: | :-----: |  
    | 1          | 10      | 0,011613s  | -       |  
    | 1          | 11      | 0,058876s  | -       |  
    | 1          | 12      | 0,327562s  | -       |  
    | 1          | 13      | 1,988893s  | -       |  
    | 1          | 14      | 12,606894s | -       |  
    | 1          | 15      | 1,4926448m | -       |  
    | 2          | 10      | 0,009153s  | 1,268   |  
    | 2          | 11      | 0,045311s  | 1,299   |  
    | 2          | 12      | 0,265717s  | 1,232   |
    | 2          | 13      | 1,327540s  | 1,498   |
    | 2          | 14      | 8,987704s  | 1,402   |
    | 2          | 15      | 1,0984301m | 1,358   |
    | 4          | 10      | 0,008162s  | 1,422   |
    | 4          | 11      | 0,048380s  | 1,216   |
    | 4          | 12      | 0,209917s  | 1,560   |
    | 4          | 13      | 1,227503s  | 1,620   |
    | 4          | 14      | 8,229271s  | 1,743   |
    | 4          | 15      | 1,0319049m | 1,446   |
    
### Comparação de SpeedUps
  
   | Threads | SpeedUp (Dynamic) | SpeedUp (Guided) |
   | :-----: | :---------------: | :--------------: |
   | 2 | 1,135   | 1,268 |
   | 2 | 1,171   | 1,299 |
   | 2 | 1,397   | 1,232 |
   | 2 | 1,345   | 1,498 |
   | 2 | 1,309   | 1,402 |
   | 2 | 1,172   | 1,358 |
   | 4 | 1,248   | 1,422 |
   | 4 | 1,216   | 1,216 |
   | 4 | 1,819   | 1,560 |
   | 4 | 1,834   | 1,620 |
   | 4 | 1,502   | 1,743 |
   | 4 | 1,268   | 1,446 |
    
## Conclusão

* Em geral foi mais eficiente utilizar a schedule Guided, porém foi muito pouca diferença de performance entre as duas. É possível perceber que a grande maioria dos SpeedUps, em ambos schedules, foram baixos.
 
### Obs.:

*Para compilar qualquer um dos programas de qualquer uma das pastas, no terminal faça:*  
`make`  
`./nqueens`
